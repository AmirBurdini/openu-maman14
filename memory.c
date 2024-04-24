#include "data.h"

static BinaryWord *binaryImg = NULL;
unsigned static IC = MEMORY_START;
unsigned static DC = 0;
unsigned static ICF = 0;
unsigned static DCF = 0;

extern char *numToBin(int num);
unsigned getDC() { return DC; }
unsigned getIC() { return IC; }
unsigned getICF() { return ICF; }
unsigned getDCF() { return DCF; }

void increaseDataCounter(int amount)
{
    DC += amount;
}

void increaseInstructionCounter(int amount)
{
    IC += amount;
}

void allocMemoryImg()
{
    const int totalSize = DCF - MEMORY_START;
    int i, j;

    if (binaryImg != NULL)
        free(binaryImg);

    binaryImg = (BinaryWord*)malloc(totalSize * sizeof(BinaryWord));
    for (i = 0; i < totalSize; i++)
    {
        for (j = 0; j < BINARY_WORD_SIZE; j++)
        {
            binaryImg[i].digit[j].on = 0;
        }
    }
}

void resetMemoryCounters()
{
    IC = MEMORY_START;
    DC = 0;
    ICF = 0;
    DCF = 0;
}

void addWord(int value, DataType type)
{
    if (type == Code)
        addWordToCodeImage(numToBin(value));
    else if (type == Data)
        addWordToDataImage(numToBin(value));
}

void addWordToDataImage(char *s)
{
    wordStringToWordObj(s, Data);
    DC++;
}

void addWordToCodeImage(char *s)
{
    wordStringToWordObj(s, Code);
    IC++;
}

void wordStringToWordObj(char *s, DataType type)
{
    int j;
    int index = type == Code ? IC - MEMORY_START : DC - MEMORY_START;
    for (j = 0; j < BINARY_WORD_SIZE; j++)
        binaryImg[index].digit[j].on = s[j] == '1' ? 1 : 0;
}

void calcFinalAddrsCountersValues()
{
    ICF = IC;
    DCF = ICF + DC;
    DC = IC;
    IC = MEMORY_START;
}

void writeMemoryImageToObFile(FILE *fp)
{
    extern BinaryWord *binaryImg;
    int i, j;
    char *encoded;
    int totalSize = DCF - MEMORY_START;
    fprintf(fp, "%d %d\n", ICF - MEMORY_START, DCF - ICF);
    for (i = 0; i < totalSize; i++)
    {
        fprintf(fp, "%04d \t %s \n", MEMORY_START + i, binaryWordToBase4(&binaryImg[i]));
    }
}
