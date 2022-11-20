/*! \file    interactions.cpp
 *
 *  \brief   File with functions.
 *
 *  \details Contains client-server functions.
 */
#include <sys/socket.h>
#include <cstdio>
#include <cstdlib>
#include "interactions.hpp"

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
void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int res = bind(sockfd, addr, addrlen);
    if (res == -1) {
        perror("Bind failed");
        exit(-1);
    }
}
/*! \brief   Connect function wrapper.
 *
 *  \details Function connect to a server.
 *
 *  \param   sockfd  Socket descriptor.
 *
 *  \param   addr    Address structure.
 *
 *  \param   addrlen Size of address structure.
 * */
void Connect(int sockfd, const struct sockaddr *addr,
             socklen_t addrlen) {
    int res = connect(sockfd, addr, addrlen);
    if (res == -1) {
        perror("Connection failed");
        exit(-1);
    }
}
