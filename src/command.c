#include "command.h"

void exit_command(int client_socket, __attribute__((unused)) char* command)
{
    end_connection(client_socket);
    leave_room(client_socket);
}

void list_command(int client_socket, __attribute__((unused)) char* command)
{
    list_rooms(client_socket);
}

void members_command(int client_socket, __attribute__((unused)) char* command)
{
    list_people(client_socket);
}

void join_command(int client_socket, char* command)
{
    char *token = strtok(command, " ");
    int room_id = atoi(strtok(NULL, " "));

    if(room_id == 0) {
        send_message(client_socket, "invalid command\n");
        return;
    }

    token = strtok(NULL, " ");
    char* name = strtok(token, "\r\n");

    if(name == NULL) {
        send_message(client_socket, "invalid command\n");
        return;
    }

    join_room(client_socket, room_id, name);
}

void leave_command(int client_socket, __attribute__((unused)) char* command)
{
    leave_room(client_socket);
}

void create_command(int client_socket, char* command)
{
    char *token = strtok(command, " ");
    char *room_name = strtok(NULL, " ");

    if(room_name == NULL) {
        send_message(client_socket, "invalid command\n");
        return;
    }

    token = strtok(NULL, " ");
    int capacity = atoi(strtok(token, "\r\n"));

    if(capacity == 0) {
        send_message(client_socket, "invalid command\n");
        return;
    }

    if(capacity > MAX_CAPACITY) {
        send_message(client_socket, "capacity too large\n");
        return;
    }

    add_room(room_name, capacity);
}

void delete_command(int client_socket, char* command)
{
    strtok(command, " ");
    int room_id = atoi(strtok(NULL, "\r\n"));

    if(room_id == 0) {
        send_message(client_socket, "invalid command\n");
        return;
    }
    
    remove_room(client_socket, room_id);
}

void help_command(int client_socket, __attribute__((unused)) char* command)
{
    send_message(client_socket, "Commands:\n");
    send_message(client_socket, "\t/help : show this message\n");
    send_message(client_socket, "\t/create <room_name> <capacity> : create a new room\n");
    send_message(client_socket, "\t/delete <room_id> : delete a room\n");
    send_message(client_socket, "\t/join <room_id> <name> : join a room\n");
    send_message(client_socket, "\t/leave : leave the current room\n");
    send_message(client_socket, "\t/list : list all rooms\n");
    send_message(client_socket, "\t/members : list all members in the current room\n");
    send_message(client_socket, "\t<msg> : send a message to the current room\n");
    send_message(client_socket, "\t/exit : exit the chat\n");
}

typedef struct {
    char* command;
    void (*function)(int, char*);
} command_t;

command_t commands[] = {
    {"/exit\r\n", exit_command},
    {"/list\r\n", list_command},
    {"/members\r\n", members_command},
    {"/join ", join_command},
    {"/leave\r\n", leave_command},
    {"/create ", create_command},
    {"/delete ", delete_command},
    {"/help\r\n", help_command},
    {NULL, NULL}
};

void execute_command(int client_socket, char* command)
{
    if(strncmp(command, "/", 1) == 0) {
        for(int i = 0; commands[i].command != NULL; i++) {
            if(strncmp(command, commands[i].command, strlen(commands[i].command)) == 0) {
                commands[i].function(client_socket, command);
                return;
            }
        }

        send_message(client_socket, "invalid command\n");
    }
    else
    {
        send_message2room(client_socket, command);
    }
}