#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "util.h"
#include "room.h"
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

    init_rooms();

    while (1)
    {
        wait_for_connection();
    }

    exit(EXIT_SUCCESS);
}
