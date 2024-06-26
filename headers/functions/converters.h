
/*
##########################################################################################################
##########################################################################################################
#################################### converters.c/h General Overview: ########################################
##########################################################################################################
##########################################################################################################

this file containing some helper functions that are used in other files for doing simple and independent small
tasks like cloning a string, trimming white space, and also it contains converters functions that are used for
encoding numeric values in binary(2's complement)/hex string.

##########################################################################################################
##########################################################################################################
##########################################################################################################
*/

/* @ Function: char *cloneString(char *s)
   @ Arguments: The function gets char *s- the string it copies
   @ Description: The function gets a char *s, if it is equal to NULL, it returns empty string.
   Else it copies the string to a new memory allocation and returns it.
*/
char *cloneString(char *s);

/* @ Function: char *trimFromLeft(char *s)
   @ Arguments: The function gets char *s- the string it trims from the white spaces from the left.
   @ Description: The function gets a char *s, while it hasn't reached the string's end,
   it skips all the white-space characters that are in the begining of this string
   and than returns a pointer to the string
   (which points to the part after the white space that were before).
*/
char *trimFromLeft(char *s);

/* @ Function: char *decimalToBinary(char *s)
   @ Arguments: The function gets int num - The number we get converts to binary number.
   @ Description: The function gets a int num, 
   that representred in decimal and we convert it to binary.
*/
char *decimalToBinary(int num);

/* @ Function: char *decimalToBase4(int number)
   @ Arguments: The function gets int num - The number we get converted to base 4 number.
   @ Description: The function gets a int num, 
   that representred in decimal and we convert it to base4 number.
*/
char *decimalToBase4(int number);
char *binaryWordToBase4(BinaryWord *word);

int binaryWordToDecimal(BinaryWord *word);

char base4ToSign(int digit);
