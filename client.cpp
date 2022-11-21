#include <iostream>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include "interactions.hpp"

using namespace std;
const int MIN_ARGS = 3;


/*! \brief   Print usage function.
 *
 *  \details Prints usage for client CL arguments.
 */
void print_usage() {
    cout << "Usage: <IP-adress> <Port>" << endl;
    cout << "Example: 127.0.0.1 8080" << endl;
}

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
        print_usage();
        return -1;
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
    cout << "Connected to server" << endl;

    cout << "Login:\n>";
    string login;
    getline(cin, login);
    send_string(client, login);

    cout << "Password:\n>";
    string password;
    getline(cin, password);
    send_string(client, password);

    cout << "Enter the command:" << endl;
    string command;
    while (TRUE) {
        cout << ">";
        getline(cin, command);
        if (command == "logout") {
            break;
        }
    }
    close(client);
    return 0;
}