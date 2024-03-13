/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** myftp
*/

#include <myftp.h>

void pwd(const ftp_t *ftp, clients_t *client, const char *buffer)
{
    char *path = NULL;
    char message[512] = {0};

    (void)buffer;
    if (client->path != NULL) {
        path = strdup(client->path);
    } else {
        path = strdup(ftp->path);
    }
    if (!path) {
        exit_error("strdup failed");
    }
    snprintf(message, sizeof(message), "257 \"%s\" created.\r\n", path);
    write(client->socket, message, strlen(message));
    free(path);
}
