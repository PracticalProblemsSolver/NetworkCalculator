/*! \file    interactions.hpp
 *
 *  \brief   Header file for interactions.cpp
 *
 *  \details Contains signatures for client-server
 *           functions.
 */
#ifndef INTERACTIONS_H
#define INTERACTIONS_H

#include <string>
using namespace std;
const int NO_PROTOCOL = 0;
const int TRUE = 1;

void send_string(int sockfd, const string &message);

string receive_string(int sockfd);

int Socket(int domain, int type, int protocol);


void Bind(int sockfd, const struct sockaddr* addr,
          socklen_t addrlen);

void Connect(int sockfd, const struct sockaddr* addr,
             socklen_t addrlen);

void Inet_pton(int af, const char* __restrict src,
               void* __restrict dst);


#endif
