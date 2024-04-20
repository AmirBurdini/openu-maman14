#include "data.h"

/* Function to convert a base-4 digit to the corresponding sign */
char base4ToSign(char digit) {
    switch (digit) {
        case '0':
            return '*';
        case '1':
            return '#';
        case '2':
            return '%';
        case '3':
            return '!';
        default:
            return '?'; /* Handle invalid digits*/
    }
}

char *encodeNumber(char *number) {

    char *result, *temp = '';
    result = temp;
    int index = 0;
    while (number[index] = '\0') {
        
        temp[index] = base4ToSign(number[index]);
        index++;
    }

    return result;
}

/* Function to process each line of the file */
char *processLine(char *line) {
    char *space = strchr(line, ' '); /* Find the space separator */
    int i;
    if (space != NULL) {
        char *binary = space + 1; /* Extract binary part after the space */
        int len = strlen(binary);
        for (i = 0; i < len; i += 2) {
            binary[i/2] = decimalToBase4(binary + i); /* Convert 2-bit group to base-4 */
        }
        binary[len/2] = '\0'; /* Null-terminate the string */
    }
}

FILE *convertFile(const char *inputFileName) {

    FILE *inputFile = fopen(inputFileName, "r");
    FILE *outputFile = fopen("output.txt", "w");
    char line[100];

    if (inputFile == NULL) {
        printf("Error: Unable to open input file.\n");
        return NULL;
    }

    if (outputFile == NULL) {
        printf("Error: Unable to create output file.\n");
        fclose(inputFile);
        fclose(outputFile);
        return NULL;
    }

    fgets(line, sizeof(line), inputFile); 
    fprintf(outputFile, "%s", line);

    while (fgets(line, sizeof(line), inputFile)) {
        processLine(line); 
        fprintf(outputFile, "%s\n", line); 
    }

    fclose(inputFile);
    fclose(outputFile);

    return outputFile; 
}