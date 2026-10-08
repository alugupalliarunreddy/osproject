#include "input.h"
#include <stdio.h>
int input_line(char *buffer, unsigned long size)
{
    if (buffer == NULL || size == 0 || fgets(buffer, (int)size, stdin) == NULL)
        return 0;
    return 1;
}
