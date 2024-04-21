
/*
##########################################################################################################
##########################################################################################################
#################################### utils.c/utils.h General Overview: ###################################
##########################################################################################################
##########################################################################################################

Utils.c files contains most of all converters functions that are used for verifying and checking and
validating tokens identity, funtion here are mainly used out side of this file by other functions that deals
with parsing the assembly code.

##########################################################################################################
##########################################################################################################
##########################################################################################################
*/

Bool isInstruction(char *s);
/* @ Function: isInstruction
   @ Arguments: The function gets a char *s, the string it checks whether it or a part of it is an instruction or not.
   @ Description: The function checks if char *s or a part of it is an instruction by comparing it to the name of the instructions or checking if one of the instructions are a substring of it.
   Returns true if it or a part of it is an instruction, and false if it isn't.
*/

Bool isInstructionStrict(char *s);
/* @ Function: isInstructionStrict
   @ Arguments: The function gets a char *s, the string it checks whether it is an instruction or not.
   @ Description: The function checks if char *s is an instruction by comparing it to the name of the instructions.
   Returns true if it is an instruction, and false if it isn't.
*/

Bool isComment(char *s);
/* @ Function: isComment
   @ Arguments: The function gets a char *s, the string it checks whether it is a comment or not.
   @ Description: The function checks if char *s is a comment by checking if it's first char is ;.
   Returns true if it is a comment, and false if it isn't.
*/
Bool isOperation(char *s);
/* @ Function: isOperation
   @ Arguments: The function gets a char *s, the string it checks whether it is an operation or not.
   @ Description: The function checks if char *s is an operation, by checking if it is equal to one of the names of the operations, using getOperationByName.
   Returns true if it is an operation, and false if it isn't.
*/

Bool isLabelDeclarationStrict(char *s);
/* @ Function: isLabelDeclarationStrict
   @ Arguments: The function gets a char *s, the string it checks whether it is a label declaration or not.
   @ Description: The function checks if char *s is a label declaration by checking if it's last char is :.
     Returns true if it is a label declaration, and false if it isn't.
*/

Bool isLabelDeclaration(char *s);
/* @ Function: isLabelDeclaration
   @ Arguments: The function gets a char *s, the string it checks whether it or a part of it is a label declaration or not.
   @ Description: The function checks if char *s or a part of it is a label declaration by checking if it consists a :.
   Returns true if it or a part of it is a label declaration, and false if it isn't.
*/

int getInstructionType(char *s);
/* @ Function: getInstructionType
    @ Arguments: The function gets a char *s, the string it checks what instruction it is.
    @ Description: The function checks if char *s or a part of it is an instruction  by  checking if one of the instructions are a substring of it.
    Returns the right instruction if it is an instruction, and false(0) if it isn't
*/

char *getInstructionName(char *s);

char *getInstructionNameByType(int type);
/* @ Function: getInstructionNameByType
   @ Arguments: The function gets int type- the type of instruction.
   @ Description: The function returns the type of the istruction and returns it as a string with \0 at the end.
   If type is not an instruction it returns NULL.
*/

Bool verifyLabelNaming(char *s);
/* @ Function: verifyLabelNaming
   @ Arguments: The function gets char *s- the name of the label it about to verify.
   @ Description: The function makes sure the name of the label is valid, by checking things like its length, if it is equal to an operation...
   Returns true if it is a valid name of label, and false if it isn't.
*/

Bool verifyLabelNamingAndPrintErrors(char *s);
/* @ Function: verifyLabelNamingAndPrintErrors
   @ Arguments: The function gets char *s- the name of the label it about to verify and prints it's errors.
   @ Description: The function makes sure the name of the label is valid, by checking things like its length, if it is equal to an operation...
   If it finds an error it yields (prints) it and returns false, else returns true.
*/

Bool isDefinition(char *s);