#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <unistd.h>
#include "interactions.hpp"

using namespace std;
const int MIN_ARGS = 2;
const int MAX_CONNECTIONS = 10;

/*! \brief   Print usage function.
 *
 *  \details Prints usage for client CL arguments.
 */
void print_usage() {
    cout << "Usage: <Port>" << endl;
    cout << "Example: 8080" << endl;
}

/*! \brief   Server main function.
 *
 *  \details Function that starts a server and connects with a client.
 *
 *  \return  Returns -1 upon error.
 */
int main(int argc, char* argv[]) {
    if (argc != MIN_ARGS) {
        print_usage();
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
    listen(server, MAX_CONNECTIONS);
    int new_socket = accept(server, (sockaddr*) &new_adr,
                            &size);
    if (new_socket < 0) {
        cout << "Error connecting with client" << endl;
        exit(-1);
    }
    cout << "Client connected on " << inet_ntoa(new_adr.sin_addr)
         << ":" << ntohs(new_adr.sin_port) << endl;

    string login = receive_string(new_socket);
    cout << login << endl;

    string password = receive_string(new_socket);
    cout << password << endl;

    close(new_socket);
    close(server);
    return 0;
}