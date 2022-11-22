/*! \file    interactions.cpp
 *
 *  \brief   File with interaction functions.
 *
 *  \details Contains client-server interaction functions.
 */
#include <sys/socket.h>
#include <cstdio>
#include <cstdlib>
#include <arpa/inet.h>
#include <cstring>
#include "interactions.hpp"
#include <string>


/*! \brief   String sending function.
 *
 *  \details Sends given string by given socket if possible.
 *
 *  \param   sockfd   Socket descriptor.
 *
 *  \param   message  String type message.
 * */
void send_string(int sockfd, std::string message) {
    char buffer[256];
    memset(&buffer, 0, sizeof(buffer));
    strcpy(buffer, message.c_str());
    size_t res = send(sockfd, (char*) &buffer, strlen(buffer), 0);
    if (res == -1) {
        perror("Message sending error");
        exit(-1);
    }
}

/*! \brief   String receiving function.
 *
 *  \details Accepts string by given socket.
 *
 *  \param   sockfd  Socket descriptor.
 *
 *  \return  Accepted string.
 * */
std::string receive_string(int sockfd) {
    char buffer[256];
    memset(&buffer, 0, sizeof(buffer));
    size_t res = recv(sockfd, (char*) &buffer, sizeof(buffer), 0);
    if (res == -1) {
        perror("Receiving error");
        exit(-1);
    }
    std::string message = std::string(buffer);
    return message;
}

/*! \brief   Socket function wrapper.
 *
 *  \details Function creates socket by given parameters.
 *
 *  \param   domain   Socket domain.
 *
 *  \param   type     Type of internet connection.
 *
 *  \param   protocol Protocol of internet connection
 *
 *  \return  Created socket descriptor.
 * */
int Socket(int domain, int type, int protocol) {
    int res = socket(domain, type, protocol);
    if (res == -1) {
        perror("Socket failed");
        exit(-1);
    }
    return res;
}

/*! \brief   Bind function wrapper.
 *
 *  \details Function binds server by socket descriptor and
 *           address structure.
 *
 *  \param   sockfd  Socket descriptor.
 *
 *  \param   addr    Address structure.
 *
 *  \param   addrlen Size of address structure.
 * */
void Bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen) {
    int res = bind(sockfd, addr, addrlen);
    if (res == -1) {
        perror("Bind failed");
        exit(-1);
    }
}

/*! \brief   Connect function wrapper.
 *
 *  \details Connect client to server.
 *
 *  \param   sockfd  Socket descriptor.
 *
 *  \param   addr    Address structure.
 *
 *  \param   addrlen Size of address structure.
 * */
void Connect(int sockfd, const struct sockaddr* addr,
             socklen_t addrlen) {
    int res = connect(sockfd, addr, addrlen);
    if (res == -1) {
        perror("Connection failed");
        exit(-1);
    }
}

/*! \brief   Inet function wrapper.
 *
 *  \details Checks given IP address property.
 *
 *  \param   af  AF_INET or AF_INET6.
 *
 *  \param   src String with address.
 *
 *  \param   dst Sin_addr.
 * */
void Inet_pton(int af, const char* __restrict src, void* __restrict dst) {
    int res = inet_pton(af, src, dst);
    if (res != 1) {
        perror("Address is not supported");
        exit(-1);
    }
}
