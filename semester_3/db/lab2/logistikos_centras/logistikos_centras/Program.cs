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
                1)  Sukurti DB
                2)  Įdėti pradinius duomenis
                3)  Peržiūrėti visas lenteles
                4)  Ištrinti visas lenteles
                
                10) Sukurti naują paketą 
                11) Sukurti naują prekę
                12) Įvykdyti naują žingsnį

                20) Paketo informacija
                21) Surasti prekę(s) pagal pavadinimą
                22) Rodyti kompanijos pagal pavadinimą gabenamus paketus
                23) Filtruoti paketus pagal sukūrimo datą

                30) Pakeisti prekės pavadinimą
                31) Pakeisti prekių kiekį pakete

                40) Ištrinti paketą
                41) Ištrinti prekę
                """);
            bool success = int.TryParse(Console.ReadLine(), out n);

            succeeded = success && n >= 0;
        }
        while (!succeeded);
    
        switch (n)
        {
            case 1:
                {
                    await ExecQueryAsync<object?>(conn, "init.sql");

                    break;
                }
            case 2:
                {
                    await ExecQueryAsync<int?>(conn, "seed.sql", null, async reader =>
                        {
                            Console.WriteLine("Records affected: " + reader.RecordsAffected);
                            return reader.RecordsAffected;
                        });


                    break;
                }
            case 3:
                {
                    var tableNames = await ExecQueryAsync<List<string>>(conn, "select_personal_tables.sql", null, async reader =>
                    {
                        var names = new List<string>();
                        while (await reader.ReadAsync())
                            names.Add(reader.GetString(0));
                        return names;
                    }) ?? [];

                    foreach (var table in tableNames)
                    {
                        Console.WriteLine($"{table}:");
                        string sqlc = $"SELECT * FROM {table};";
                        await ExecSqlTextAsync(conn, sqlc, async (_, readerc) =>
                        {
                            do
                            {
                                tablePrint(readerc);
                            }
                            while (await readerc.NextResultAsync());

                            return true;
                        });
                    }

                    break;
                }
            case 4:
                {
                    var tableNames = await ExecQueryAsync(conn, "select_personal_tables.sql", null, async reader =>
                    {
                        var names = new List<string>();
                        while (await reader.ReadAsync())
                            names.Add(reader.GetString(0));
                        return names;
                    }) ?? [];

                    foreach (var table in tableNames)
                    {
                        Console.WriteLine($"Deleting {table}");
                        string sqld = $"DROP TABLE {table} CASCADE;";
                        await ExecSqlTextAsync(conn, sqld, async (_, _) => true);
                    }

                    break;
                }

            case 20:
                {
                    bool correct = false;
                    int id;
                    string sqlc = $"SELECT * FROM paketas;";
                    await ExecSqlTextAsync(conn, sqlc, async (_, readerc) =>
                    {
                        do
                        {
                            tablePrint(readerc);
                        }
                        while (await readerc.NextResultAsync());

                        return true;
                    });
                    do
                    {
                        Console.WriteLine("Paketo ID:");
                        bool success = int.TryParse(Console.ReadLine(), out id);

                        correct = success;

                        if(!correct)
                        {
                            Console.WriteLine("Įvestis ne skaičius, bandykite dar kartą");
                        }
                    } while (!correct);

                    await ExecQueryAsync(conn, "read/packet_info.sql", cmd =>
                         {
                             cmd.Parameters.AddWithValue("p_id", id);
                         },
                         handle: async reader =>
                         {
                             do
                             {
                                 tablePrint(reader);
                             }
                             while (await reader.NextResultAsync());
                             return true;
                         }
                     );


                    break;
                }
        }
    }

}
catch (Exception ex)
{
    Console.WriteLine(ex.Message);
}

async Task<T?> ExecQueryAsync<T>(
    NpgsqlConnection conn,
    string fileName,
    Action<NpgsqlCommand>? setup = null,
    Func<NpgsqlDataReader, Task<T?>>? handle = null)
{
    var exeDir = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location)!;
    var sqlPath = Path.Combine(exeDir, "queries", fileName);
    string sql = File.ReadAllText(sqlPath);

    await using var cmd = new NpgsqlCommand(sql, conn);

    // Add parameters BEFORE execution
    setup?.Invoke(cmd);

    await using var reader = await cmd.ExecuteReaderAsync();

    if (handle != null)
        return await handle(reader);

    return default;
}


async Task<T?> ExecSqlTextAsync<T>(NpgsqlConnection conn, string sql, Func<NpgsqlCommand, NpgsqlDataReader, Task<T?>>? handler = null)
{
    await using var cmd = new NpgsqlCommand(sql, conn);
    await using var reader = await cmd.ExecuteReaderAsync();

    if (handler != null)
        return await handler(cmd, reader);

    return default;
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