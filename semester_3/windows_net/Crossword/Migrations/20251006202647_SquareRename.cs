using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace Crossword.Migrations
{
    /// <inheritdoc />
    public partial class SquareRename : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DeleteData(
                table: "Fields",
                keyColumn: "ID",
                keyValue: 1);

            migrationBuilder.AddColumn<int>(
                name: "Length",
                table: "Fields",
                type: "integer",
                nullable: false,
                defaultValue: 0);
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "Length",
                table: "Fields");

            migrationBuilder.InsertData(
                table: "Fields",
                columns: new[] { "ID", "Completed", "Guesses", "Squares" },
                values: new object[] { 1, false, "[\"\\u0160\",\" \",\" \",\" \"]", "[{\"Item1\":9,\"Item2\":6},{\"Item1\":10,\"Item2\":6},{\"Item1\":11,\"Item2\":6},{\"Item1\":12,\"Item2\":6}]" });
        }
    }
}
