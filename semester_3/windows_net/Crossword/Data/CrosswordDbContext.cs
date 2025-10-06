using Crossword.Models;
using Microsoft.EntityFrameworkCore;
using System.Text.Json;

namespace Crossword.Data
{
    public class CrosswordDbContext : DbContext
    {
        public DbSet<Word> Words { get; set; }
        public required DbSet<Field> Fields { get; set; }

        public CrosswordDbContext(DbContextOptions<CrosswordDbContext> options) : base(options)
        {
            Database.EnsureCreated();
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<Field>(entity =>
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


                entity.HasKey(f => f.ID);

                entity.Property(f => f.Squares)
                    .HasConversion(
                        v => JsonSerializer.Serialize(v, (JsonSerializerOptions)null),
                        v => JsonSerializer.Deserialize<List<Tuple<int, int>>>(v, (JsonSerializerOptions)null));

                entity.Property(f => f.Guesses)
                    .HasConversion(
                        v => JsonSerializer.Serialize(v, (JsonSerializerOptions)null),
                        v => JsonSerializer.Deserialize<List<char>>(v, (JsonSerializerOptions)null));

                entity.Property(f => f.Completed);

                // Seed data
                entity.HasData(
                    new Field
                    {
                        ID = 1,
                        Squares = [
                            Tuple.Create(9, 6),
                            Tuple.Create(10, 6),
                            Tuple.Create(11, 6),
                            Tuple.Create(12, 6),

                            ],
                        Guesses = ['Š'],
                        Completed = false
                    }
                );
            });
        }
    }
}
