/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** myftp
*/

#include <myftp.h>

void disconnect_client(ftp_t *ftp, clients_t *client)
{
    FD_CLR(client->socket, &ftp->read_fds);
    FD_CLR(client->socket, &ftp->write_fds);
    fprintf(stderr, "Client %d disconnected\n", client->socket);
    write_response(client->socket, 221);
    close(client->socket);
    client->socket = 0;
    if (client->data_socket != 0) {
        close(client->data_socket);
        client->data_socket = -1;
        client->mode = UNDEFINED;
    }
    remove_client(&ftp->clients, client->socket);
}

void handle_disconnection(ftp_t *ftp)
{
    clients_t *client = ftp->clients;
    clients_t *next_client = NULL;

    while (client != NULL) {
        next_client = client->next;
        if (!FD_ISSET(client->socket, &ftp->read_fds)) {
            client = next_client;
            continue;
        }
        if (client->need_exit) {
            disconnect_client(ftp, client);
        }
        client = next_client;
    }
}
