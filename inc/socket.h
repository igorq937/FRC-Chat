#ifndef SOCKET_H
#define SOCKET_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include "util.h"

#define MAX_BUFFER_SIZE 4096

void new_socket_fd();
void allow_reuse();
void bind_socket(char *ip, int port);
void listen_socket();
void wait_for_connection();

#endif // SOCKET_H
