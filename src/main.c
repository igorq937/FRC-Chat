#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "util.h"
#include "socket.h"


int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("usage: %s <ip> <port>\n", argv[0]);
        exit(-1);
    }

    new_socket_fd();
    allow_reuse();
    bind_socket(argv[1], atoi(argv[2]));
    listen_socket();
    int conn_fd = wait_for_connection();

    int n;
    char buf[MAX_BUFFER_SIZE];
    char response[] = "Hello World!";
    while ((n = read(conn_fd, buf, sizeof(buf))) > 0)
    {
        debug_print("received %d bytes\n", n);
        write(conn_fd, response, strlen(response));
        close(conn_fd);
    }

    exit(EXIT_SUCCESS);
}
