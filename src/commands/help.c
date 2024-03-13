/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** myftp
*/

#include <myftp.h>

void help(const ftp_t *ftp, clients_t *client, const char *buffer)
{
    (void)ftp;
    (void)buffer;
    write(client->socket, "214-The following commands are recognized\r\n", 44);
    write(client->socket, "USER PASS CWD CDUP QUIT DELE PWD\r\n", 34);
    write(client->socket, "PASV PORT HELP NOOP RETR STOR LIST\r\n", 36);
    write(client->socket, "214 Help message.\r\n", 19);
}
