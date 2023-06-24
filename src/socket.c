#include "socket.h"

int server_socket = -1;
fd_set current_sockets, ready_sockets;
int max_sockets_fd = -1;

void new_socket_fd()
{
    check_error(server_socket = socket(AF_INET, SOCK_STREAM, 0));
    debug_print("socket created\n");
}

void allow_reuse()
{
    int optval = 1;
    check_error(setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)));
    debug_print("socket reuse allowed\n");
}

void bind_socket(char *ip, int port)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);
    check_error(bind(server_socket, (struct sockaddr *) &addr, sizeof(addr)));
    debug_print("socket bound to http://%s:%d\n", ip, port);
}

void listen_socket()
{
    check_error(listen(server_socket, 10));
    FD_ZERO(&current_sockets);
    FD_SET(server_socket, &current_sockets);
    max_sockets_fd = server_socket;
    debug_print("socket listening\n");
}

int accept_connection()
{
    debug_print("waiting for connection...\n");
    struct sockaddr_in end_cli;
    socklen_t alen = sizeof(end_cli);
    int client_socket;
    check_error(client_socket = accept(server_socket, (struct sockaddr *)&end_cli, &alen));
    debug_print("connection accepted from %s:%d\n", inet_ntoa(end_cli.sin_addr), ntohs(end_cli.sin_port));
    return client_socket;
}

void handle_connection(int client_socket) {

    debug_print("waiting for data...\n");
    char buf[MAX_BUFFER_SIZE];
    char response[] = "Hello World!\n";
    int n;
    check_error(n = recv(client_socket, buf, MAX_BUFFER_SIZE, 0));

    //Aqui começa o tratamento da requisição

    debug_print("received %d bytes\n", n);
    send(client_socket, response, strlen(response), 0);
}

void wait_for_connection()
{
    ready_sockets = current_sockets;
    check_error(select(max_sockets_fd + 1, &ready_sockets, NULL, NULL, NULL));

    for (int i = 0; i <= max_sockets_fd; i++) {
        if(FD_ISSET(i, &ready_sockets)) {
            if(i == server_socket) {
                int client_socket = accept_connection();
                FD_SET(client_socket, &current_sockets);
                if(client_socket > max_sockets_fd) max_sockets_fd = client_socket;
            }else{
                handle_connection(i);
                FD_CLR(i, &current_sockets);
            }
        }
	}
}
