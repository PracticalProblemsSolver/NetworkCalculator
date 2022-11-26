g++ client.cpp interactions.cpp calc.cpp handling.cpp -o client.o
g++ server.cpp interactions.cpp calc.cpp handling.cpp -o server.o -lpqxx -lpq