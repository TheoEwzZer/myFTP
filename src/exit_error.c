/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** myftp
*/

#include <myftp.h>

void exit_error(const char *str)
{
    perror(str);
    exit(84);
}
