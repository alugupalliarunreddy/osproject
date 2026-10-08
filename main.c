#include "vmem.h"
#include "input.h"
#include "parser.h"
#include "translate.h"
#include "stats.h"
#include "simulator.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void help(void)
{
    puts("\nCommands:");
    puts("  read <address>  Translate a virtual address");
    puts("  tables          Display page and frame tables");
    puts("  stats           Display memory statistics");
    puts("  reset           Reset the simulator");
    puts("  help            Display commands");
    puts("  quit            Exit");
}

static int read_config(size_t *pages, size_t *frames, VmPolicy *policy)
{
    char line[64];

    printf("Number of virtual pages (1-%u): ", VM_MAX_PAGES);
    if (!input_line(line, sizeof(line))) return 0;
    *pages = (size_t)strtoul(line, NULL, 10);

    printf("Number of physical frames (1-%u): ", VM_MAX_FRAMES);
    if (!input_line(line, sizeof(line))) return 0;
    *frames = (size_t)strtoul(line, NULL, 10);

    printf("Replacement policy (FIFO/LRU): ");
    if (!input_line(line, sizeof(line))) return 0;

    if (strncmp(line, "FIFO", 4) == 0 || strncmp(line, "fifo", 4) == 0)
        *policy = VM_FIFO;
    else if (strncmp(line, "LRU", 3) == 0 || strncmp(line, "lru", 3) == 0)
        *policy = VM_LRU;
    else
        return 0;

    return 1;
}

int main(void)
{
    VmManager vm;
    size_t pages, frames;
    VmPolicy policy;
    char line[128];

    puts("==========================================");
    puts(" Virtual Memory Management Utility (VMU)");
    puts("==========================================");

    if (!read_config(&pages, &frames, &policy) ||
        simulator_init(&vm, pages, frames, policy) != 0) {
        fprintf(stderr, "Invalid VM configuration.\n");
        return EXIT_FAILURE;
    }

    help();

    for (;;) {
        printf("\nvm> ");
        if (!input_line(line, sizeof(line))) break;
        line[strcspn(line, "\n")] = '\0';

        Command cmd = parse_command(line);

        if (cmd.type == CMD_QUIT) break;

        switch (cmd.type) {
        case CMD_READ:
            if (!cmd.has_value || cmd.value > UINT16_MAX) {
                puts("Usage: read <address 0-65535>");
                break;
            }
            {
                uint16_t physical;
                if (translate_address(&vm, (uint16_t)cmd.value, &physical) != 0)
                    puts("Address is outside the configured virtual address space.");
                else
                    printf("VA %lu -> PA %u\n", cmd.value, physical);
            }
            break;
        case CMD_TABLES:
            simulator_tables(&vm);
            break;
        case CMD_STATS:
            stats_print(&vm);
            break;
        case CMD_RESET:
            simulator_reset(&vm);
            puts("Simulator reset.");
            break;
        case CMD_HELP:
            help();
            break;
        default:
            if (line[0] != '\0') puts("Unknown command. Type 'help'.");
            break;
        }
    }

    stats_print(&vm);
    return EXIT_SUCCESS;
}
