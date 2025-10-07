using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

#pragma warning disable CA1814 // Prefer jagged arrays over multidimensional

namespace Crossword.Migrations
{
    /// <inheritdoc />
    public partial class SeedFields : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.InsertData(
                table: "Fields",
                columns: new[] { "ID", "Completed", "Guesses", "Length", "Squares" },
                values: new object[,]
                {
                    { 1, false, "[\" \",\" \",\" \",\" \",\" \",\" \",\" \",\" \",\" \"]", 9, "[{\"X\":0,\"Y\":2},{\"X\":1,\"Y\":2},{\"X\":2,\"Y\":2},{\"X\":3,\"Y\":2},{\"X\":4,\"Y\":2},{\"X\":5,\"Y\":2},{\"X\":6,\"Y\":2},{\"X\":7,\"Y\":2},{\"X\":8,\"Y\":2}]" },
                    { 2, false, "[\" \",\" \",\" \",\" \"]", 4, "[{\"X\":10,\"Y\":2},{\"X\":11,\"Y\":2},{\"X\":12,\"Y\":2},{\"X\":13,\"Y\":2}]" },
                    { 3, false, "[\" \",\" \",\" \",\" \",\" \",\" \",\" \"]", 7, "[{\"X\":5,\"Y\":4},{\"X\":6,\"Y\":4},{\"X\":7,\"Y\":4},{\"X\":8,\"Y\":4},{\"X\":9,\"Y\":4},{\"X\":10,\"Y\":4},{\"X\":11,\"Y\":4}]" },
                    { 4, false, "[\" \",\" \",\" \",\" \",\" \",\" \"]", 6, "[{\"X\":2,\"Y\":6},{\"X\":3,\"Y\":6},{\"X\":4,\"Y\":6},{\"X\":5,\"Y\":6},{\"X\":6,\"Y\":6},{\"X\":7,\"Y\":6}]" },
                    { 5, false, "[\" \",\" \",\" \",\" \"]", 4, "[{\"X\":9,\"Y\":6},{\"X\":10,\"Y\":6},{\"X\":11,\"Y\":6},{\"X\":12,\"Y\":6}]" },
                    { 6, false, "[\" \",\" \",\" \",\" \",\" \",\" \",\" \",\" \",\" \"]", 9, "[{\"X\":3,\"Y\":8},{\"X\":4,\"Y\":8},{\"X\":5,\"Y\":8},{\"X\":6,\"Y\":8},{\"X\":7,\"Y\":8},{\"X\":8,\"Y\":8},{\"X\":9,\"Y\":8},{\"X\":10,\"Y\":8},{\"X\":11,\"Y\":8}]" },
                    { 7, false, "[\" \",\" \",\" \",\" \"]", 4, "[{\"X\":4,\"Y\":6},{\"X\":4,\"Y\":7},{\"X\":4,\"Y\":8},{\"X\":4,\"Y\":9}]" },
                    { 8, false, "[\" \",\" \",\" \",\" \",\" \",\" \",\" \",\" \",\" \"]", 9, "[{\"X\":7,\"Y\":0},{\"X\":7,\"Y\":1},{\"X\":7,\"Y\":2},{\"X\":7,\"Y\":3},{\"X\":7,\"Y\":4},{\"X\":7,\"Y\":5},{\"X\":7,\"Y\":6},{\"X\":7,\"Y\":7},{\"X\":7,\"Y\":8}]" },
                    { 9, false, "[\" \",\" \",\" \",\" \",\" \",\" \",\" \",\" \",\" \"]", 9, "[{\"X\":11,\"Y\":1},{\"X\":11,\"Y\":2},{\"X\":11,\"Y\":3},{\"X\":11,\"Y\":4},{\"X\":11,\"Y\":5},{\"X\":11,\"Y\":6},{\"X\":11,\"Y\":7},{\"X\":11,\"Y\":8},{\"X\":11,\"Y\":9}]" },
                    { 10, false, "[\" \",\" \",\" \",\" \",\" \",\" \"]", 6, "[{\"X\":9,\"Y\":4},{\"X\":9,\"Y\":5},{\"X\":9,\"Y\":6},{\"X\":9,\"Y\":7},{\"X\":9,\"Y\":8},{\"X\":9,\"Y\":9}]" }
                });
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DeleteData(
                table: "Fields",
                keyColumn: "ID",
                keyValue: 1);

            migrationBuilder.DeleteData(
                table: "Fields",
                keyColumn: "ID",
                keyValue: 2);

            migrationBuilder.DeleteData(
                table: "Fields",
                keyColumn: "ID",
                keyValue: 3);

            migrationBuilder.DeleteData(
                table: "Fields",
                keyColumn: "ID",
                keyValue: 4);

            migrationBuilder.DeleteData(
                table: "Fields",
                keyColumn: "ID",
                keyValue: 5);

            migrationBuilder.DeleteData(
                table: "Fields",
                keyColumn: "ID",
                keyValue: 6);

            migrationBuilder.DeleteData(
                table: "Fields",
                keyColumn: "ID",
                keyValue: 7);

            migrationBuilder.DeleteData(
                table: "Fields",
                keyColumn: "ID",
                keyValue: 8);

            migrationBuilder.DeleteData(
                table: "Fields",
                keyColumn: "ID",
                keyValue: 9);

            migrationBuilder.DeleteData(
                table: "Fields",
                keyColumn: "ID",
                keyValue: 10);
        }
    }
}
