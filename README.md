# Client-Server Calculator
## Requirements:
* PostgreSQL 14.5
* G++ 12.2.0
* libpqxx
* CMake 3.23
## Preparations
1. Run create_db.sql script as postgres admin
2. Write login and password of your postgres admin like in the example
```
login
password
```

## Build instructions
### Simple way
```
mkdir build
bash build.sh
cd build
```
### CMake way
```
mkdir build
cd build
cmake ..
cmake --build .
```
Now you can use the application.
## Launch instructions
The app consists of two parts - server and client applications.
To launch a server you need to set the port for incoming connections. After that, to launch
a client part you need to set an IP-address and a port of the server.
Then you will be using CLI to interact with the server.

Examples:
```
./server.o 1234
./client 127.0.0.1 1234
```