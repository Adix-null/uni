using Crossword.Data;
using Crossword.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore.Storage;
using System;

namespace Crossword.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class CrosswordController(CrosswordDbContext context, ILogger<CrosswordController> logger) : ControllerBase
    {
        private readonly ILogger<CrosswordController> _logger = logger;
        private readonly CrosswordDbContext _context = context;

        [HttpPost(Name = "AddField")]
        public IActionResult AddField(int x_start, int y_start, int length, int direction)
        {
            if (length <= 0)
            {
                return BadRequest("Invalid length");
            }

            int dx = 0, dy = 0;
            switch (direction)
            {
                case 0: dx = 0; dy = -1; break; // North
                case 1: dx = 1; dy = 0; break; // East
                case 2: dx = 0; dy = 1; break; // South
                case 3: dx = -1; dy = 0; break; // West
                default: return BadRequest("Invalid direction");
            }

            var squares = new List<Square>();
            var guesses = new List<char>();
            for (int i = 0; i < length; i++)
            {
                guesses.Add(' ');
                squares.Add(new(x_start + i * dx, y_start + i * dy));
            }

            Field newField = new()
            {
                Squares = squares,
                Guesses = guesses,
                Length = length,
                Completed = false
            };
            _context.Fields.Add(newField);
            _context.SaveChanges();
            return Ok(newField);
        }

        [HttpGet(Name = "PrintCrossword")]
        public IActionResult PrintCrossword()
        {
            var fields = _context.Fields.ToList();
            if (fields.Count == 0)
            {
                return Ok("No fields available.");
            }
            int minX = fields.SelectMany(f => f.Squares).Min(sq => sq.X);
            int maxX = fields.SelectMany(f => f.Squares).Max(sq => sq.X);
            int minY = fields.SelectMany(f => f.Squares).Min(sq => sq.Y);
            int maxY = fields.SelectMany(f => f.Squares).Max(sq => sq.Y);
            int width = maxX - minX + 1;
            int height = maxY - minY + 1;

            char[,] grid = new char[height, width];
            for (int i = 0; i < height; i++)
                for (int j = 0; j < width; j++)
                    grid[i, j] = ' ';

            foreach (var field in fields)
            {
                for (int i = 0; i < field.Length; i++)
                {
                    var (x, y) = field.Squares[i];
                    char guessChar = field.Guesses[i];
                    grid[y - minY, x - minX] = guessChar != ' ' ? guessChar : 'O';
                }
            }
            var result = new System.Text.StringBuilder();
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    result.Append(grid[i, j]);
                }
                result.AppendLine();
            }
            return Ok(result.ToString());
        }
    }
}
