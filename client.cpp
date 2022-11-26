/*! \file    client.cpp
 *
 *  \brief   Client app.
 *
 *  \details Starts a client that connects to a server.
 */
#include <iostream>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include "functions/interactions.hpp"

const int MIN_ARGS = 3;

/*! \brief   Client main function.
 *
 *  \details Client function that connects with server.
 *
 *  \param   argc  Count of terminal arguments.
 *
 *  \param   argv  List of terminal arguments.
 *
 *  \return  Returns -1 upon error.
 * */
int main(int argc, char* argv[]) {
    if (argc != MIN_ARGS) {
        std::cout << "Usage: <IP-adress> <Port>\nExample: 127.0.0.1 8080\n";
        return EXIT_FAIL;
    }
    char* ip = argv[1];
    int port = atoi(argv[2]);
    struct sockaddr_in adr = {0};
    struct hostent* host = gethostbyname(ip);
    adr.sin_family = AF_INET;
    adr.sin_port = htons(port);
    adr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*) *host->h_addr_list));
    Inet_pton(AF_INET, ip, &adr.sin_addr);

    int client = Socket(AF_INET, SOCK_STREAM, NO_PROTOCOL);
    Connect(client, (sockaddr*) &adr,
            sizeof(adr));
    std::cout << "Connected to server\n";

    std::cout << "Login:\n>";
    std::string login;
    getline(std::cin, login);
    send_string(client, login);

    std::cout << "Password:\n>";
    std::string password;
    getline(std::cin, password);
    send_string(client, password);

    std::string response = receive_string(client);
    if (response == INVALID_INPUT) {
        std::cout << INVALID_INPUT << "\n";
        close(client);
        return EXIT_FAIL;
    }
    else if (response == AUTH_SUCCESS) {
        std::cout << AUTH_SUCCESS << "\n";
    }
    std::string command;
    std::string calc_res;
    std::string expr;
    while (true) {
        std::cout << "Enter the command:\n>";
        getline(std::cin, command);
        if (command == "logout") {
            send_string(client, command);
            break;
        }
        else if (command == "calc") {
            std::cout << "Enter the expression to calculate:\n>";
            getline(std::cin, expr);
            send_string(client, expr);
            calc_res = receive_string(client);
            std::cout << calc_res << "\n";
            if (calc_res == BALANCE_OVER) {
                break;
            }
        }
        else if (command == "help") {
            std::cout << "Commands:\n"
                         "calc - Calculate an expression\n"
                         "logout - Logout and disconnect from server\n";
        }
        else {
            std::cout << "Unknown command, type 'help'\n";
        }
    }
    close(client);
    return 0;
}