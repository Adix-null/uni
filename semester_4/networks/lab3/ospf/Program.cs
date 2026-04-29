using System.Collections.Concurrent;

namespace ospf
{
    public static class Constants
    {
        public static readonly int MaxSequenceNumber = 1000000;
        public static readonly int HelloIntervalSeconds = 5;
        public static readonly int LsaFloodIntervalSeconds = 10;
        public static readonly int pollingIntervalMs = 250;
        public static readonly int NeighborAbsenceThresholdSeconds = 15;
        public static readonly int CostChangeThresholdMs = 50;
    }

    public enum PacketType
    {
        Hello = 0,
        Lsa = 1
    }

    class Router(string name)
    {
        public bool Disabled = false;
        public string Name = name;
        private int OwnSequenceNumber = 0;
        public HashSet<int> ActivePorts = [];
        public Dictionary<string, (int linkCost, DateTime lastSeen)> Neighbors = [];
        public Dictionary<string, (string nextHop, int totalCostMs)> Routes = [];
        public Dictionary<string, Dictionary<string, int>> Topology = [];
        public Dictionary<string, int> LatestSequences = [];
        public BlockingCollection<Packet> Inbox = [];
        public BlockingCollection<(int port, Packet packet)> Outbox = [];

        public void Run()
        {
            DateTime nextHello = DateTime.UtcNow;

            while (!Disabled)
            {
                if (Inbox.TryTake(out Packet? packet, Constants.pollingIntervalMs))
                {
                    switch (packet.Type)
                    {
                        case PacketType.Hello:
                            ProcessHello((HelloPacket)packet);
                            break;
                        case PacketType.Lsa:
                            ProcessLsa((LsaPacket)packet);
                            break;
                    }
                }

                if (DateTime.UtcNow >= nextHello)
                {
                    CheckDeadNeighbors();
                    SendHello();
                    nextHello = DateTime.UtcNow.AddSeconds(Constants.HelloIntervalSeconds);
                }
            }
        }

        private void CheckDeadNeighbors()
        {
            foreach (var neighbor in Neighbors.ToList())
            {
                if ((DateTime.UtcNow - neighbor.Value.lastSeen).TotalSeconds > Constants.NeighborAbsenceThresholdSeconds)
                {
                    Neighbors.Remove(neighbor.Key);
                    SendLSA();
                }
            }
        }

        private void SendHello()
        {
            foreach (int port in ActivePorts)
            {
                Packet packet = new HelloPacket(Name);
                Outbox.Add((port, packet));
            }
        }

        private void ProcessHello(HelloPacket packet)
        {
            int costMs = (int)(DateTime.UtcNow - packet.Timestamp).TotalMilliseconds;

            bool changed =
                !Neighbors.TryGetValue(packet.Source, out var old) ||
                Math.Abs(old.linkCost - costMs) > Constants.CostChangeThresholdMs;

            Neighbors[packet.Source] = (costMs, DateTime.UtcNow);

            if (changed)
            {
                SendLSA();
            }
        }

        private void SendLSA()
        {
            OwnSequenceNumber++; 

            var lsa = new LsaPacket(
                Name,
                OwnSequenceNumber,
                Neighbors.ToDictionary(n => n.Key, n => n.Value.linkCost)
            );

            foreach (int port in ActivePorts)
            {
                Outbox.Add((port, lsa));
            }
        }

        private void ProcessLsa(LsaPacket packet)
        {
            if (LatestSequences.TryGetValue(packet.Origin, out int oldSeq) &&
                oldSeq >= packet.SequenceNumber)
            {
                return;
            }

            LatestSequences[packet.Origin] = packet.SequenceNumber;
            Topology[packet.Origin] = new Dictionary<string, int>(packet.Links);

            RecalculateRoutes();
            foreach (int port in ActivePorts)
            {
                Outbox.Add((port, packet));
            }
        }

        private void RecalculateRoutes()
        {
            //djikstra to compute routes from topology
            var dist = new Dictionary<string, int>();
            var prev = new Dictionary<string, string?>();
            var pq = new SortedSet<(int cost, string node)>();

            foreach (var node in Topology.Keys)
            {
                dist[node] = int.MaxValue;
                prev[node] = null;
            }

            dist[Name] = 0;
            pq.Add((0, Name));

            while (pq.Count > 0)
            {
                var (cost, u) = pq.Min;
                pq.Remove(pq.Min);

                foreach (var (v, edgeCost) in Topology[u])
                {
                    int newCost = cost + edgeCost;

                    if (newCost < dist[v])
                    {
                        pq.Remove((dist[v], v));
                        dist[v] = newCost;
                        prev[v] = u;
                        pq.Add((newCost, v));
                    }
                }
            }

            Routes.Clear();

            foreach (var node in dist.Keys)
            {
                if (node == Name || dist[node] == int.MaxValue)
                    continue;

                string nextHop = node;
                while (prev[nextHop] != Name)
                    nextHop = prev[nextHop];

                Routes[node] = (nextHop, dist[node]);
            }
        }
    }


