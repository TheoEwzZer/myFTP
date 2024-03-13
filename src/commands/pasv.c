/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** myftp
*/

#include <myftp.h>

int create_passive_socket(clients_t *client)
{
    int data_socket = socket(AF_INET, SOCK_STREAM, 0);
    int x = 0;

    if (data_socket == -1) {
        exit_error("Failed to create data socket");
    }
    x = bind(data_socket, (struct sockaddr *)&client->addr, client->addr_len);
    if (x == -1) {
        exit_error("Failed to bind data socket");
    }
    return data_socket;
}

void send_pasv_response(const ftp_t *ftp, clients_t *client, int socket)
{
    uint16_t port = 0;
    uint8_t port1 = 0;
    uint8_t port2 = 0;
    uint8_t ip[4] = {0};
    char response[256] = {0};

    if (getsockname(socket,
        (struct sockaddr *)&client->addr, &client->addr_len) == -1)
        exit_error("Failed to get data socket name");
    port = ntohs(client->addr.sin_port);
    port1 = (uint8_t)(port / 256);
    port2 = (uint8_t)(port % 256);
    memcpy(ip, &ftp->server_addr.sin_addr.s_addr, 4);
    sprintf(response, "227 Entering Passive Mode (%u,%u,%u,%u,%u,%u)\r\n",
        ip[0], ip[1], ip[2], ip[3], port1, port2);
    if (listen(socket, 1) == -1)
        exit_error("Failed to listen on data socket");
    write(client->socket, response, strlen(response));
    client->data_socket = socket;
    client->mode = PASSIVE;
}

void pasv(const ftp_t *ftp, clients_t *client, const char *buffer)
{
    int socket = 0;

    (void)buffer;
    client->addr.sin_family = AF_INET;
    client->addr.sin_addr.s_addr = INADDR_ANY;
    client->addr.sin_port = 0;
    client->addr_len = sizeof(client->addr);
    socket = create_passive_socket(client);
    send_pasv_response(ftp, client, socket);
}
