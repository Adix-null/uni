CC=gcc
CFLAGS=-lws2_32

server.exe: server.c game_logic.c
	$(CC) server.c game_logic.c -o server.exe $(CFLAGS)

client.exe: client.c game_logic.c
	$(CC) client.c game_logic.c -o client.exe $(CFLAGS)

start_server: server.exe
	.\server.exe $(PORT)

start_client: client.exe
	.\client.exe $(IP) $(PORT)

clean:
	del server.exe client.exes