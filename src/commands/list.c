/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** myftp
*/

#include <myftp.h>

void handle_child_process_list(clients_t *client, const char *arg)
{
    if (client->mode == PASSIVE) {
        client->data_socket = accept(client->data_socket,
            (struct sockaddr *)&client->addr, &client->addr_len);
    }
    if (client->data_socket < 0) {
        write_response(client->socket, 425);
        exit(1);
    }
    dup2(client->data_socket, STDOUT_FILENO);
    execlp("ls", "ls", "-l", arg, NULL);
    exit(0);
}

bool handle_error_list(const clients_t *client, char *arg)
{
    if ((client->data_socket < 0) || (client->mode == UNDEFINED)) {
        write_response(client->socket, 425);
        if (arg != NULL) {
            free(arg);
        }
        return false;
    }
    return true;
}

bool check_fork_error_list(pid_t pid, const clients_t *client, char *arg)
{
    if (pid < 0) {
        write_response(client->socket, 451);
        if (arg != NULL) {
            free(arg);
        }
        return false;
    }
    return true;
}

bool is_good_arg(const char *buffer)
{
    char *arg = strdup(buffer + 5);

    if (strlen(arg) > 2) {
        return true;
    } else {
        free(arg);
        return false;
    }
}

void list(const ftp_t *ftp, clients_t *client, const char *buffer)
{
    pid_t pid = 0;
    struct stat path_stat = {0};
    char *arg = construct_new_path_list(client->path, buffer, 5);

    (void)ftp;
    if (!handle_error_list(client, arg))
        return;
    write_response(client->socket, 150);
    if (!check_arg(buffer, arg, &path_stat)) {
        write_response(client->socket, 550);
        free(arg);
        return;
    }
    pid = fork();
    if (!check_fork_error_list(pid, client, arg))
        return;
    if (pid == 0)
        handle_child_process_list(client, arg);
    write_response(client->socket, 226);
    reset_client_data(client);
}
