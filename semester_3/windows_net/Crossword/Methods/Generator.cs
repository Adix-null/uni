using Crossword.Models;

namespace Crossword.Methods
{
    public static class Generator
    {
        public static List<Square> GenerateSquares(int x_start, int y_start, int length, int direction)
        {
            int dx = 0, dy = 0;
            switch (direction)
            {
                case 0: dx = 0; dy = -1; break; // North
                case 1: dx = 1; dy = 0; break;  // East
                case 2: dx = 0; dy = 1; break;  // South
                case 3: dx = -1; dy = 0; break; // West
            }
            var squares = new List<Square>();
            for (int i = 0; i < length; i++)
            {
                squares.Add(new(x_start + i * dx, y_start + i * dy));
            }
            return squares;
        }
    }
}
