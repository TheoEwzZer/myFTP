/*
** EPITECH PROJECT, 2024
** my_ftp
** File description:
** my_ftp
*/

#include <myftp.h>

static const response_t responses[16] = {
    {150, "File status okay; about to open data connection"},
    {200, "Command okay"},
    {220, "Service ready for new user"},
    {221, "Service closing control connection"},
    {226, "Closing data connection"},
    {230, "User logged in, proceed"},
    {250, "Requested file action okay, completed"},
    {331, "User name okay, need password"},
    {332, "Need account for login"},
    {425, "Can't open data connection"},
    {451, "Requested action aborted. Local error in processing"},
    {500, "Syntax error, command unrecognized"},
    {501, "Syntax error in parameters or arguments"},
    {530, "Not logged in"},
    {550, "Requested action not taken"},
    {0, NULL},
};

void write_response(int fd, int code)
{
    char response[256] = {0};

    for (size_t i = 0; responses[i].message != 0; i++) {
        if (responses[i].code == code) {
            sprintf(response, "%d %s.\r\n", code, responses[i].message);
            write(fd, response, strlen(response));
            return;
        }
    }
}
