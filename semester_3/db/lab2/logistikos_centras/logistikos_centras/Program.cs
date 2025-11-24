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
    Console.WriteLine("Succesfully connected");

    bool succeeded = false;
    int n;
    while (true)
    {
        do
        {
            Console.WriteLine(
                """
                
                Options: 
                0) Test
                1) Init DB
                2) Seed data
                3) View all tables
                4) Nuke  
                """);
            bool success = int.TryParse(Console.ReadLine(), out n);

            succeeded = success && n >= 0 & n <= 4;
        }
        while (!succeeded);
    
        switch (n)
        {
            case 0:
                {
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

                    break;
                }
            case 1:
                {
                    var exeDir = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location)!;
                    var sqlPath = Path.Combine(exeDir, "queries", "init.sql");
                    string sql = File.ReadAllText(sqlPath);

                    await using var cmd = new NpgsqlCommand(sql, conn);
                    await using var reader = await cmd.ExecuteReaderAsync();

                    break;
                }
            case 2:
                {
                    var exeDir = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location)!;
                    var sqlPath = Path.Combine(exeDir, "queries", "seed.sql");
                    string sql = File.ReadAllText(sqlPath);

                    await using var cmd = new NpgsqlCommand(sql, conn);
                    await using var reader = await cmd.ExecuteReaderAsync();

                    Console.WriteLine("Records affected: " + reader.RecordsAffected);
                    break;
                }
            case 3:
                {
                    var exeDir = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location)!;
                    var sqlPath = Path.Combine(exeDir, "queries", "select_personal_tables.sql");
                    string sql = File.ReadAllText(sqlPath);

                    await using var cmd = new NpgsqlCommand(sql, conn);
                    await using var reader = await cmd.ExecuteReaderAsync();

                    List<string> tableNames = [];
                    await using (cmd)
                    await using (reader)
                    {
                        while (await reader.ReadAsync())
                            tableNames.Add(reader.GetString(0));
                    }

                    foreach (var table in tableNames)
                    {
                        Console.WriteLine($"{table}:");
                        string sqlc = $"SELECT * FROM {table};";
                        await using var cmdc = new NpgsqlCommand(sqlc, conn);
                        await using var readerc = await cmdc.ExecuteReaderAsync();

                        do
                        {
                            tablePrint(readerc);
                        }
                        while (await readerc.NextResultAsync());
                    }

                    break;
                }
            case 4:
                {
                    var exeDir = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location)!;
                    var sqlPath = Path.Combine(exeDir, "queries", "select_personal_tables.sql");
                    string sql = File.ReadAllText(sqlPath);

                    await using var cmd = new NpgsqlCommand(sql, conn);
                    await using var reader = await cmd.ExecuteReaderAsync();

                    List<string> tableNames = [];
                    await using (cmd)
                    await using (reader)
                    {
                        while (await reader.ReadAsync())
                            tableNames.Add(reader.GetString(0));
                    }

                    foreach (var table in tableNames)
                    {
                        Console.WriteLine($"Deleting {table}");
                        string sqld = $"DROP TABLE {table} CASCADE;";
                        await using var cmdd = new NpgsqlCommand(sqld, conn);
                        await cmdd.ExecuteNonQueryAsync();
                    }

                    break;
                }
        }
    }

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