using Npgsql;
using Microsoft.Extensions.Configuration;

try
{
    var config = new ConfigurationBuilder()
    .AddJsonFile("appsettings.json", optional: false, reloadOnChange: true)
    .Build();

    string? connString = config["Postgres"] ?? throw new Exception("Connection string not found.");

    await using var conn = new NpgsqlConnection(connString);
    await conn.OpenAsync();

    await using var cmd = new NpgsqlCommand("""SELECT ak FROM stud.skaitytojas ORDER BY pavarde DESC;""", conn);
    await using var reader = await cmd.ExecuteReaderAsync();
    while (await reader.ReadAsync())
        Console.WriteLine(reader.GetString(0));
}
catch (Exception ex)
{
    Console.WriteLine(ex.Message);
}