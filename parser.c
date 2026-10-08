#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Command parse_command(const char *line)
{
    Command c = {CMD_UNKNOWN, 0, 0};
    char word[32];

    if (line == NULL) return c;
    if (sscanf(line, "%31s", word) != 1) return c;

    if (strcmp(word, "read") == 0) {
        unsigned long value;
        if (sscanf(line, "%*s %lu", &value) == 1) {
            c.type = CMD_READ;
            c.value = value;
            c.has_value = 1;
        }
    } else if (strcmp(word, "tables") == 0) c.type = CMD_TABLES;
    else if (strcmp(word, "stats") == 0) c.type = CMD_STATS;
    else if (strcmp(word, "reset") == 0) c.type = CMD_RESET;
    else if (strcmp(word, "help") == 0) c.type = CMD_HELP;
    else if (strcmp(word, "quit") == 0 || strcmp(word, "exit") == 0) c.type = CMD_QUIT;

    return c;
}
