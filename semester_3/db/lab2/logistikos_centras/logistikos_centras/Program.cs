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
                
                Pasirinkimai: 
                1)  Sukurti DB
                2)  Įdėti pradinius duomenis
                3)  Peržiūrėti visas lenteles
                4)  Ištrinti visas lenteles
                
                10) Sukurti naują paketą 
                11) Sukurti naują prekę
                12) Įvykdyti naują žingsnį

                20) Pristatytų paketų informacija
                21) Surasti prekę(s) pagal pavadinimą
                22) Rodyti kompanijos pagal pavadinimą gabenamus paketus
                23) Filtruoti paketus pagal sukūrimo datą

                30) Pakeisti prekės pavadinimą
                31) Pakeisti prekių kiekį pakete
                32) Įvertinti atkeliavusį paketą

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

                    foreach (string table in tableNames)
                    {
                        await DisplayTable(table, conn);
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

            case 10:
                {
                    string kilmes_salis = prompt<string>("Kilmės šalies kodas (ISO-3166-1)", x => x.Length == 2 && x.All(x => x >= 'A' && x <= 'Z'));
                    string galutinis_tikslas = prompt<string>("Galutinis tikslas", x => x.Length < 65);
                    await DisplayTable("kompanija", conn);
                    string kompanija = prompt<string>("Kompanijos pavadinimas", x => x.Length < 65);

                    await ProceedWithQuery(conn, "create/create_packet.sql", new()
                    {
                        ["kilmes_salis"] = kilmes_salis,
                        ["galutinis_tikslas"] = galutinis_tikslas,
                        ["kompanija"] = kompanija
                    }, "Paketas sukurtas sėkmingai", new() { [23503] = "kompanija su duotu pavadinimu neegzistuoja" });

                    break;
                }
            case 11:
                {
                    string pavadinimas = prompt<string>("Prekės pavadinimas", x => x.Length < 65);
                    decimal svoris_kg = prompt<decimal>("Prekės svoris (kg)", x => x > 0);
                    decimal kaina_eur = prompt<decimal>("Prekės kaina (eur)", x => x > 0);
                    await ProceedWithQuery(conn, "create/create_item.sql", new()
                    {
                        ["pavadinimas"] = pavadinimas,
                        ["svoris_kg"] = svoris_kg,
                        ["kaina_eur"] = kaina_eur
                    }, "Prekė sukurta sėkmingai", null);
                    break;
                }
            case 12:
                {
                    await DisplayTable("paketas", conn);
                    int id = prompt<int>("Paketo ID", _ => true);
                    await DisplayTable("zingsnis", conn, new ("paketo_id", id));
                    string tikslas_is = prompt<string>("Tikslas iš", x => x.Length < 65);
                    string tikslas_i = prompt<string>("Tikslas į", x => x.Length < 65);

                    await ProceedWithQuery(conn, "create/new_step.sql", new()
                    {
                        ["id"] = id,
                        ["tikslas_is"] = tikslas_is,
                        ["tikslas_i"] = tikslas_i
                    }, "Žingsnis įvykdytas", null);
                    break;
                }

            case 20:
                {
                    //await ProceedWithQuery(conn, "read/packet_info.sql", null, "tr", null);
                    await DisplayTable("paketu_ataskaita", conn);
                    break;
                }
            case 21:
                {
                    string pavadinimas = prompt<string>("Pavadinimas ar jo dalis", x => x.Length < 65);
                    await ProceedWithQuery(conn, "read/search_item_by_name.sql", new()
                    {
                        ["pavadinimas"] = pavadinimas
                    }, "", null, true);
                    break;
                }
            case 22:
                {
                    await DisplayTable("kompanija", conn);
                    string pavadinimas = prompt<string>("Kompanijos pavadinimas", x => x.Length < 65);
                    await ProceedWithQuery(conn, "read/search_packets_by_company_name.sql", new()
                    {
                        ["pavadinimas"] = pavadinimas
                    }, "Rodomi visi kompanijos gabenami paketai", null, true);
                    break;
                }
            case 23:
                {
                    DateTime data = prompt<DateTime>("Data vėliau nei YYYY-MM-DD", x => DateTime.Compare(DateTime.Today, x) > 0);
                    await ProceedWithQuery(conn, "read/search_packets_by_date.sql", new()
                    {
                        ["data"] = data
                    }, "", null, true);
                    break;
                }

            case 30:
                {
                    await DisplayTable("preke", conn);
                    int id = prompt<int>("Prekės ID", _ => true);
                    string naujas_pav = prompt<string>("Naujas pavadinimas", x => x.Length < 65);
                    await ProceedWithQuery(conn, "update/change_item_name.sql", new()
                    {
                        ["id"] = id,
                        ["pavadinimas"] = naujas_pav
                    }, "Pavadinimas sėkmingai pakeistas", null);

                    break;
                }
            case 31:
                {
                    await DisplayTable("paketas", conn);
                    int paketo_id = prompt<int>("Paketo ID", _ => true);
                    await DisplayTable("paketo_preke", conn, new ("paketo_id", paketo_id ));
                    int prekes_id = prompt<int>("Prekės ID", _ => true);
                    int naujas_kiekis = prompt<int>("Naujas kiekis", x => x > 0);
                    await ProceedWithQuery(conn, "update/change_item_amount.sql", new()
                    {
                        ["paketo_id"] = paketo_id,
                        ["prekes_id"] = prekes_id,
                        ["kiekis"] = naujas_kiekis
                    }, "Kiekis sėkmingai pakeistas", null);
                    break;
                }
            case 32:
                {
                    await DisplayTable("galutine_busena", conn);
                    int id = prompt<int>("Paketo ID", _ => true);
                    int busena = prompt<int>("Įvertinimas [1-5]", x => x >= 1 && x <= 5);
                    await ProceedWithQuery(conn, "update/rate_packet.sql", new()
                    {
                        ["id"] = id,
                        ["busena"] = busena
                    }, "Paketas sėkmingai įvertintas", null);

                    break;
                }

            case 40:
                {
                    await DisplayTable("paketas", conn);
                    int id = prompt<int>("Paketo ID", _ => true);

                    await ProceedWithQuery(conn, "delete/delete_packet.sql", new()
                    {
                        ["id"] = id
                    }, "Paketas ištrintas sėkmingai", null);

                    break;
                }
            case 41:
                {
                    await DisplayTable("preke", conn);
                    int id = prompt<int>("Prekės ID", _ => true);
                    await ProceedWithQuery(conn, "delete/delete_item.sql", new()
                    {
                        ["id"] = id
                    }, "Prekė ištrinta sėkmingai", null);
                    break;
                }
        }
    }

}
catch (Exception ex)
{
    Console.WriteLine(ex.Message);
}

