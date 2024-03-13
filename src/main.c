/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** myftp
*/

#include <myftp.h>

int main(int argc, char **argv)
{
    char *endptr = NULL;
    long port_num = 0;

    if ((argc == 2) && (strcmp(argv[1], "-help") == 0)) {
        printf("USAGE: ./myftp port path\n");
        printf("\tport is number on which the server socket listens\n");
        printf("\tpath is to the home directory for the Anonymous user\n");
        return 0;
    }
    if (argc != 3) {
        printf("Invalid arguments. Use -help for usage instructions.\n");
        return 84;
    }
    port_num = strtol(argv[1], &endptr, 10);
    if ((*endptr != '\0') || (port_num < 1) || (port_num > MAX_PORT)) {
        printf("Invalid port given. It has to be a value from 1 to 65535.\n");
        return 84;
    }
    myftp((uint16_t)port_num, argv[2]);
    return 0;
}
