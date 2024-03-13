/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** myftp
*/

#pragma once

#include <arpa/inet.h>
#include <fcntl.h>
#include <libgen.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_PORT 65535

typedef enum mode {
    UNDEFINED,
    ACTIVE,
    PASSIVE
} ftp_mode_t;

typedef struct clients {
    int socket;
    int data_socket;
    struct sockaddr_in addr;
    socklen_t addr_len;
    char *username;
    char *path;
    struct clients *next;
    bool need_exit;
    bool is_logged;
    ftp_mode_t mode;
} clients_t;

typedef struct response {
    int code;
    const char *message;
} response_t;

typedef struct ftp {
    char *path;
    clients_t *clients;
    fd_set read_fds;
    fd_set write_fds;
    int max_fd;
    int server_socket;
    socklen_t client_addr_len;
    socklen_t server_addr_len;
    struct sockaddr_in client_addr;
    struct sockaddr_in server_addr;
    uint16_t port;
} ftp_t;

typedef void (*command_function)(const ftp_t *, clients_t *, const char *);

bool check_arg(const char *buffer, const char *arg, struct stat *path_stat);
bool check_data_connection(const clients_t *client, char *file_content);
bool check_fork_error(pid_t pid, const clients_t *client, char *file_content);
bool check_fork_error_list(pid_t pid, const clients_t *client, char *arg);
bool is_good_arg(const char *buffer);
bool open_dest_file(int dest_fd, const clients_t *client,
    char *file_content, const char *dest_filename);
char *construct_new_path(const char *client_path,
    const char *buffer, int offset);
char *construct_new_path_list(char *client_path,
    const char *buffer, int offset);
char *get_command(clients_t *client);
char *handle_relative_path(const char *client_path, const char *parse_path);
int create_passive_socket(clients_t *client);
void add_new_client(clients_t **list, int client_sock);
void bind_and_listen(const ftp_t *ftp);
void cdup(const ftp_t *ftp, clients_t *client, const char *buffer);
void check_client(ftp_t *ftp);
void create_active_socket(clients_t *client);
void cwd(const ftp_t *ftp, clients_t *client, const char *buffer);
void dele(const ftp_t *ftp, clients_t *client, const char *buffer);
void disconnect_client(ftp_t *ftp, clients_t *client);
void exit_error(const char *str) __attribute__((noreturn));
void handle_child_process(clients_t *client,
    char *file_content, int dest_fd) __attribute__((noreturn));
void handle_child_process_list(clients_t *client,
    const char *arg) __attribute__((noreturn));
void handle_child_process_retr(clients_t *client,
    char *file_content, int fd) __attribute__((noreturn));
bool handle_error_list(const clients_t *client, char *arg);
void handle_disconnection(ftp_t *ftp);
void help(const ftp_t *ftp, clients_t *client, const char *buffer);
void init_fds(ftp_t *ftp);
void init_ftp(ftp_t *ftp, uint16_t port, char *path);
void list(const ftp_t *ftp, clients_t *client, const char *buffer);
void loop_ftp(ftp_t *ftp) __attribute__((noreturn));
void myftp(uint16_t port, char *path) __attribute__((noreturn));
void noop(const ftp_t *ftp, clients_t *client, const char *buffer);
void pass(const ftp_t *ftp, clients_t *client, const char *buffer);
void pasv(const ftp_t *ftp, clients_t *client, const char *buffer);
void port(const ftp_t *ftp, clients_t *client, const char *buffer);
void process_command(const ftp_t *ftp, clients_t *client, const char *buffer);
void pwd(const ftp_t *ftp, clients_t *client, const char *buffer);
void quit(const ftp_t *ftp, clients_t *client, const char *buffer);
void remove_client(clients_t **list, int client_socket);
void reset_client_data(clients_t *client);
void retr(const ftp_t *ftp, clients_t *client, const char *buffer);
void select_accept(ftp_t *ftp);
void send_pasv_response(const ftp_t *ftp, clients_t *client, int socket);
void send_welcome_message(int client_socket);
void setup_address(const char *buffer, clients_t *client);
void stor(const ftp_t *ftp, clients_t *client, const char *buffer);
void user(const ftp_t *ftp, clients_t *client, const char *buffer);
void write_response(int fd, int code);
