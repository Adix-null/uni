CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJ = main.o dekas.o
TARGET = main

all: $(TARGET)
	./main

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(TARGET)