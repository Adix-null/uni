using Microsoft.Extensions.Configuration;
using Npgsql;
using System.Reflection;

try
{
    var config = new ConfigurationBuilder()
    .AddJsonFile("appsettings.json", optional: false, reloadOnChange: true)
    .Build();

    string? connString = config["Postgres"] ?? throw new Exception("Connection string not found.");

    Console.WriteLine("Connecting...");
    await using var conn = new NpgsqlConnection(connString);
    await conn.OpenAsync();

    var exeDir = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location)!;
    var sqlPath = Path.Combine(exeDir, "queries", "studentu_test.sql");

    string sql = File.ReadAllText(sqlPath);

    await using var cmd = new NpgsqlCommand(sql, conn);
    await using var reader = await cmd.ExecuteReaderAsync();

    do
    {
        tablePrint(reader);
    } 
    while (await reader.NextResultAsync());
}
catch (Exception ex)
{
    Console.WriteLine(ex.Message);
}

async void tablePrint(NpgsqlDataReader reader)
{
    List<string> columnNames = Enumerable.Range(0, reader.FieldCount).Select(reader.GetName).ToList();
    List<int> columnWidths = columnNames.Select(n => n.Length).ToList();

    List<List<string>> rows = [];
    while (await reader.ReadAsync())
    {
        List<string> row = [];
        for (int i = 0; i < reader.FieldCount; i++)
        {
            row.Add(reader.GetValue(i)?.ToString() ?? "");
            columnWidths[i] = Math.Max(columnWidths[i], row[i].ToString()!.Length);
        }
        rows.Add(row);
    }

    string separator = "+" + string.Join("+", columnWidths.Select(w => new string('-', w + 2))) + "+";

    // print header
    Console.WriteLine(separator);
    Console.WriteLine("| " + string.Join(" | ", columnNames.Select((n, i) => n.PadRight(columnWidths[i]))) + " |");
    Console.WriteLine(separator);

    // print rows
    foreach (var row in rows)
    {
        Console.WriteLine("| " + string.Join(" | ", row.Select((v, i) => v.ToString()!.PadRight(columnWidths[i]))) + " |");
    }
    Console.WriteLine(separator);
}