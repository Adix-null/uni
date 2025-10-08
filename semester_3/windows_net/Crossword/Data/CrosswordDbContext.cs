using Crossword.Methods;
using Crossword.Models;
using Microsoft.EntityFrameworkCore;
using System.Text.Json;

namespace Crossword.Data
{
    public class CrosswordDbContext : DbContext
    {
        public DbSet<Word> Words { get; set; }
        public required DbSet<Field> Fields { get; set; }
        public DbSet<GuessChain> GuessChains { get; set; }

        public CrosswordDbContext(DbContextOptions<CrosswordDbContext> options) : base(options)
        {
            Database.EnsureCreated();
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<Field>(entity =>
            {
                entity.HasKey(f => f.ID);

                entity.Property(f => f.Squares)
                    .HasConversion(
                        v => JsonSerializer.Serialize(v, (JsonSerializerOptions)null),
                        v => JsonSerializer.Deserialize<List<Square>>(v, (JsonSerializerOptions)null));

                entity.Property(f => f.Guesses)
                    .HasConversion(
                        v => JsonSerializer.Serialize(v, (JsonSerializerOptions)null),
                        v => JsonSerializer.Deserialize<List<char>>(v, (JsonSerializerOptions)null));

                entity.Property(f => f.Completed);

                var fieldParams = new (int id, int x, int y, int length, int direction)[]
                   {
                        (1, 0, 2, 9, 1),
                        (2, 10, 2, 4, 1),
                        (3, 5, 4, 7, 1),
                        (4, 2, 6, 6, 1),
                        (5, 9, 6, 4, 1),
                        (6, 3, 8, 9, 1),
                        (7, 4, 6, 4, 2),
                        (8, 7, 0, 9, 2),
                        (9, 9, 4, 6, 2),
                        (10, 11, 1, 9, 2)
                   };

                var fields = fieldParams.Select(p => new Field
                {
                    ID = p.id,
                    Squares = Generator.GenerateSquares(p.x, p.y, p.length, p.direction),
                    Guesses = [.. Enumerable.Repeat(' ', p.length)],
                    Length = p.length,
                    Completed = false
                }).ToArray();

                entity.HasData(fields);
            });
            modelBuilder.Entity<Word>(entity =>
            {
                var words = File.ReadAllLines("upes.txt")
                   .Where(line => !string.IsNullOrWhiteSpace(line) && line.Length > 3 && line.Length < 10)
                   .Select(line =>
                   {
                       var chars = line.ToUpper().PadRight(9).ToCharArray(); // length := >9
                       return new Word
                       {
                           Strword = line.ToUpper(),
                           Length = line.Length,
                           C1 = chars[0],
                           C2 = chars[1],
                           C3 = chars[2],
                           C4 = chars[3],
                           C5 = chars[4],
                           C6 = chars[5],
                           C7 = chars[6],
                           C8 = chars[7],
                           C9 = chars[8]
                       };
                   })
                   .ToArray();
                modelBuilder.Entity<Word>().HasData(words);
            });
            modelBuilder.Entity<GuessChain>(entity =>
            {
                entity.Property(g => g.Guesses)
                   .HasConversion(
                       v => JsonSerializer.Serialize(v, (JsonSerializerOptions)null),
                       v => JsonSerializer.Deserialize<List<Guess>>(v, (JsonSerializerOptions)null));

                entity.HasKey(g => g.ID);
            });
        }
    }
}
