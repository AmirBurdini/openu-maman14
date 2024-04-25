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

char *decimalToBinary(int num)
{
    unsigned int remainder = 0;
    unsigned int absValue = num;
    int index = 0;
    char *word = (char *)malloc(BINARY_WORD_SIZE + 1);
    
    if (num < 0)
    {
        absValue = abs(num);
        absValue = ~absValue;
        absValue++;
    }
        
    while (index < BINARY_WORD_SIZE) {
        remainder = absValue % 2;
        absValue /= 2;
        word[index] = remainder == 1 ? '1' : '0';
        index++;
    }

    strcat(word, "\0");
    return word;
}

char *binaryWordToBase4(BinaryWord *word) {

    int number = binaryWordToDecimal(word);
    int i, temp = abs(number);
    int remainder;
    char *result = (char *)malloc(8 * sizeof(char));

    if (number == 0) {
        for (i = 0; i < 8; i++){
            result[i] = '*';
        }
    } else {
        temp = abs(number);
        i = 6;
        while (temp > 0) {
            remainder = temp % 4;
            result[i] = base4ToSign(remainder);
            temp = temp / 4;
            i--;
        }
    }

    result[7] = '\0';
    return result;
}

int binaryWordToDecimal(BinaryWord *word) {

    int i, number = 0, scale = 1;
    for (i = BINARY_WORD_SIZE - 1; i >= 0; i--) {
        number += word->digit[i].on ?scale : 0;
        scale = scale * 2;
    }
    return number;
}

char base4ToSign(int digit) {
    switch (digit) {
        case 0:
            return '*';
        case 1:
            return '#';
        case 2:
            return '%';
        case 3:
            return '!';
        default:
            printf("unrecognised encoded number :%d\n", digit);
            return '0'; /* Handle invalid digits*/
    }
}