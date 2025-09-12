namespace uninet
{
    internal class Program
    {
        static void f1(int x)
        {
            if (x == 1)
                Console.WriteLine("Vienas");
            else if (x == 2)
                Console.WriteLine("Du");
            else if (x == 3)
                Console.WriteLine("Trys");
        }
        static void f4(int x)
        {
            //Console.WriteLine(new string[]{"Vienas","Du","Trys"}[x-1]);
            //Console.WriteLine((string[])"Vienas\0Du\0Trys"[(x-1)+(x*2)]);
        }

        static void Main(string[] args)
        {
            int i;
            Int32.TryParse(Console.ReadLine(), out i);
            f4(i);
        }
    }
}