    class Link
    {
        public Link(Router router1, int port1, Router router2, int port2, int costMs)
        {
            r1 = router1;
            r1.ActivePorts.Add(port1);
            this.port1 = port1;
            r2 = router2;
            r2.ActivePorts.Add(port2);
            this.port2 = port2;
            this.costMs = costMs;
        }

        public Router r1;
        public int port1;
        public Router r2;
        public int port2;
        public int costMs;
    }

    class Network
    {
        public void AddRouter(string name)
        {
            if (routers.Any(r => r.Name == name))
            {
                Console.WriteLine($"Router with name {name} already exists.");
                return;
            }
            Router newRouter = new(name);
            newRouter.Run();
            routers.Add(newRouter);
        }

        public void RemoveRouter(string name)
        {
            Router? router = routers.FirstOrDefault(r => r.Name == name);
            if (router == null)
            {
                Console.WriteLine("Router not found.");
                return;
            }

            // Remove all links associated with router
            var linksToRemove = links.Where(l => l.r1 == router || l.r2 == router).ToList();
            foreach (var link in linksToRemove)
            {
                RemoveLink(link.r1.Name, link.port1);
            }
            routers.Remove(router);
        }

        public void AddLink(string routerName1, int port1, string routerName2, int port2, int costMs)
        {
            Router? r1 = routers.FirstOrDefault(r => r.Name == routerName1);
            Router? r2 = routers.FirstOrDefault(r => r.Name == routerName2);
            if (r1 == null)
            {
                Console.WriteLine("Router 1 not found.");
                return;
            }
            if (r2 == null)
            {
                Console.WriteLine("Router 2 not found.");
                return;
            }
            if (r1.ActivePorts.Contains(port1))
            {
                Console.WriteLine("Port 1 already occupied");
                return;
            }
            if (r2.ActivePorts.Contains(port2))
            {
                Console.WriteLine("Port 2 already occupied");
                return;
            }

            links.Add(new(r1, port1, r2, port2, costMs));
        }

        public void RemoveLink(string routerName, int port)
        {
            Link? link = links.FirstOrDefault(l =>
                l.r1.Name == routerName && l.r1.ActivePorts.Contains(port) ||
                l.r2.Name == routerName && l.r2.ActivePorts.Contains(port)
            );

            if (link == null)
            {
                Console.WriteLine("Link not found.");
                return;
            }

            link.r1.ActivePorts.Remove(link.port1);
            link.r2.ActivePorts.Remove(link.port2);
            links.Remove(link);
        }

        private void Forward(Router sender, int port, Packet packet)
        {
            var link = links.First(l =>
                (l.r1 == sender && l.port1 == port) ||
                (l.r2 == sender && l.port2 == port));

            Router target = link.r1 == sender ? link.r2 : link.r1;

            Task.Run(async () =>
            {
                await Task.Delay(link.costMs);
                target.Inbox.Add(packet);
            });
        }

        public void Monitor()
        {
            while (active)
            {
                foreach (var router in routers)
                {
                    if (router.Outbox.TryTake(out var item, 10))
                    {
                        Forward(router, item.port, item.packet);
                    }
                }
            }
        }

        public List<Router> routers = [];
        public List<Link> links = [];
        public bool active = true;
    }

    abstract class Packet(string source, PacketType type)
    {
        public DateTime Timestamp = DateTime.UtcNow;
        public string Source = source;
        public PacketType Type = type;
    }

    class HelloPacket(string source) : Packet(source, PacketType.Hello)
    {

    }

    class LsaPacket(string origin, int sequenceNumber, Dictionary<string, int> links)
    : Packet(origin, PacketType.Lsa)
    {
        public string Origin = origin;
        public int SequenceNumber = sequenceNumber;
        public Dictionary<string, int> Links = links;
    }


    class Program
    {
        static void Main()
        {
            Network net = new();
            Task.Run(net.Monitor);

            while (true)
            {
                Console.Write(">");
                string input = Console.ReadLine()!;
                if (input.Split(' ')[0] == "help")
                {
                    string help = File.ReadAllText($"{Directory.GetParent(Environment.CurrentDirectory)!.Parent!.Parent!.FullName}/help.txt");
                    Console.WriteLine(help);
                }
                else if (input.Split(' ')[0] == "conf")
                {
                    //conf router
                }
                else
                { 
                    Console.WriteLine("Unrecognized command. Type 'help' for a list of commands");
                    break;
                }

            }

            //net.AddRouter("A");
            //net.AddRouter("B");
            //net.AddRouter("C");
            //net.AddRouter("D");

            //net.AddLink("A", 1, "B", 1, 10);
        }
    }
}

