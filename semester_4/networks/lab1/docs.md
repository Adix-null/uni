### Server
Runs on port 1790. \
Quickly run with 
```bash
gcc server.c -o server.exe -lws2_32 && ./server.exe 1790
``` 
To find if something active is on port 
```bash
netstat -ano | findstr :1790
```
To kill it, look at the PID at the end and
```bash
taskkill /F /PID THE_PID
```

### Client
Quickly run with 
```bash
gcc client.c -o client.exe -lws2_32 && ./client.exe 127.0.0.1 1790
``` 