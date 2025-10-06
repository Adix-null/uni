using Microsoft.EntityFrameworkCore;

namespace Crossword.Models
{
    [PrimaryKey(nameof(Strword))]
    public class Word
    {
        public required string Strword { set; get; }
        public int Length { set; get; }
        public char C1 { set; get; }
        public char C2 { set; get; }
        public char C3 { set; get; }
        public char C4 { set; get; }
        public char C5 { set; get; }
        public char C6 { set; get; }
        public char C7 { set; get; }
        public char C8 { set; get; }
        public char C9 { set; get; }
    }
}
