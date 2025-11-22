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
    var sqlPath = Path.Combine(exeDir, "queries", "query.sql");

    string sql = File.ReadAllText(sqlPath);
    //string sql = """SELECT ak FROM stud.skaitytojas ORDER BY pavarde DESC;""";

    await using var cmd = new NpgsqlCommand(sql, conn);
    await using var reader = await cmd.ExecuteReaderAsync();
    while (await reader.ReadAsync())
        Console.WriteLine(reader.GetString(0));
}
catch (Exception ex)
{
    Console.WriteLine(ex.Message);
}