/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** myftp
*/

#include <myftp.h>

void dele(const ftp_t *ftp, clients_t *client, const char *buffer)
{
    char *path = construct_new_path(client->path, buffer, 5);

    (void)ftp;
    if (remove(path) == 0) {
        write_response(client->socket, 250);
    } else {
        write_response(client->socket, 550);
    }
    free(path);
}
