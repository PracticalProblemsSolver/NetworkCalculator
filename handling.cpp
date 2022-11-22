/*! \file    handling.cpp
 *
 *  \brief   File with handling functions.
 *
 *  \details Contains functions that performs signal handling
 *           and timer functioning.
 */
#include <unistd.h>
#include <csignal>
#include <sys/time.h>
#include <cstring>
#include <iostream>
#include "handling.hpp"
#include "interactions.hpp"

int g_server_socket;

/*! \brief   Server signals handler.
 *
 *  \details Handles signals coming from server
 *           process.
 *
 *  \param   signum Signal type.
 * */
void signal_handler(int signum) {
    if (signum == SIGALRM) {
        std::cout << "Server are no longer receiving messages: Inactive client\n";
    }
    else if (signum == SIGINT) {
        std::cout << "\nServer work interrupted by user\n";
        close(g_server_socket);
        exit(EXIT_SUCCESS);
    }
    else if (signum == SIGTERM) {
        std::cout << "Server process terminated\n";
        close(g_server_socket);
        exit(EXIT_SUCCESS);
    }

}

/*! \brief   Function that handle signals.
 *
 *  \details Binds signals for a server and
 *           returns itimerval timer struct.
 *
 *  \param   sockfd     Socket descriptor.
 *
 *  \param   wait_time  The time after which the timer
 *                      will send a signal .
 *  \return  timer      Itimerval structure
 * */
struct itimerval handle_signals(int sockfd, int wait_time) {
    struct sigaction sig_struct;
    struct itimerval timer = {0};
    memset(&sig_struct, 0, sizeof sig_struct);
    g_server_socket = sockfd;
    sig_struct.sa_handler = &signal_handler;
    Sigaction(SIGALRM, &sig_struct, NULL);
    Sigaction(SIGINT, &sig_struct, NULL);
    Sigaction(SIGTERM, &sig_struct, NULL);
    timer.it_value.tv_sec = wait_time;
    return timer;
}

/*! \brief   Setitimer function.
 *
 *  \details Sets timer for a process.
 *
 *  \param   which  Type of timer.
 *
 *  \param   new_value  A pointer to a new itimerval structure.
 *
 *  \param   old_value  A pointer to an old itimerval structure.
 * */
void Setitimer(int which, const struct itimerval* new_value,
               struct itimerval* old_value) {
    int res = setitimer(which, new_value, old_value);
    if (res == EXIT_FAIL) {
        perror("set timer fail");
        exit(EXIT_FAIL);
    }
}

/*! \brief   Sigaction function.
 *
 *  \details Function binds the signal to a given function.
 *
 *  \param   signum  Signal type.
 *
 *  \param   act     Address of the function.
 *
 *  \param   oldact  Old address.
 * */
void Sigaction(int signum, const struct sigaction* act,
               struct sigaction* oldact) {
    int res = sigaction(signum, act, oldact);
    if (res == EXIT_FAIL) {
        perror("sig action fail");
        exit(EXIT_FAIL);
    }
}