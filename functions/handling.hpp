/*! \file    handling.hpp
 *
 *  \brief   Header file for handling.cpp
 *
 *  \details Contains signatures for signal handling
 *           and timer functions.
 */
#ifndef HANDLING_H
#define HANDLING_H

void signal_handler(int signum);

struct itimerval handle_signals(int sockfd, int wait_time);

void Setitimer(int which, const struct itimerval* new_value,
               struct itimerval* old_value);

void Sigaction(int signum, const struct sigaction* act,
               struct sigaction* oldact);

#endif
