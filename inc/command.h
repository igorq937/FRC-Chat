#ifndef COMMAND_H
#define COMMAND_H

#include "socket.h"
#include "room.h"

void execute_command(int client_socket, char* command);

#endif // COMMAND_H
