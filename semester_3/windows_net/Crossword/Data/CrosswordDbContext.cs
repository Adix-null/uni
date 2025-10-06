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
