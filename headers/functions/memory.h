
/*
##########################################################################################################
################################################# memory.c ###############################################
##########################################################################################################

This memory module serves the purpose of managing the memory for the resulting binary/hex image. 
It is utilized both in the first and second runs of the assembler.
During the first run, the functions within this module are responsible for adjusting the DC (Data Counter) and IC (Instruction Counter) counters as needed.
During the second run, the functions included in this module construct the memory image word by word.

##########################################################################################################

*/

/* @ Function: increaseDataCounter(int amount)
   @ Arguments: The function gets int amount- The data counter (DC) holds the count of addresses in the memory allocated for data storage.
   @ Description: The function increments the data counter by the specified amount, subtracting the number of addresses already held in the data counter. It does not return any value.
*/
void increaseDataCounter(int amount);

/* @ Function: increaseInstructionCounter
   @ Arguments: The function gets int amount- the amount of addresses in the memory the instruction counter holds.
   @ Description: The function increases the instruction counter by amount- the amount of addresses in the memory the instruction counter holds.
   The function doesnt return any value.
*/
void increaseInstructionCounter(int amount);

/* @ Function: allocMemoryImg
   @ Arguments: The function gets no arguments.
   @ Description: The function allocates the precise amount of space needed to generate the compiled image. 
   It does not return any value.
*/
void allocMemoryImg();

/* @ Function: resetMemoryCounters
   @ Arguments: The function gets no arguments.
   @ Description: The function resets the counter responsible for tracking the precise amount of space needed to generate the compiled image. 
   It does not return any value.
*/
void resetMemoryCounters();

/* @ Function: void wordStringToWordObj(char *s, DataType type)
   @ Arguments: The function gets char *s - the string it converts and DataType type - This function determines whether the current word belongs to the instructions or to the data part of the memory image. 
   Additionally, it converts a string from a binary word to a typedef struct.
   @ Description: 
The function converts a string to a binaryWord typedef struct (defined in complex_typedef.h). It does not return any value.
*/
void wordStringToWordObj(char *s, DataType type);

/* @ Function: writeMemoryImageToObFile
   @ Arguments: The function gets FILE *fp the file it writes the ob memory into
   @ Description: The function generates the .ob memory image of the code by writing into the .ob file word by word, utilizing helper functions to convert binary words into hex words. 
It does not return any value.
*/
void writeMemoryImageToObFile(FILE *fp);

/* @ Function: void calcFinalAddrsCountersValues()
   @ Arguments: The function gets no arguments
   @ Description: The function calculates the final values of the counters.
*/
void calcFinalAddrsCountersValues();

/* @ Function: void addWordToCodeImage(char *s)
   @ Arguments: The function gets char *s
   @ Description: The function adds the word "*s" to the code image.
*/
void addWordToCodeImage(char *s);

/* @ Function: void addWordToDataImage(char *s)
   @ Arguments: The function gets char *s
   @ Description: The function adds the word "*s" to the data image.
*/
void addWordToDataImage(char *s);

/* @ Function: void addWord(int value, DataType type)
   @ Arguments: The function gets int value, DataType type
   @ Description: The function adds the relevant data to the code or data image as a binary number.
*/
void addWord(int value, DataType type);

unsigned getDC();
unsigned getIC();
unsigned getICEnd();
unsigned getDCEnd();