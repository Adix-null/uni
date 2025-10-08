namespace Crossword.Models
{
    public class GuessChain
    {
        public int ID { get; set; }
        public List<Guess> Guesses { get; set; } = [];
    }
    public record Guess(int FieldId, string Word);
}
