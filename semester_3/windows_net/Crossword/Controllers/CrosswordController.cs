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
                SyncIntersections(ref fields, 9, 6, '\u0160');
            }
            _context.SaveChanges();
            return NoContent();
        }

        //[HttpGet("PrintCrossword")]
        //public IActionResult PrintCrossword()
        //{
        //    var fields = _context.Fields.ToList();
        //    List<string> result = VisualizeCrossword(fields, ' ', 'X');
        //    return Ok(result.ToString());
        //}

        private static List<string> VisualizeCrossword(List<Field> fields, char filler, char unknown)
        {
            if (fields.Count == 0)
                return ["No fields to display"];
            int minX = fields.SelectMany(f => f.Squares).Min(sq => sq.X);
            int maxX = fields.SelectMany(f => f.Squares).Max(sq => sq.X);
            int minY = fields.SelectMany(f => f.Squares).Min(sq => sq.Y);
            int maxY = fields.SelectMany(f => f.Squares).Max(sq => sq.Y);
            int width = maxX - minX + 1;
            int height = maxY - minY + 1;

            char[,] grid = new char[height, width];
            for (int i = 0; i < height; i++)
                for (int j = 0; j < width; j++)
                    grid[i, j] = filler;

            foreach (var field in fields)
            {
                for (int i = 0; i < field.Length; i++)
                {
                    Square ts = field.Squares[i];
                    char guessChar = field.Guesses[i];
                    grid[ts.Y - minY, ts.X - minX] = guessChar != ' ' ? guessChar : unknown;
                }
            }
            int rows = grid.GetLength(0), cols = grid.GetLength(1);
            return Enumerable.Range(0, rows)
                .Select(i => new string(Enumerable.Range(0, cols).Select(j => grid[i, j]).ToArray())).ToList();
        }

        private static void SyncIntersections(ref List<Field> fields, int x, int y, char c)
        {
            var intersectingFields = fields.AsEnumerable()
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

        private List<Field> CreateNewState(ref List<List<Field>> fields, Guess guess)
        {
            // Deep copy of crossword
            List<Field> lastState = [.. fields[^1].Select(f => new Field
            {
                ID = f.ID,
                Squares = new List<Square>(f.Squares),
                Length = f.Length,
                Guesses = new List<char>(f.Guesses),
                Completed = f.Completed
            })];

            Field field = lastState.Find(f => f.ID == guess.FieldId)!;

            for (int i = 0; i < field.Squares.Count; i++)
            {
                foreach (var fd in lastState)
                {
                    List<char> tmpList = [];

                    for (int j = 0; j < fd.Length; j++)
                    {
                        tmpList.Add(
                            fd.Squares[j].X == field.Squares[i].X &&
                            fd.Squares[j].Y == field.Squares[i].Y ? guess.Word.ToCharArray()[i] : fd.Guesses[j]);

                    }
                    fd.Guesses = tmpList;
                }
            }
            //var visualization = VisualizeCrossword(lastState, ' ', 'X');
            //visualization.ForEach(line => _logger.LogInformation(line));
            return lastState;
        }

        private void GetNextGuess(ref List<Guess> gc, ref List<List<Field>> fields)
        {
            if (gc.Count == 10)
            {
                return;
            }

            var field = fields.Last().AsEnumerable()
                .Where(f => f.Guesses.Any(c => c != ' ') && !f.Completed)
                .OrderBy(f => f.ID)
                .FirstOrDefault();

            if (field == null)
                return;

            //CS1628 otherwise
            var gcLocal = gc.ToList();

            var validWords = _context.Words.AsEnumerable().Where(w => w.Length == field.Length &&
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

            //if any field has no valid words, backtrack
            if (fields.Last().Where(f => !f.Completed).Any(fl => _context.Words.AsEnumerable().Where(
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
                fields.RemoveAt(fields.Count - 1);
                gc.RemoveAt(gc.Count - 1);
                return;
            }

            foreach (var w in validWords)
            {
                if (gc.Count == 10)
                {
                    return;
                }
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

                field.Completed = true;
                fields.Add(CreateNewState(ref fields, guess));
                GetNextGuess(ref gc, ref fields);
                if (w == validWords.Last())
                {
                    fields.RemoveAt(fields.Count - 1);
                    gc.RemoveAt(gc.Count - 1);
                }
            }

            return;
        }

        [HttpGet("AutoSolve")]
        public IActionResult AutoSolve()
        {
            ResetCrossword();
            var fields = _context.Fields.ToList();
            List<List<Field>> cwStates = [fields];
            List<Guess> gc = [];
            GetNextGuess(ref gc, ref cwStates);
            gc = gc.OrderBy(g => g.FieldId).ToList();
            _context.GuessChains.Add(new GuessChain { Guesses = gc });
            _context.SaveChanges();
            return Ok(gc);
        }

        [HttpGet("GetSolution")]
        public IActionResult GetSolution()
        {
            var solution = _context.GuessChains
                .FirstOrDefault();
            if (solution == null)
                return NotFound("Solution not found");
            return Ok(solution);
        }
    }
}
