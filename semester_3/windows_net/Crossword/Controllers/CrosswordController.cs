using Crossword.Data;
using Crossword.Methods;
using Crossword.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore.Storage;
using System;
using System.Text.Json;

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

            //if (x_start + dx * (length - 1) < 0 || y_start + dy * (length - 1) < 0)
            //{
            //    return BadRequest("negative positions forbidden");
            //}

            Field newField = new()
            {
                Squares = Generator.GenerateSquares(x_start, y_start, length, direction),
                Guesses = [.. Enumerable.Repeat(' ', 7)],
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
            return NoContent();
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

        private void GetNextGuess(ref List<Guess> gc, ref List<Field> fields)
        {
            var field = fields.AsEnumerable()
                .Where(f => f.Guesses.Any(c => c != ' ') && !f.Completed)
                .OrderBy(f => f.ID)
                .FirstOrDefault();

            if (field == null)
                return;

            //CS1628 otherwise
            var gcLocal = gc.ToList();

            var validWords = _context.Words.Where(w => w.Length == field.Length &&
                gcLocal.All(g => g.Word != w.Strword) &&
                (field.Guesses[0] == ' ' || w.C1 == field.Guesses[0]) &&
                (field.Guesses[1] == ' ' || w.C2 == field.Guesses[1]) &&
                (field.Guesses[2] == ' ' || w.C3 == field.Guesses[2]) &&
                (field.Guesses[3] == ' ' || w.C4 == field.Guesses[3]) &&
                (field.Guesses.Count < 5 || (field.Guesses[4] == ' ' || w.C5 == field.Guesses[4])) &&
                (field.Guesses.Count < 6 || (field.Guesses[5] == ' ' || w.C6 == field.Guesses[5])) &&
                (field.Guesses.Count < 7 || (field.Guesses[6] == ' ' || w.C7 == field.Guesses[6])) &&
                (field.Guesses.Count < 8 || (field.Guesses[7] == ' ' || w.C8 == field.Guesses[7])) &&
                (field.Guesses.Count < 9 || (field.Guesses[8] == ' ' || w.C9 == field.Guesses[8]))
            ).OrderBy(w => w.Strword).ToList();

            if (fields.Where(f => !f.Completed).Any(fl => _context.Words.Where(
                w => w.Length == fl.Length &&
                gcLocal.All(g => g.Word != w.Strword) &&
                (fl.Guesses[0] == ' ' || w.C1 == fl.Guesses[0]) &&
                (fl.Guesses[1] == ' ' || w.C2 == fl.Guesses[1]) &&
                (fl.Guesses[2] == ' ' || w.C3 == fl.Guesses[2]) &&
                (fl.Guesses[3] == ' ' || w.C4 == fl.Guesses[3]) &&
                (fl.Guesses.Count < 5 || (fl.Guesses[4] == ' ' || w.C5 == fl.Guesses[4])) &&
                (fl.Guesses.Count < 6 || (fl.Guesses[5] == ' ' || w.C6 == fl.Guesses[5])) &&
                (fl.Guesses.Count < 7 || (fl.Guesses[6] == ' ' || w.C7 == fl.Guesses[6])) &&
                (fl.Guesses.Count < 8 || (fl.Guesses[7] == ' ' || w.C8 == fl.Guesses[7])) &&
                (fl.Guesses.Count < 9 || (fl.Guesses[8] == ' ' || w.C9 == fl.Guesses[8]))
            ).ToList().Count == 0))
            {
                removeGuess(field.ID);
                gc.RemoveAt(gc.Count - 1);
                return;
            }

            foreach (var w in validWords)
            {
                Guess guess = new(field.ID, w.Strword);
                gc.Add(guess);

                if (guess.Word.Length != field.Length)
                    throw new Exception($"'{guess.Word}' length does not match field length {field.Length}");
                for (int i = 0; i < field.Guesses.Count; i++)
                {
                    if (field.Guesses[i] != ' ' && guess.Word[i] != field.Guesses[i])
                    {
                        throw new Exception($"'{guess.Word}' does not match at index {i} for word {field.Guesses}");
                    }
                }

                for (int i = 0; i < ((List<char>)[.. guess.Word.Take(field.Length)]).Count; i++)
                {
                    SyncIntersections(field.Squares[i].X, field.Squares[i].Y, field.Guesses[i]);
                }
                field.Completed = true;
                GetNextGuess(ref gc, ref fields);
            }

            return;
        }

        private void removeGuess(int fieldID)
        {

        }

        [HttpGet("AutoSolve")]
        public IActionResult AutoSolve()
        {
            var fields = _context.Fields.ToList();
            List<Guess> gc = [];
            GetNextGuess(ref gc, ref fields);
            foreach (var guess in gc)
            {
                Console.WriteLine($"{guess.FieldId} {guess.Word}");
            }
            //while (!_context.Fields.All(f => !f.Completed))
            //{
            //}
            //_context.GuessChains.Add(gc);
            _context.SaveChanges();
            return Ok();
        }

        [HttpGet("CheckSolved")]
        public IActionResult CheckSolved()
        {
            var solution = _context.GuessChains.First(g => g.Guesses.Count == 10);
            if (solution != null)
            {
                return Ok(solution);
            }
            else
            {
                return NotFound("No solution found");
            }
        }
    }
}
