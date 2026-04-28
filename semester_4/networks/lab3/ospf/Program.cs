

class Router(string name)
{
    public string Name { get; set; } = name;
    public HashSet<int> ActivePorts { get; set; } = [];
    public Dictionary<Router, int> Neighbors { get; set; } = [];
    public Dictionary<string, (string NextHop, int totalCost)> Routes { get; set; } = [];

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


class Program
{
    static void Main()
    {
        

        //net.AddRouter("A");
        //net.AddRouter("B");
        //net.AddRouter("C");
        //net.AddRouter("D");

        //net.AddLink("A", 1, "B", 1, 10);
    }
}


