
/*
##########################################################################################################
################################################ Operation.c #############################################
##########################################################################################################

This file holds the operation table information and contain functions that their purpose is to share different
parts of the operation information from this table.

##########################################################################################################
*/

/* @ Function: Bool isOperationName(char *s)
   @ Arguments: char *s - the operation's name.
   @ Description: The function checks if the operation name is valid and returns true if it is, 
   otherwise it returns false.
*/
Bool isOperationName(char *s);

/* Function: Operation *getOperationByName(char *s)
   @ Arguments: char *s- operation's name.
   @ Description: The function checks for the opcode corresponding to the given operation name and returns the relevant operation. 
   If the argument name is not valid, it returns NULL.
*/
const Operation *getOperationByName(char *s);

/* @ Function: int getOpIndex(char *s)
   @ Arguments: char *s- operation's name.
   @ Description: The function searches for the given operation in the operations table and returns the relevant operation's opcode index. 
   If the operation name isn't valid, it returns -1.
*/
const Operation *getOperationByIndex(unsigned int i);

