class Router(string name)
{
    public string Name { get; set; } = name;
    public List<(Router router, int cost)> Neighbors { get; set; } = [];
    public Dictionary<string, (string NextHop, int totalCost)> Routes { get; set; } = [];

    public void AddNeighbor(Router neighbor, int cost)
    {
        if (!Neighbors.Any(n => n.router == neighbor))
        {
            Neighbors.Add((neighbor, cost));
            neighbor.AddNeighbor(this, cost);
        }
    }
    public void RemoveNeighbour(Router neighbor)
    {
        Neighbors.RemoveAll(n => n.router == neighbor);
        neighbor.RemoveNeighbour(this);
    }
}

class Program
{
    static void Main(string[] args)
    {
        Console.WriteLine("test");

    }
}
