#ifndef ROOM_H
#define ROOM_H

#include <stdlib.h>

#include "socket.h"

void add_room(char* name, int capacity);
void remove_room(int room_id);
void print_rooms(int client_socket);

#endif //ROOM_H
