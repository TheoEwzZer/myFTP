/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** myftp
*/

#include <myftp.h>

void setup_address(const char *buffer, clients_t *client)
{
    char ip_str[INET_ADDRSTRLEN] = {0};
    uint8_t ip[4] = {0};
    uint8_t port[2] = {0};
    uint16_t port_num = 0;

    sscanf(buffer, "PORT %hhu,%hhu,%hhu,%hhu,%hhu,%hhu",
        &ip[0], &ip[1], &ip[2], &ip[3], &port[0], &port[1]);
    sprintf(ip_str, "%u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);
    port_num = (uint16_t)((port[0] * 256) + port[1]);
    client->addr.sin_family = AF_INET;
    client->addr.sin_port = htons(port_num);
    client->addr_len = sizeof(client->addr);
    inet_pton(AF_INET, ip_str, &client->addr.sin_addr);
}

void create_active_socket(clients_t *client)
{
    int data_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (data_socket == -1) {
        exit_error("Failed to create data socket");
    }
    if (connect(data_socket,
        (struct sockaddr *)&client->addr, client->addr_len) == -1) {
        write_response(client->socket, 200);
        close(data_socket);
        return;
    }
    write_response(client->socket, 200);
    client->data_socket = data_socket;
    client->mode = ACTIVE;
}

void port(const ftp_t *ftp, clients_t *client, const char *buffer)
{
    (void)ftp;
    setup_address(buffer, client);
    create_active_socket(client);
}
