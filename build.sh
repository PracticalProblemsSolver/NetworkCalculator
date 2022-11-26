mkdir build
g++ client.cpp functions/interactions.cpp -o build/client.o
g++ server.cpp functions/interactions.cpp functions/calc.cpp functions/handling.cpp -o build/server.o -lpqxx -lpq