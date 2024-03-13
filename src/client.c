/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** myftp
*/

#include <myftp.h>

void add_new_client(clients_t **list, int client_socket)
{
    clients_t *new_client = malloc(sizeof(clients_t));
    clients_t *current = *list;

    new_client->socket = client_socket;
    new_client->next = NULL;
    new_client->username = NULL;
    new_client->path = NULL;
    new_client->need_exit = false;
    new_client->is_logged = false;
    new_client->data_socket = -1;
    new_client->mode = UNDEFINED;
    if (!current) {
        *list = new_client;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_client;
    }
    send_welcome_message(client_socket);
}

void remove_client(clients_t **list, int client_socket)
{
    clients_t *current = *list;
    clients_t *prev = NULL;

    if ((current != NULL) && (current->socket == client_socket)) {
        *list = current->next;
        free(current);
        return;
    }
    while ((current != NULL) && (current->socket != client_socket)) {
        prev = current;
        current = current->next;
    }
    if (!current) {
        return;
    }
    prev->next = current->next;
    free(current);
}

void process_command(const ftp_t *ftp, clients_t *client, const char *buffer)
{
    const char *commands[15] = {
        "USER", "PASS", "QUIT", "PWD", "CWD", "CDUP", "LIST", "DELE",
        "NOOP", "HELP", "PASV", "PORT", "RETR", "STOR", NULL
    };
    const command_function commands_functions[15] = {
        &user, &pass, &quit, &pwd, &cwd, &cdup, &list, &dele,
        &noop, &help, &pasv, &port, &retr, &stor, NULL
    };

    for (int i = 0; commands[i] != NULL; i++) {
        if (strncmp(buffer, commands[i], strlen(commands[i])) != 0)
            continue;
        if ((!client->is_logged) && (i > 2)) {
            write_response(client->socket, 530);
            return;
        }
        commands_functions[i](ftp, client, buffer);
        return;
    }
    write_response(client->socket, 500);
}

char *get_command(clients_t *client)
{
    char *command = calloc(1024, sizeof(char));
    char *buffer = calloc(1024, sizeof(char));
    ssize_t nbytes = 0;

    nbytes = read(client->socket, buffer, 1023);
    if (nbytes <= 0) {
        client->need_exit = true;
        free(buffer);
        free(command);
        return NULL;
    }
    command = strcat(command, buffer);
    while ((nbytes > 0) && (buffer[nbytes - 1] != '\n')) {
        nbytes = read(client->socket, buffer, 1023);
        command = strcat(command, buffer);
    }
    free(buffer);
    return command;
}

void check_client(ftp_t *ftp)
{
    char *command = NULL;
    clients_t *client = ftp->clients;

    for (; client != NULL; client = client->next) {
        if (!FD_ISSET(client->socket, &ftp->read_fds)) {
            continue;
        }
        command = get_command(client);
        if (command == NULL) {
            continue;
        }
        printf("Client %d sent: %s", client->socket, command);
        process_command(ftp, client, command);
        free(command);
    }
}
