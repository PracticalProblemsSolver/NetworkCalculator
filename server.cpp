#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <unistd.h>
#include "interactions.hpp"
#include "calc.hpp"

const int MIN_ARGS = 2;
const int MAX_CONNECTIONS = 10;


/*! \brief   Server main function.
 *
 *  \details Function that starts a server and connects with a client.
 *
 *  \return  Returns -1 upon error.
 */
int main(int argc, char* argv[]) {
    if (argc != MIN_ARGS) {
        std::cout << "Usage: <Port>\nExample: 8080\n";
        return -1;
    }
    int port = atoi(argv[1]);
    struct sockaddr_in adr = {0};
    int server = Socket(AF_INET, SOCK_STREAM,
                        NO_PROTOCOL);
    adr.sin_family = AF_INET;
    adr.sin_addr.s_addr = htonl(INADDR_ANY);
    adr.sin_port = htons(port);
    Bind(server, (const struct sockaddr*) &adr,
         sizeof adr);
    sockaddr_in new_adr{0};
    auto size = (socklen_t) sizeof(new_adr);
    int new_socket;
    while (true) {
        listen(server, MAX_CONNECTIONS);
        new_socket = accept(server, (sockaddr*) &new_adr,
                            &size);
        if (new_socket < 0) {
            std::cout << "Error connecting with client\n";
            exit(-1);
        }
        std::cout << "Client connected on " << inet_ntoa(new_adr.sin_addr)
                  << ":" << ntohs(new_adr.sin_port) << "\n";

        std::string login = receive_string(new_socket);
        std::string password = receive_string(new_socket);
        std::cout << login << " " << password << "\n";

        std::string message;
        std::string calc_res;
        while (true) {
            message = receive_string(new_socket);
            if (message == "logout") {
                close(new_socket);
                break;
            }
            calc_res = std::to_string(calculate(message));
            send_string(new_socket, calc_res);
        }
        break;
    }
    close(server);
    return 0;
}