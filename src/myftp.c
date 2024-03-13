/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** myftp
*/

#include <myftp.h>

void myftp(uint16_t port, char *path)
{
    ftp_t *ftp = malloc(sizeof(ftp_t));
    struct stat path_stat = {0};

    if ((stat(path, &path_stat) != 0)
    || (!S_ISDIR(path_stat.st_mode)) || (access(path, R_OK) != 0)) {
        exit_error("");
    }
    init_ftp(ftp, port, path);
    loop_ftp(ftp);
    free(ftp);
}

void send_welcome_message(int client_socket)
{
    write_response(client_socket, 220);
    fprintf(stderr, "New client connected on socket %d\n", client_socket);
}

void select_accept(ftp_t *ftp)
{
    int client_sock = 0;
    struct sockaddr *addr = (struct sockaddr *)&ftp->server_addr;

    init_fds(ftp);
    if (select(ftp->max_fd + 1, &ftp->read_fds,
        &ftp->write_fds, NULL, NULL) == -1)
        exit_error("Select failed");
    if (!FD_ISSET(ftp->server_socket, &ftp->read_fds)) {
        return;
    }
    client_sock = accept(ftp->server_socket, addr, &ftp->server_addr_len);
    if (client_sock == -1)
        exit_error("Accept failed");
    ftp->max_fd = (client_sock > ftp->max_fd) ? client_sock : ftp->max_fd;
    add_new_client(&ftp->clients, client_sock);
}

void loop_ftp(ftp_t *ftp)
{
    ftp->max_fd = ftp->server_socket;
    while (1) {
        select_accept(ftp);
        check_client(ftp);
        handle_disconnection(ftp);
    }
}
