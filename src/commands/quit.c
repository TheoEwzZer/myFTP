/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** myftp
*/

#include <myftp.h>

void quit(const ftp_t *ftp, clients_t *client, const char *buffer)
{
    (void)ftp;
    (void)buffer;
    client->need_exit = true;
    write_response(client->socket, 221);
}
