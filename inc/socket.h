#ifndef SOCKET_H
#define SOCKET_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>

#include "command.h"
#include "util.h"

#define MAX_BUFFER_SIZE 4096

void new_socket_fd();
void allow_reuse();
void bind_socket(char *ip, int port);
void listen_socket();
void wait_for_connection();
void send_message(int client_socket, const char* message);
void end_connection(int client_socket);

#endif // SOCKET_H
