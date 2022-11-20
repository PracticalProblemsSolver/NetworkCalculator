/*! \file    interactions.hpp
 *
 *  \brief   Header file for interactions.cpp
 *
 *  \details Contains signatures for client-server
 *           functions.
 */
#ifndef INTERACTIONS_H
#define INTERACTIONS_H
const int NO_PROTOCOL = 0;
const int TRUE = 1;
int Socket(int domain, int type, int protocol);

void Bind(int sockfd, const struct sockaddr* addr,
        socklen_t addrlen);

void Connect(int sockfd, const struct sockaddr *addr,
             socklen_t addrlen);
#endif
