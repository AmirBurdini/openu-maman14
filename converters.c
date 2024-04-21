#include "data.h"

char *cloneString(char *s)
{
    char *copy;
    if (!(*s))
        return "";
    copy = (char *)calloc(strlen(s), sizeof(char *));
    strcpy(copy, s);
    return copy;
}

char *trimFromLeft(char *s)
{
    while (isspace(*s) && *s != '\0')
        s++;
    return s;
}

char *numToBin(int num)
{
    int i = 0;
    unsigned int result;
    char *word, hex[5];
    word = (char *)calloc(BINARY_WORD_SIZE + 1, sizeof(char *));
    if (num < 0)
    {
        result = abs(num);
        result = ~result;
        result++;
        sprintf(hex, "%05x", (int)(result & 0x4ffff));
    }
    else
        sprintf(hex, "%05x", (int)num & 0xfffff);

    while (hex[i] != '\0')
    {
        switch (hex[i])
        {

        case '0':
            strcat(word, "0000");
            break;
        case '1':
            strcat(word, "0001");
            break;
        case '2':
            strcat(word, "0010");
            break;
        case '3':
            strcat(word, "0011");
            break;
        case '4':
            strcat(word, "0100");
            break;
        case '5':
            strcat(word, "0101");
            break;
        case '6':
            strcat(word, "0110");
            break;
        case '7':
            strcat(word, "0111");
            break;
        case '8':
            strcat(word, "1000");
            break;
        case '9':
            strcat(word, "1001");
            break;
        case 'A':
        case 'a':
            strcat(word, "1010");
            break;
        case 'B':
        case 'b':
            strcat(word, "1011");
            break;
        case 'C':
        case 'c':
            strcat(word, "1100");
            break;
        case 'D':
        case 'd':
            strcat(word, "1101");
            break;
        case 'E':
        case 'e':
            strcat(word, "1110");
            break;
        case 'F':
        case 'f':
            strcat(word, "1111");
            break;
        default:
            break;
        }

        i++;
    }

    strcat(word, "\0");
    return word;
}

char *decimalToBase4(int number) {

    int length = 0;
     /*  Allocate memory for the base-4 representation */
    char* result = (char*)malloc((length) * sizeof(char));
    int temp = abs(number);
    int remainder;
    int index;
    while (temp > 0) {
        length++;
        temp /= 4;
    }

    /* Convert number to base-4 */ 
    temp = abs(number);
    index = 0;
    while (temp > 0) {
        remainder = temp % 4;
        result[index++] = (char)('0' + remainder);
        temp /= 4;
    }

    result[index] = '\0';  
    return result;
}