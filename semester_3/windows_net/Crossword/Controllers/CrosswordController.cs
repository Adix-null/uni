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

        [HttpPost("AddField")]
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

        [HttpDelete("RemoveField")]
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

        [HttpPut("ResetCrossword")]
        public IActionResult ResetCrossword()
        {
            var fields = _context.Fields.ToList();
            foreach (var field in fields)
            {
                field.Completed = false;
                SyncIntersections(9, 6, '\u0160');
            }
            _context.SaveChanges();
            return Ok();
        }

        [HttpGet("PrintCrossword")]
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
                    Square ts = field.Squares[i];
                    char guessChar = field.Guesses[i];
                    grid[ts.Y - minY, ts.X - minX] = guessChar != ' ' ? guessChar : 'O';
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

        [HttpPost("guess/ManualGuess")]
        public IActionResult ManualGuess(int fieldId, string word)
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
            for (int i = 0; i < ((List<char>)[.. word.Take(field.Length)]).Count; i++)
            {
                SyncIntersections(field.Squares[i].X, field.Squares[i].Y, field.Guesses[i]);
            }
            field.Completed = true;

            _context.SaveChanges();
            return Ok(field);
        }

        private void SyncIntersections(int x, int y, char c)
        {
            var intersectingFields = _context.Fields.AsEnumerable()
                .Where(f => f.Squares.Any(sq => sq.X == x && sq.Y == y) && !f.Completed)
                .ToList();
            foreach (var field in intersectingFields)
            {
                List<char> tmpList = [];

                foreach (Square s in field.Squares)
                {
                    tmpList.Add(s.X == x && s.Y == y ? c : ' ');
                }
                field.Guesses = tmpList;
            }
        }

        [HttpPost("guess/NextGuess")]
        public IActionResult NextGuess()
        {
            var field = _context.Fields.AsEnumerable().First(f => f.Guesses.Any(c => c != ' ') && !f.Completed);
            if (field == null)
            {
                return NotFound("Field not found");
            }
            var validWords = _context.Words.Where(w => w.Length == field.Length &&
                (field.Guesses[0] == ' ' || w.C1 == field.Guesses[0]) &&
                (field.Guesses[1] == ' ' || w.C2 == field.Guesses[1]) &&
                (field.Guesses[2] == ' ' || w.C3 == field.Guesses[2]) &&
                (field.Guesses[3] == ' ' || w.C4 == field.Guesses[3]) &&
                (field.Guesses.Count < 5 || (field.Guesses[4] == ' ' || w.C5 == field.Guesses[4])) &&
                (field.Guesses.Count < 6 || (field.Guesses[5] == ' ' || w.C6 == field.Guesses[5])) &&
                (field.Guesses.Count < 7 || (field.Guesses[6] == ' ' || w.C7 == field.Guesses[6])) &&
                (field.Guesses.Count < 8 || (field.Guesses[7] == ' ' || w.C8 == field.Guesses[7])) &&
                (field.Guesses.Count < 9 || (field.Guesses[8] == ' ' || w.C9 == field.Guesses[8]))
            ).ToList();

            if (validWords.Count == 0)
            {
                return NotFound("No valid words found");
            }
            ManualGuess(field.ID, validWords[0].Strword);

            _context.SaveChanges();
            return Ok(validWords);
        }
    }
}
