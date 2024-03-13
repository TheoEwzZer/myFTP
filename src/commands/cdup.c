/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** myftp
*/

#include <myftp.h>

void cdup(const ftp_t *ftp, clients_t *client, const char *buffer)
{
    char *path = NULL;
    const char *parent_dir = NULL;
    struct stat path_stat = {0};

    (void)buffer;
    path = client->path != NULL ? strdup(client->path) : strdup(ftp->path);
    if (!path) {
        exit_error("strdup failed");
    }
    parent_dir = dirname(path);
    if ((stat(parent_dir, &path_stat) != 0)
    || (!S_ISDIR(path_stat.st_mode)) || (access(parent_dir, R_OK) != 0)) {
        write_response(client->socket, 550);
    } else {
        free(client->path);
        client->path = strdup(parent_dir);
        write_response(client->socket, 200);
    }
    free(path);
}
