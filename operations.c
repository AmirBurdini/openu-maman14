#include "data.h"

static const Operation operations[OP_SIZE] = {
    {0x0001, 0, "mov", {1, 1, 1, 1}, {0, 1, 1, 1}},
    {0x0002, 1, "cmp", {1, 1, 1, 1}, {1, 1, 1, 1}},
    {0x0004, 2, "add", {1, 1, 1, 1}, {0, 1, 1, 1}},
    {0x0004, 3, "sub", {1, 1, 1, 1}, {0, 1, 1, 1}},
    {0x0010, 4, "not", {0, 0, 0, 0}, {0, 1, 1, 1}},
    {0x0020, 5, "clr", {0, 0, 0, 0}, {0, 1, 1, 1}},
    {0x0020, 6, "lea", {0, 1, 1, 0}, {0, 1, 1, 1}},
    {0x0020, 7, "inc", {0, 0, 0, 0}, {0, 1, 1, 1}},
    {0x0020, 8, "dec", {0, 0, 0, 0}, {0, 1, 1, 1}},
    {0x0200, 9, "jmp", {0, 0, 0, 0}, {0, 1, 0, 1}},
    {0x0200, 10, "bne", {0, 0, 0, 0}, {0, 1, 0, 1}},
    {0x0200, 11, "jsr", {0, 0, 0, 0}, {0, 1, 0, 1}},
    {0x1000, 12, "red", {0, 0, 0, 0}, {0, 1, 1, 1}},
    {0x2000, 13, "prn", {0, 0, 0, 0}, {1, 1, 1, 1}},
    {0x4000, 14, "rts", {0, 0, 0, 0}, {0, 0, 0, 0}},
    {0x8000, 15, "hlt", {0, 0, 0, 0}, {0, 0, 0, 0}},
};

/* @ Function: Bool isOperationName(char *s)
   @ Arguments: char *s - the operation's name.
   @ Description: checks if the operation name is valid.
   @ Returns: returns true if the operation name is valid, false otherwise.
*/
Bool isOperationName(char *s)
{
    return getOpIndex(s) != -1 ? True : False;
}

/* Function: Operation *getOperationByName(char *s)
   @ Arguments: char *s- operation's name.
   @ Description: checks what is the opcode for the operation name given.
   @ Returns: returns the relevant Operation for the given argument name, else returns NULL.
*/
const Operation *getOperationByName(char *s)
{
    int i = getOpIndex(s);

    return i != -1 ? &operations[i] : NULL;
}

/* @ Function: int getOpIndex(char *s)
   @ Arguments: char *s- operation's name.
   @ Description: searches for the operation it got in the operations table.
   @ Returns: returns the relevant operation's opcode index, ot -1 if the operation name isn't valid 
*/
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