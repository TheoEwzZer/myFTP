/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** myftp
*/

/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** myftp
*/

#include <myftp.h>

void bind_and_listen(const ftp_t *ftp)
{
    const struct sockaddr *addr = (const struct sockaddr *)&ftp->server_addr;

    if (bind(ftp->server_socket, addr, ftp->server_addr_len) == -1) {
        exit_error("Bind failed");
    }
    if (listen(ftp->server_socket, 5) == -1) {
        exit_error("Listen failed");
    }
    fprintf(stderr, "Server listening on port %hu\n", ftp->port);
}

void init_fds(ftp_t *ftp)
{
    FD_ZERO(&ftp->read_fds);
    FD_ZERO(&ftp->write_fds);
    FD_SET(ftp->server_socket, &ftp->read_fds);
    FD_SET(ftp->server_socket, &ftp->write_fds);
    for (clients_t *clien = ftp->clients; clien != NULL; clien = clien->next) {
        FD_SET(clien->socket, &ftp->read_fds);
    }
}

void init_ftp(ftp_t *ftp, uint16_t port, char *path)
{
    ftp->port = port;
    ftp->path = path;
    ftp->max_fd = 0;
    ftp->clients = NULL;
    ftp->server_addr = (struct sockaddr_in){0};
    ftp->client_addr = (struct sockaddr_in){0};
    ftp->client_addr_len = sizeof(ftp->client_addr);
    ftp->server_addr_len = sizeof(ftp->server_addr);
    ftp->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    init_fds(ftp);
    if (ftp->server_socket == -1) {
        exit_error("Socket creation failed");
    }
    ftp->server_addr.sin_family = AF_INET;
    ftp->server_addr.sin_port = htons(port);
    ftp->server_addr.sin_addr.s_addr = INADDR_ANY;
    bind_and_listen(ftp);
}
