/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** myftp
*/

#include <myftp.h>

void noop(const ftp_t *ftp, clients_t *client, const char *buffer)
{
    (void)ftp;
    (void)buffer;
    write_response(client->socket, 200);
}
