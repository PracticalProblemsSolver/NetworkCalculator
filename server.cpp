/*! \file    server.cpp
 *
 *  \brief   Server app.
 *
 *  \details Starts a server that accepts connections
 *           from clients.
 */
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <unistd.h>
#include <sys/time.h>
#include <pqxx/pqxx>
#include <fstream>
#include "functions/interactions.hpp"
#include "functions/calc.hpp"
#include "functions/handling.hpp"

const int MIN_ARGS = 2;
const int MAX_CONNECTIONS = 10;
const int RESPONSE_TIMEOUT = 15;

/*! \brief   Timer stop function.
 *
 *  \details Stops timer on given socket.
 *
 *  \param   sockfd Socket descriptor.
 * */
void stop_timer(int sockfd) {
    int wait_time = 0;
    struct itimerval timer = handle_signals(sockfd, wait_time);
    Setitimer(ITIMER_REAL, &timer, nullptr);
}

/*! \brief   Client disconnect function.
 *
 *  \details Disconnects client and sends disconnect reason.
 *
 *  \param   newsockfd Client socket.
 *
 *  \param   reason    Disconnect reason string.
 * */
void disconnect_client(int newsockfd, std::string reason) {
    send_string(newsockfd, reason);
    std::cout << "Client disconnected: " << reason << "\n";
    close(newsockfd);
}

/*! \brief   Server main function.
 *
 *  \details Function that starts a server and connects with a client.
 *
 *  \return  Returns -1 upon error.
 */
int main(int argc, char* argv[]) {
    if (argc != MIN_ARGS) {
        std::cout << "Usage: <Port>\nExample: 8080\n";
        return EXIT_FAIL;
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
    std::cout << "Server started\n";

    sockaddr_in new_adr{0};
    auto size = (socklen_t) sizeof(new_adr);
    int wait_time = RESPONSE_TIMEOUT;
    int new_socket;
    while (true) {
        listen(server, MAX_CONNECTIONS);
        new_socket = accept(server, (sockaddr*) &new_adr,
                            &size);
        if (new_socket < 0) {
            std::cout << "Error connecting with client\n";
            exit(EXIT_FAIL);
        }

        struct itimerval timer = handle_signals(server, wait_time);
        Setitimer(ITIMER_REAL, &timer, nullptr);
        std::cout << "Client connected on " << inet_ntoa(new_adr.sin_addr)
                  << ":" << ntohs(new_adr.sin_port) << "\n";

        std::string login = receive_string(new_socket);
        std::string password = receive_string(new_socket);
        std::cout << login << " " << password << "\n";
        stop_timer(server);
        std::ifstream input("login_db.txt");
        if (!input) {
            std::cout << "Error opening login file\n";
            return EXIT_FAIL;
        }
        std::vector<std::string> db_user;
        while (!input.eof()) {
            std::string line;
            getline(input, line);
            db_user.push_back(line);
        }

        std::string connection =
                "host=localhost port=5432 dbname=cscalc"
                " user=" + db_user[0] +
                " password=" + db_user[1];
//        try {
        pqxx::connection connectionObject(connection.c_str());
        pqxx::work worker(connectionObject);
//        }
//        catch (const std::exception &e) {
//            std::cerr << e.what() << "\n";
//            close(server);
//            close(new_socket);
//            return EXIT_FAIL;
//        }
        std::string query = "SELECT password, balance FROM users "
                            "WHERE login = " + worker.quote(login);
        pqxx::result response = worker.exec(query);
        worker.commit();
        std::string db_password = to_string(response[0][0]);
        int db_balance = std::stoi(to_string(response[0][1]));
        std::cout << db_balance << "\n";
        if (response.empty() || to_string(response[0][0]) != password) {
            disconnect_client(new_socket, INVALID_INPUT);
            continue;
        }
        send_string(new_socket, AUTH_SUCCESS);
        std::string message;
        float calc_res;
        std::string update = "UPDATE users "
                             "SET balance = balance - 1 "
                             "WHERE login = " + worker.quote(login);

        while (true) {
            message = receive_string(new_socket);
            if (message == "logout") {
                close(new_socket);
                break;
            }
            if (db_balance < 1) {
                disconnect_client(new_socket, BALANCE_OVER);
                break;
            }
            calc_res = calculate(message);
            if (calc_res == CALC_FAIL) {
                message = "Invalid input";
            }
            else {
                db_balance--;
                pqxx::work updater(connectionObject);
                message = std::to_string(calc_res);
                updater.exec0(update);
                updater.commit();
            }
            send_string(new_socket, message);
        }
    }
}