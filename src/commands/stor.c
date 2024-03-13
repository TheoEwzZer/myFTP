/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** myftp
*/

#include <myftp.h>

bool check_data_connection(const clients_t *client, char *file_content)
{
    if ((client->data_socket < 0) || (client->mode == UNDEFINED)) {
        write_response(client->socket, 425);
        free(file_content);
        return false;
    }
    write_response(client->socket, 150);
    return true;
}

bool open_dest_file(int dest_fd, const clients_t *client,
    char *file_content, const char *dest_filename)
{
    if (dest_filename == NULL) {
        write_response(client->socket, 501);
        free(file_content);
        return false;
    }
    if (dest_fd == -1) {
        write_response(client->socket, 550);
        free(file_content);
        return false;
    }
    return true;
}

bool check_fork_error(pid_t pid, const clients_t *client, char *file_content)
{
    if (pid < 0) {
        write_response(client->socket, 451);
        free(file_content);
        return false;
    }
    return true;
}

void handle_child_process(clients_t *client, char *file_content, int dest_fd)
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
    read_bytes = read(client->data_socket, file_content, 1023);
    while (read_bytes > 0) {
        write(dest_fd, file_content, (size_t)read_bytes);
        read_bytes = read(client->data_socket, file_content, 1023);
    }
    write_response(client->socket, 226);
    exit(0);
}

void stor(const ftp_t *ftp, clients_t *client, const char *buffer)
{
    const char *dest_filename = construct_new_path(ftp->path, buffer, 5);
    int dest_fd = open(dest_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    char *file_content = calloc(1024, sizeof(char));
    pid_t pid = 0;

    (void)ftp;
    if (!check_data_connection(client, file_content))
        return;
    if (!open_dest_file(dest_fd, client, file_content, dest_filename))
        return;
    pid = fork();
    if (!check_fork_error(pid, client, file_content))
        return;
    if (pid == 0)
        handle_child_process(client, file_content, dest_fd);
    free(file_content);
    close(client->data_socket);
    close(dest_fd);
    client->mode = UNDEFINED;
    client->data_socket = -1;
}
