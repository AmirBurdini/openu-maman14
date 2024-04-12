#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//GERMAN : add headers to  encode

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
            return 'E'; /* Handle invalid digits*/
    }
}

/* Function to convert a binary string to base-4 representation*/
char binaryToBase4(char *binary) {
    int decimal = (binary[0] - '0') * 2 + (binary[1] - '0'); /* Convert 2-bit binary to decimal */
    char base4_digit = decimal % 4 + '0';
    return base4ToSign(base4_digit); /* Convert base-4 digit to sign */
}

/* Function to process each line of the file */
void processLine(char *line) {
    char *space = strchr(line, ' '); /* Find the space separator */
    int i;
    if (space != NULL) {
        char *binary = space + 1; /* Extract binary part after the space */
        int len = strlen(binary);
        for (i = 0; i < len; i += 2) {
            binary[i/2] = binaryToBase4(binary + i); /* Convert 2-bit group to base-4 */
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

/*
int main() {

    FILE *outputFileName = convertFile("input.txt");

    if (outputFileName != NULL) {
        printf("Conversion successful.\n");
    } else {
        printf("Error: Conversion failed.\n");
    }

    return 0;
}
*/