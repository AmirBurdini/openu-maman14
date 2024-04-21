#include "data.h"

const char *regs[REGS_SIZE] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"};

Bool isRegistery(char *s)
{
    int len = strlen(s);
    int i = 0;
    if (s[0] == 'r' && len == 2)
    {
        while (i < REGS_SIZE)
        {
            if ((strcmp(regs[i], s) == 0))
                return True;
            i++;
        }
    }
    return False;
}

int getRegisteryNumber(char *s)
{
    s++;
    return atoi(s);
}