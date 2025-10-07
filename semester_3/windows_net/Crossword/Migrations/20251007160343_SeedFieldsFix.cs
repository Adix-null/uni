using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace Crossword.Migrations
{
    /// <inheritdoc />
    public partial class SeedFieldsFix : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.UpdateData(
                table: "Fields",
                keyColumn: "ID",
                keyValue: 9,
                columns: new[] { "Guesses", "Length", "Squares" },
                values: new object[] { "[\" \",\" \",\" \",\" \",\" \",\" \"]", 6, "[{\"X\":9,\"Y\":4},{\"X\":9,\"Y\":5},{\"X\":9,\"Y\":6},{\"X\":9,\"Y\":7},{\"X\":9,\"Y\":8},{\"X\":9,\"Y\":9}]" });

            migrationBuilder.UpdateData(
                table: "Fields",
                keyColumn: "ID",
                keyValue: 10,
                columns: new[] { "Guesses", "Length", "Squares" },
                values: new object[] { "[\" \",\" \",\" \",\" \",\" \",\" \",\" \",\" \",\" \"]", 9, "[{\"X\":11,\"Y\":1},{\"X\":11,\"Y\":2},{\"X\":11,\"Y\":3},{\"X\":11,\"Y\":4},{\"X\":11,\"Y\":5},{\"X\":11,\"Y\":6},{\"X\":11,\"Y\":7},{\"X\":11,\"Y\":8},{\"X\":11,\"Y\":9}]" });
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.UpdateData(
                table: "Fields",
                keyColumn: "ID",
                keyValue: 9,
                columns: new[] { "Guesses", "Length", "Squares" },
                values: new object[] { "[\" \",\" \",\" \",\" \",\" \",\" \",\" \",\" \",\" \"]", 9, "[{\"X\":11,\"Y\":1},{\"X\":11,\"Y\":2},{\"X\":11,\"Y\":3},{\"X\":11,\"Y\":4},{\"X\":11,\"Y\":5},{\"X\":11,\"Y\":6},{\"X\":11,\"Y\":7},{\"X\":11,\"Y\":8},{\"X\":11,\"Y\":9}]" });

            migrationBuilder.UpdateData(
                table: "Fields",
                keyColumn: "ID",
                keyValue: 10,
                columns: new[] { "Guesses", "Length", "Squares" },
                values: new object[] { "[\" \",\" \",\" \",\" \",\" \",\" \"]", 6, "[{\"X\":9,\"Y\":4},{\"X\":9,\"Y\":5},{\"X\":9,\"Y\":6},{\"X\":9,\"Y\":7},{\"X\":9,\"Y\":8},{\"X\":9,\"Y\":9}]" });
        }
    }
}
