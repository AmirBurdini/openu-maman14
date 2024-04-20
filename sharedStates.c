#include "data.h"

static Step currentCompilerState = programStart;
static char *path;
static unsigned currentLineNumber = 1;

void setCompilerStep(Step newState)
{
    currentCompilerState = newState;
}
Step getCompilerStep()
{
    Step current = currentCompilerState;
    return current;
}

void setFileNamePath(char *s)
{
    if (!*s)
        return;
    path = (char *)realloc(path, strlen(s) * sizeof(char *));
    strcpy(path, cloneString(s));
}

char *getFileNamePath()
{
    return cloneString(path);
}

void resetCurrentLineNumber()
{
    currentLineNumber = 1;
}
void increaseCurrentLineNumber()
{
    currentLineNumber++;
}
int getCurrentLineNumber()
{
    return currentLineNumber;
}
