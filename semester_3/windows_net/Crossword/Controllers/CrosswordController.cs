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

            int dx, dy;
            switch (direction)
            {
                case 0: dx = 0; dy = -1; break; // North
                case 1: dx = 1; dy = 0; break; // East
                case 2: dx = 0; dy = 1; break; // South
                case 3: dx = -1; dy = 0; break; // West
                default: return BadRequest("Invalid direction");
            }
            //if (x_start + dx * (length - 1) < 0 || y_start + dy * (length - 1) < 0)
            //{
            //    return BadRequest("negative positions forbidden");
            //}

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

        [HttpDelete(Name = "RemoveField")]
        public IActionResult RemoveField(int fieldId)
        {
            var field = _context.Fields.Find(fieldId);
            if (field == null)
            {
                return NotFound("Field not found");
            }
            _context.Fields.Remove(field);
            _context.SaveChanges();
            return NoContent();
        }

        [HttpPut(Name = "ResetCrossword")]
        public IActionResult ResetCrossword()
        {
            //var fields = _context.Fields.ToList().Clear;
            AddField(0, 2, 9, 1);
            AddField(5, 4, 7, 1);
            AddField(2, 6, 6, 1);
            AddField(10, 2, 4, 1);
            AddField(3, 8, 9, 1);
            AddField(4, 6, 4, 1);
            AddField(7, 0, 9, 2);
            AddField(11, 1, 9, 2);
            AddField(9, 6, 4, 2);
            AddField(9, 4, 6, 2);
            _context.SaveChanges();
            return Ok();
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

        [HttpPost("MakeGuess")]
        public IActionResult MakeGuess(int fieldId, string word)
        {
            var field = _context.Fields.Find(fieldId);
            if (field == null)
            {
                return NotFound("Field not found");
            }
            if (word.Length != field.Length)
            {
                return BadRequest("Word length does not match field length");
            }
            for (int i = 0; i < field.Guesses.Count; i++)
            {
                if (field.Guesses[i] != ' ' && word[i] != field.Guesses[i])
                {
                    return BadRequest($"Guess does not match at index {i}");
                }
            }
            for (int i = 0; i < field.Guesses.Count; i++)
            {
                field.Guesses[i] = word[i];
            }

            _context.SaveChanges();
            return Ok(field);
        }
    }
}
