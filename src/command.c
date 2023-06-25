#include "command.h"

void exit_command(int client_socket, char* command)
{
    end_connection(client_socket);
}

void rooms_command(int client_socket, char* command)
{
    print_rooms(client_socket);
}

void join_command(int client_socket, char* command)
{
    send_message(client_socket, "join\n");
}

void leave_command(int client_socket, char* command)
{
    send_message(client_socket, "leave\n");
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

    add_room(room_name, capacity);
}

void delete_command(int client_socket, char* command)
{
    char *token = strtok(command, " ");
    int room_id = atoi(strtok(NULL, "\r\n"));

    if(room_id == 0) {
        send_message(client_socket, "invalid command\n");
        return;
    }
    
    remove_room(room_id);
    send_message(client_socket, "room deleted\n");
}

void help_command(int client_socket, char* command)
{
    send_message(client_socket, "help\n");
}

typedef struct {
    char* command;
    void (*function)(int, char*);
} command_t;

command_t commands[] = {
    {"/exit\r\n", exit_command},
    {"/rooms\r\n", rooms_command},
    {"/join ", join_command},
    {"/leave\r\n", leave_command},
    {"/create ", create_command},
    {"/delete ", delete_command},
    {"/help\r\n", help_command},
    {NULL, NULL}
};

void execute_command(int client_socket, char* command)
{
    for(int i = 0; commands[i].command != NULL; i++) {
        if(strncmp(command, commands[i].command, strlen(commands[i].command)) == 0) {
            commands[i].function(client_socket, command);
            return;
        }
    }

    send_message(client_socket, "invalid command\n");
}