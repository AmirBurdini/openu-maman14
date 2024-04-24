#include "data.h"

static const Operation operations[OP_SIZE] = {
    {0, "mov", {1, 1, 1, 1}, {0, 1, 1, 1}},
    {1, "cmp", {1, 1, 1, 1}, {1, 1, 1, 1}},
    {2, "add", {1, 1, 1, 1}, {0, 1, 1, 1}},
    {3, "sub", {1, 1, 1, 1}, {0, 1, 1, 1}},
    {4, "not", {0, 0, 0, 0}, {0, 1, 1, 1}},
    {5, "clr", {0, 0, 0, 0}, {0, 1, 1, 1}},
    {6, "lea", {0, 1, 1, 0}, {0, 1, 1, 1}},
    {7, "inc", {0, 0, 0, 0}, {0, 1, 1, 1}},
    {8, "dec", {0, 0, 0, 0}, {0, 1, 1, 1}},
    {9, "jmp", {0, 0, 0, 0}, {0, 1, 0, 1}},
    {10, "bne", {0, 0, 0, 0}, {0, 1, 0, 1}},
    {11, "jsr", {0, 0, 0, 0}, {0, 1, 0, 1}},
    {12, "red", {0, 0, 0, 0}, {0, 1, 1, 1}},
    {13, "prn", {0, 0, 0, 0}, {1, 1, 1, 1}},
    {14, "rts", {0, 0, 0, 0}, {0, 0, 0, 0}},
    {15, "hlt", {0, 0, 0, 0}, {0, 0, 0, 0}},
};


Bool isOperationName(char *s)
{
    return getOpIndex(s) != -1 ? True : False;
}

const Operation *getOperationByName(char *s)
{
    int i = getOpIndex(s);

    return i != -1 ? &operations[i] : NULL;
}

int getOpIndex(char *s)
{
    int i = 0;
    while (i < OP_SIZE)
    {
        if (strcmp(operations[i].keyword, s) == 0)
            return i;
        i++;
    }
    return -1;
}