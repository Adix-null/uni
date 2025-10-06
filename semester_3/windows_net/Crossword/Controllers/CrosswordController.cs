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

            var squares = new List<Tuple<int, int>>();
            var guesses = new List<char>();
            for (int i = 0; i < length; i++)
            {
                guesses.Add(' ');
                squares.Add(new Tuple<int, int>(x_start + i * dx, y_start + i * dy));
            }

            Field newField = new()
            {
                Squares = squares,
                Guesses = guesses,
                Completed = false
            };
            _context.Fields.Add(newField);
            _context.SaveChanges();
            return Ok(newField);
        }
    }
}
