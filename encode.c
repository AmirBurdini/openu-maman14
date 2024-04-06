#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");
    char line[100]; /* Assuming each line has a maximum length of 100 characters*/

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error: Unable to open file.\n");
        return 1;
    }

    fgets(line, sizeof(line), inputFile); /* Read the first line (header) and write to output file */
    fprintf(outputFile, "%s", line);

    while (fgets(line, sizeof(line), inputFile)) {
        processLine(line); /* Process each line */
        fprintf(outputFile, "%s\n", line); /* Write the modified line to output file */
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Conversion successful.\n");

    return 0;
}