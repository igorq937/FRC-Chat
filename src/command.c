#include "command.h"

void exit_command(int client_socket, char* command)
{
    send_message(client_socket, "bye\n");
    end_connection(client_socket);
}

void rooms_command(int client_socket, char* command)
{
    send_message(client_socket, "rooms\n");
}

void join_command(int client_socket, char* command)
{
    send_message(client_socket, "join\n");
}

void leave_command(int client_socket, char* command)
{
    send_message(client_socket, "leave\n");
}

char * get_room_name(char* command)
{
    char* room_name = strtok(command, " ");
    room_name = strtok(NULL, " ");
    room_name = strtok(room_name, "\r\n");
    return room_name;
}

void create_command(int client_socket, char* command)
{
    char* room_name = get_room_name(command);
    if(room_name == NULL) {
        send_message(client_socket, "invalid room name\n");
        return;
    }

    send_message(client_socket, "room created\n");

}

void delete_command(int client_socket, char* command)
{
    char* room_name = get_room_name(command);
    if(room_name == NULL) {
        send_message(client_socket, "invalid room name\n");
        return;
    }

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
    {"/join\r\n", join_command},
    {"/leave\r\n", leave_command},
    {"/create", create_command},
    {"/delete", delete_command},
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