/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** myftp
*/

#include <myftp.h>

void handle_child_process_retr(clients_t *client, char *file_content, int fd)
{
    ssize_t read_bytes = 0;

    if (client->mode == PASSIVE) {
        client->data_socket = accept(client->data_socket,
            (struct sockaddr *)&client->addr, &client->addr_len);
    }
    if (client->data_socket < 0) {
        write_response(client->socket, 425);
        free(file_content);
        exit(1);
    }
    read_bytes = read(fd, file_content, 1023);
    while (read_bytes > 0) {
        write(client->data_socket, file_content, (size_t)read_bytes);
        read_bytes = read(fd, file_content, 1023);
    }
    write_response(client->socket, 226);
    exit(0);
}

void retr(const ftp_t *ftp, clients_t *client, const char *buffer)
{
    const char *path = construct_new_path(client->path, buffer, 5);
    int fd = open(path, O_RDONLY);
    char *file_content = calloc(1024, sizeof(char));
    pid_t pid = 0;

    (void)ftp;
    if (!check_data_connection(client, file_content))
        return;
    if (!open_dest_file(fd, client, file_content, path))
        return;
    pid = fork();
    if (!check_fork_error(pid, client, file_content))
        return;
    if (pid == 0)
        handle_child_process_retr(client, file_content, fd);
    free(file_content);
    close(client->data_socket);
    close(fd);
    client->mode = UNDEFINED;
    client->data_socket = -1;
}
