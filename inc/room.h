#ifndef ROOM_H
#define ROOM_H

#include <stdlib.h>

#include "socket.h"

#define MAX_CAPACITY 10
#define MAX_ROOMS 20
#define MAX_MSG_SIZE 2048

void init_rooms();
void add_room(char* name, int capacity);
void remove_room(int client_socket, int room_id);
void list_rooms(int client_socket);
void list_people(int client_socket);
void join_room(int client_socket, int room_id, char* name);
void leave_room(int client_socket);
void send_message2room(int client_socket, char* message);

#endif //ROOM_H
