#ifndef PARSER_H
#define PARSER_H
typedef enum {
    CMD_READ,
    CMD_TABLES,
    CMD_STATS,
    CMD_RESET,
    CMD_HELP,
    CMD_QUIT,
    CMD_UNKNOWN
} CommandType;

typedef struct {
    CommandType type;
    unsigned long value;
    int has_value;
} Command;

Command parse_command(const char *line);
#endif
