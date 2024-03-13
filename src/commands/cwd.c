/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** myftp
*/

#include <myftp.h>

char *handle_relative_path(const char *client_path, const char *parse_path)
{
    char *path = strdup(client_path);
    char *new_path = NULL;

    if (!path) {
        exit_error("strdup failed");
    }
    new_path = calloc(strlen(path) + strlen(parse_path) + 2, sizeof(char));
    if (!new_path) {
        exit_error("malloc failed");
    }
    strcpy(new_path, path);
    if (path[strlen(path) - 1] != '/') {
        strcat(new_path, "/");
    }
    strcat(new_path, parse_path);
    free(path);
    return new_path;
}

void cwd(const ftp_t *ftp, clients_t *client, const char *buffer)
{
    struct stat path_stat = {0};
    char *new_path = construct_new_path(client->path, buffer, 4);

    (void)ftp;
    if ((new_path == NULL) || (stat(new_path, &path_stat) != 0)
        || (!S_ISDIR(path_stat.st_mode)) || (access(new_path, R_OK) != 0)) {
        write_response(client->socket, 550);
        free(new_path);
    } else {
        free(client->path);
        client->path = new_path;
        write_response(client->socket, 250);
    }
}
