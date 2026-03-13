### Server
Download mozilla server and create a user. Then set all the connection params from the user to allow plain ftp without tls and login from the client. 

### Client
Quickly run with 
```bash
gcc client.c ftp.c command_list.c -o client.exe -lws2_32 && ./client.exe 127.0.0.1 21
``` 