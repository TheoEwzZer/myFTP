/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** myftp
*/

#include <myftp.h>

void user(const ftp_t *ftp, clients_t *client, const char *buffer)
{
    const char *username = buffer + 5;

    (void)ftp;
    if (!username) {
        write_response(client->socket, 501);
        fprintf(stderr, "Invalid username from client %d\n", client->socket);
        return;
    }
    client->username = strdup(username);
    write_response(client->socket, 331);
}
