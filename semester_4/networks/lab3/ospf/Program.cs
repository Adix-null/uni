using System.Collections.Concurrent;
using System.Net.Sockets;

public enum PacketType
{
    Hello = 0,
    Lsa = 1
}

class Router(string name)
{
    public bool Disabled = false;
    public string Name { get; set; } = name;
    public HashSet<int> ActivePorts { get; set; } = [];
    public Dictionary<Router, int> Neighbors { get; set; } = [];
    public Dictionary<string, (string NextHop, int totalCost)> Routes { get; set; } = [];
    public BlockingCollection<Packet> Inbox { get; set; } = new();

    public void AddNeighbor(Router neighbor, int cost)
    {
        Neighbors[neighbor] = cost;
    }
    public void RemoveNeighbour(Router neighbor)
    {
        Neighbors.Remove(neighbor);
    }

    public void AddRoute(string destination, string nextHop, int totalCost)
    {
        Routes[destination] = (nextHop, totalCost);
    }

    public void RemoveRoute(string destination)
    {
        Routes.Remove(destination);
    }

    public static async Task SendPacket(Link link, Router from, Packet packet)
    {
        int delayMs = link.cost * 100;
        await Task.Delay(delayMs);

        Router target = link.r1 == from ? link.r2 : link.r1;
        target.Inbox.Add(packet);
    }

    private void Run()
    {
        DateTime nextHello = DateTime.UtcNow;

        while (!Disabled)
        {
            if (Inbox.TryTake(out Packet packet, 250))
            {
                ProcessPacket(packet);
            }

            if (DateTime.UtcNow >= nextHello)
            {
                SendHello();
                nextHello = DateTime.UtcNow.AddSeconds(5);
            }
        }
    }

    private void SendHello()
    {
        throw new NotImplementedException();
    }

    private void ProcessPacket(Packet packet)
    {
        switch (packet.Type)
        {
            case PacketType.Hello:
                ProcessHello(packet);
                break;
            case PacketType.Lsa:
                ProcessLsa(packet);
                break;
        }
    }

    private void ProcessHello(Packet packet)
    {
        throw new NotImplementedException();
    }

    private void ProcessLsa(Packet packet)
    {
        throw new NotImplementedException();
    }

}


class Link
{
    public Link(Router router1, int port1, Router router2, int port2, int cost)
    {
        r1 = router1;
        r1.ActivePorts.Add(port1);
        this.port1 = port1;
        r2 = router2; 
        r2.ActivePorts.Add(port2);
        this.port2 = port2;
        this.cost = cost;
    }

    public Router r1;
    public int port1;
    public Router r2;
    public int port2;
    public int cost;
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
        routers.Add(new Router(name));
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

    public void AddLink(string routerName1, int port1, string routerName2, int port2, int cost)
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

        links.Add(new(r1, port1, r2, port2, cost));
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

    public List<Router> routers = [];
    public List<Link> links = [];

}

struct Packet(string source, string destination, PacketType type, object? payload)
{
    public DateTime Timestamp = DateTime.UtcNow;
    public string Source = source;
    public string Destination = destination;
    public PacketType Type = type;
    public object? Payload = payload;
}

struct HelloPayload(string origin, List<string> neighborsSeen)
{
    public string Origin = origin;
    public List<string> NeighborsSeen = neighborsSeen;
}

class LsaPayload(string origin, int sequenceNumber, Dictionary<string, int> links)
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
        //multitheaded console and sim
        while (true)
        {
            
        }

        while (true)
        {
            Console.Write(">");
            string input = Console.ReadLine()!;
            switch (input)
            {
                case "help":
                    string help = File.ReadAllText($"{Directory.GetParent(Environment.CurrentDirectory)!.Parent!.Parent!.FullName}/help.txt");
                    Console.WriteLine(help);
                    break;
                default:
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


