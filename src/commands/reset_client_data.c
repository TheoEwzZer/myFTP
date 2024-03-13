/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** myftp
*/

#include <myftp.h>

void reset_client_data(clients_t *client)
{
    close(client->data_socket);
    client->data_socket = -1;
    client->mode = UNDEFINED;
}

bool check_arg(const char *buffer, const char *arg, struct stat *path_stat)
{
    return !((is_good_arg(buffer) == true) && ((arg == NULL)
        || (stat(arg, path_stat) != 0) || (access(arg, R_OK) != 0)));
}
