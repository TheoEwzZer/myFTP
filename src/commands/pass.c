/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** myftp
*/

#include <myftp.h>

void pass(const ftp_t *ftp, clients_t *client, const char *buffer)
{
    const char *password = buffer + 5;

    if (client->username == NULL) {
        write_response(client->socket, 332);
        return;
    }
    if ((strcmp(password, "\r\n") != 0)
        || (strcmp(client->username, "Anonymous\r\n") != 0)) {
        write_response(client->socket, 530);
        fprintf(stderr, "Invalid password from client %d\n", client->socket);
        return;
    }
    write_response(client->socket, 230);
    client->path = strdup(ftp->path);
    client->is_logged = true;
}
