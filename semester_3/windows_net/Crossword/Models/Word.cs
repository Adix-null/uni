using Microsoft.EntityFrameworkCore;

namespace Crossword.Models
{
    [PrimaryKey(nameof(strword))]
    public class Word
    {
        public required string strword;
        public int length;
        public char C1;
        public char C2;
        public char C3;
        public char C4;
        public char C5;
        public char C6;
        public char C7;
        public char C8;
        public char C9;
    }
}
