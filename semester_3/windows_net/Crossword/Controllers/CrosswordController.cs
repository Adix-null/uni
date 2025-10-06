using Crossword.Models;
using Microsoft.AspNetCore.Mvc;

namespace Crossword.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class CrosswordController : ControllerBase
    {
        private readonly ILogger<CrosswordController> _logger;

        public CrosswordController(ILogger<CrosswordController> logger)
        {
            _logger = logger;
        }

        [HttpPost(Name = "AddField")]
        public IActionResult AddField()
        {

            return Ok();
        }
    }
}
