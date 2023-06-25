#include "room.h"

#define MAX_ROOMS 20

typedef struct room_s {
    int id;
    char* name;
    int num_people;
    int capacity;
    struct room_s* next;
} room_t;

room_t *rooms = NULL;
int current_room_id = 0;

void add_room(char* name, int capacity)
{
    room_t* new_room = malloc(sizeof(room_t));
    new_room->id = current_room_id++;
    new_room->name = name;
    new_room->num_people = 0;
    new_room->capacity = capacity;
    new_room->next = rooms;
    rooms = new_room;
}

void remove_room(int room_id)
{
    room_t* room = rooms;
    room_t* prev = NULL;
    while(room != NULL) {
        if(room->id == room_id) {
            if(prev == NULL) {
                rooms = room->next;
            } else {
                prev->next = room->next;
            }
            free(room);
            return;
        }
        prev = room;
        room = room->next;
    }
}

void print_rooms(int client_socket)
{
    room_t* room = rooms;
    while(room != NULL) {
        char* message = malloc(100);
        sprintf(message, "%s[%d] %s%s (%d/%d)%s\n", BLU, room->id, GRN, room->name, room->num_people, room->capacity, RESET);
        send_message(client_socket, message);
        free(message);
        room = room->next;
    }
}
