#include "data.h"

extern void fileCreationFailure(char *fileName);
static char *(*baseFileName)() = &getFileNamePath;


void exportFilesMainHandler()
{
    printf("Code ingested successfully, exporting files.\n");
    generateObFile();
    if (entriesExist())
        createEntriesFile();
    if (externalsExist())
        createExternalsFile();
}

void generateObFile()
{
    FILE *ob;
    char *fileName = (*baseFileName)();
    strcat(fileName, ".ob");
    ob = fopen(fileName, "w+");

    if (ob != NULL)
    {
        writeMemoryImageToObFile(ob);
        fclose(ob);
        free(fileName);
    }
    else
        fileCreationFailure(fileName);
}

void createEntriesFile()
{
    FILE *ent;
    char *fileName = (*baseFileName)();
    strcat(fileName, ".ent");
    ent = fopen(fileName, "w+");

    if (ent != NULL)
    {
        writeEntriesToFile(ent);
        fclose(ent);
        free(fileName);
    }
    else
        fileCreationFailure(fileName);
}

void createExternalsFile()
{
    FILE *ext;
    char *fileName = (*baseFileName)();
    strcat(fileName, ".ext");
    ext = fopen(fileName, "w+");
    if (ext != NULL)
    {   
        writeExternalsToFile(ext);
        fclose(ext);
        free(fileName);
    }
    else
        fileCreationFailure(fileName);
}