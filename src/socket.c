#include "socket.h"

char buf[MAX_BUFFER_SIZE];
int socket_fd = -1;

void new_socket_fd()
{
    check_error(socket_fd = socket(AF_INET, SOCK_STREAM, 0));
    debug_print("socket created\n");
}

void allow_reuse()
{
    int optval = 1;
    check_error(setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)));
    debug_print("socket reuse allowed\n");
}

void bind_socket(char *ip, int port)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    check_error(inet_pton(AF_INET, ip, &addr.sin_addr));
    check_error(bind(socket_fd, (struct sockaddr *) &addr, sizeof(addr)));
    debug_print("socket bound to http://%s:%d\n", ip, port);
}

void listen_socket()
{
    check_error(listen(socket_fd, 10));
}

int wait_for_connection()
{
    debug_print("waiting for connection...\n");
    struct sockaddr_in end_cli;
    socklen_t alen = sizeof(end_cli);
    int client_socket_fd;
    check_error(client_socket_fd = accept(socket_fd, (struct sockaddr *)&end_cli, &alen));
    debug_print("connection accepted from %s:%d\n", inet_ntoa(end_cli.sin_addr), ntohs(end_cli.sin_port));
    return client_socket_fd;
}