T prompt<T>(string message, Func<T, bool> condition)
{
    T val = default!;
    bool correct = false;
    do
    {
        Console.WriteLine($"{message}:");
        string? input = Console.ReadLine()!;

        try
        {
            val = (T)Convert.ChangeType(input, typeof(T));
            correct = condition(val);
        }
        catch
        {
            correct = false;
        }

        if (!correct)
        {
            Console.WriteLine("Bloga įvestis");
        }
    } while (!correct);

    return val;
}

async Task<int> ProceedWithQuery(NpgsqlConnection conn, 
    string SQLfileDir, Dictionary<string, object>? userParams, string successMessage, Dictionary<int, string>? specificException, bool print = false)
{
    try
    {
        await ExecQueryAsync(conn, SQLfileDir, cmd =>
            {
                if(userParams == null) 
                    return;
                foreach (var entry in userParams)
                {
                    cmd.Parameters.AddWithValue($"p_{entry.Key}", entry.Value);
                }
            },
            handle: async reader =>
            {
                if(print)
                    do
                    {
                        tablePrint(reader);
                    }
                while (await reader.NextResultAsync());
                return true;
            }
        );
        Console.WriteLine(successMessage);
        return 0;
    }
    catch (Exception ex)
    {
        if (specificException != null)
        {
            foreach (var item in specificException)
            {
                if (ex is PostgresException pg && pg.SqlState == item.Key.ToString())
                {
                    Console.WriteLine($"Klaida, {item.Value}");
                    return item.Key;
                }
            }
        }

        Console.WriteLine($"Netikėta klaida: {ex.Message}");
        return -1;
    }
}

async Task<bool> DisplayTable(string tableName, NpgsqlConnection conn, Tuple<string, object>? where = null)
{
    var sql = where == null
    ? $"SELECT * FROM {tableName};"
    : $"SELECT * FROM {tableName} WHERE {where.Item1} = {where.Item2};";
    await ExecSqlTextAsync(conn, sql, async (cmd, readerc) =>
    {
        do
        {
            tablePrint(readerc);
        }
        while (await readerc.NextResultAsync());

        return true;
    });
    return false;
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