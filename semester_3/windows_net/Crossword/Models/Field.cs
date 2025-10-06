using Microsoft.EntityFrameworkCore;

namespace Crossword.Models
{
    [PrimaryKey(nameof(ID))]
    public class Field
    {
        public int ID { set; get; }
        public List<Square> Squares { get; set; } = [];
        public int Length { set; get; }
        public List<char> Guesses { get; set; } = [];
        public bool Completed { get; set; }
    }
}
