/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** myftp
*/

#include <myftp.h>

char *construct_new_path(const char *client_path,
    const char *buffer, int offset)
{
    const char *parse_path = buffer + offset;
    char *new_path = NULL;
    char *path = NULL;

    if ((parse_path[0] == '\0') || (parse_path[0] == '\n')) {
        return NULL;
    }
    if (strcmp(parse_path, "..\r\n") == 0) {
        path = strdup(client_path);
        new_path = strdup(dirname(path));
        free(path);
        return new_path;
    }
    if (parse_path[0] == '/') {
        new_path = strdup(parse_path);
    } else {
        new_path = handle_relative_path(client_path, parse_path);
    }
    new_path[strlen(new_path) - 2] = '\0';
    return new_path;
}

char *construct_new_path_list(char *client_path,
    const char *buffer, int offset)
{
    const char *parse_path = buffer + offset;
    char *new_path = NULL;
    char *path = NULL;

    if ((parse_path[0] == '\0') || (parse_path[0] == '\n')) {
        return client_path;
    }
    if (strcmp(parse_path, "..\r\n") == 0) {
        path = strdup(client_path);
        new_path = dirname(path);
        free(path);
    } else if (parse_path[0] == '/') {
        new_path = strdup(parse_path);
    } else {
        new_path = handle_relative_path(client_path, parse_path);
    }
    new_path[strlen(new_path) - 2] = '\0';
    return new_path;
}
