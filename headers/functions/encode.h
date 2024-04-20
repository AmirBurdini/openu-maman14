#include <stdio.h>

/*
##########################################################################################################
##########################################################################################################
#################################### secondRun.c General Overview: #######################################
##########################################################################################################
##########################################################################################################

In this program we are taking our .ob file that made of binary lines and we encrypt the data.


##########################################################################################################
##########################################################################################################
##########################################################################################################
*/

char base4ToSign(char digit);
/* @ Function: base4ToSign
   @ Arguments: The function gets char digit -  digit represented by a char
   @ Description: The function takes a digit from 0-3 (representaion of base 4) and converts each of this number to the correct sign
   in case of a digit or anything else it will put E for indicating error.
*/

char encodeNumber(char *binary);
/* @ Function: decimalToBase4
   @ Arguments: The function gets char *binary - string of a binary number
   @ Description: The function takes Binary number from the file and converts it to a number in base4.
*/

char *processLine(char *line);
/* @ Function: processLine
   @ Arguments: The function gets char *line - string line in a file
   @ Description: The function a line from our file and use decimalToBase4 function to convert the line to base4 and 
   process the line. 
*/

FILE *convertFile(const char *inputFileName);
/* @ Function: convertFile
   @ Arguments: The function gets const char *inputFileName - string of a file name
   @ Description: The function checking if the file is empty and if yes it is not converting it.
   if it is not empty it take the inputFile and useing processLine function to process each line of the input text to the output text.
   At the end we are getting an output file converted to converted base4 file.
*/