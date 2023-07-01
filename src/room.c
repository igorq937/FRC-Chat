#include "room.h"

typedef struct person_s {
    char* name;
    int socket;
    int joined_room;
} person_t;

typedef struct room_s {
    int id;
    char* name;
    int num_people;
    int capacity;
    int* people;
} room_t;

room_t rooms[MAX_ROOMS + 1];
person_t people[FD_SETSIZE + 1];

void init_rooms()
{
    add_room("general", 10);
    for(int i = 0; i < FD_SETSIZE; i++) {
        people[i].name = NULL;
        people[i].socket = 0;
        people[i].joined_room = 0;
    }
}

void add_room(char* name, int capacity)
{
    for(int i = 1; i < MAX_ROOMS; i++) {
        if(rooms[i].name == NULL) {
            rooms[i].id = i;
            rooms[i].name = malloc(sizeof(char) * strlen(name));
            strcpy(rooms[i].name, name);
            rooms[i].num_people = 0;
            rooms[i].capacity = capacity;
            rooms[i].people = malloc(sizeof(int) * capacity);
            return;
        }
    }
}

void remove_room(int client_socket, int room_id)
{
    room_t* room = &rooms[room_id];

    if(room->num_people > 0) {
        send_message(client_socket, "room is not empty\n");
        return;
    }

    room->id = 0;
    free(room->name);
    room->name = NULL;
    room->num_people = 0;
    room->capacity = 0;
    free(room->people);
    room->people = 0;
    send_message(client_socket, "room deleted\n");
}

void list_rooms(int client_socket)
{
    for(int i = 1; i < MAX_ROOMS; i++) {
        if(rooms[i].name != NULL) {
            char* message = malloc(sizeof(char) * MAX_MSG_SIZE);
            sprintf(message, "%d: %s (%d/%d)\n", rooms[i].id, rooms[i].name, rooms[i].num_people, rooms[i].capacity);
            send_message(client_socket, message);
            free(message);
        }
    }
}

void list_people(int client_socket)
{
    person_t* person = &people[client_socket];
    room_t* room = &rooms[person->joined_room];

    if(people[client_socket].joined_room == 0) {
        send_message(client_socket, "you are not in a room\n");
        return;
    }

    for(int i = 0, peopleCounter = 0; i < room->capacity; i++) {
        if(room->people[i] != 0) {
            char* message = malloc(sizeof(char) * MAX_MSG_SIZE);
            sprintf(message, "%d: %s\n", ++peopleCounter, people[room->people[i]].name);
            send_message(client_socket, message);
            free(message);
        }
    }
}

void join_room(int client_socket, int room_id, char* name)
{
    person_t* person = &people[client_socket];
    room_t* room = &rooms[room_id];

    if(person->joined_room != 0) {
        send_message(client_socket, "you are already in a room\n");
        return;
    }

    if(room->num_people == room->capacity) {
        send_message(client_socket, "room is full\n");
        return;
    }

    person->name = malloc(sizeof(char) * strlen(name));
    strcpy(person->name, name);
    person->socket = client_socket;
    person->joined_room = room_id;

    for(int i = 0; i < room->capacity; i++) {
        if(room->people[i] == 0) {
            room->people[i] = client_socket;
            room->num_people++;
            break;
        }
    }
}

void leave_room(int client_socket)
{
    person_t* person = &people[client_socket];
    room_t* room = &rooms[person->joined_room];

    if(person->joined_room == 0) {
        send_message(client_socket, "you are not in a room\n");
        return;
    }

    free(person->name);
    person->name = NULL;
    person->socket = 0;
    person->joined_room = 0;

    for(int i = 0; i < room->capacity; i++) {
        if(room->people[i] == client_socket) {
            room->people[i] = 0;
            room->num_people--;
            break;
        }
    }
}

void send_message2room(int client_socket, char* message)
{
    if(people[client_socket].joined_room == 0) {
        send_message(client_socket, "you are not in a room\n");
        return;
    }

    person_t* person = &people[client_socket];
    room_t* room = &rooms[person->joined_room];

    char* format_message = malloc(sizeof(char) * (MAX_MSG_SIZE + 1));
    sprintf(format_message, "%s says: %s", person->name, message);
    for(int i = 0; i < room->capacity; i++) {
        if(room->people[i] != 0 && room->people[i] != client_socket) {
            send_message(room->people[i], format_message);
            send_terminal_message(room->people[i]);
        }
    }

    free(format_message);
}
