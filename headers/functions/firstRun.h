
/*
   ##########################################################################################################
   ###########################################  General Overview: ###########################################
   ##########################################################################################################

   In FirstRun.c, we parse and analyze the assembly code obtained after extracting macros from it. 
   We ensure that the syntax is legal and that the usage of the assembly language conforms to the rules of our operations and instructions 
   (matching operand types, instruction types, comment types, legal declaration of symbols, etc.). 
   If we encounter errors, we log them to the error.log file and print them to stderr, then continue checking the next characters in the line for each line of code.

   If no errors are encountered, we only increase the DATA COUNTER or the INSTRUCTION COUNTER accordingly by the size that the line of code should occupy in memory.

   By doing this, at the end of the first run, we precisely determine how much space is needed for the data image and how much space is required for the instruction image. 
   This approach allows us to allocate just the required amount of memory without wasting large random chunks of memory upfront. 
   If the first run completes without errors, we set the sharedState to secondRun.

   Additionally, we save the macros in a dedicated table and replace them with the original code in the file.
   ##########################################################################################################
   ##########################################################################################################
 */

/* @ Function: Bool handleOperation(char *operationName, char *args)
 @ Arguments: This function gets the source and destination operands, the operation and the posible addresing method of each of the operands.
 @ Description: The function verifies the validity of the source and destination operands by checking 
 if they have the correct number of operands or the appropriate addressing method. 
 If errors are encountered, it prints the relevant error message and continues parsing the rest of the line to find and report all errors.
 It returns true if the operands are valid and false if they are not.
 */
Bool handleOperation(char *operationName, char *args);

/* @ Function: parseOperands(char *src, char *des, const Operation *op, AddressMethodsEncoding active[2])
   @ Arguments: This function gets char *src, char *des, const Operation *op, AddressMethodsEncoding active[2]
   @ Description: The function validates and parses the operands according to their expected format.
   */
Bool parseOperands(char *src, char *des, const Operation *op, AddressMethodsEncoding active[2]);

/* @ Function: Bool validateOperandMatch(AddressMethod allowedAddrs, AddressMethodsEncoding active[2], char *operand, int type)
   @ Arguments: This function gets AddressMethodsEncoding allowedAddrs- the allowed addressing methods for the source and destination operands, AddressMethodsEncoding active[2]- an array that represent types of addressing methods for the operands,
    char *operand- the operands, and type- the type of the operand.
   @ Description: The function examines if the operand has the correct addressing method. It returns true if it does, and false if it doesn't.
   */
Bool validateOperandMatch(AddressMethod allowedAddrs, AddressMethodsEncoding active[2], char *operand, int type);

/* @ Function: Bool handleInstruction(int type, char *firstToken, char *nextTokens, char *line)
   @ Arguments: the function gets int type- the type of the instruction,
   char *firstToken and char *nextToken- the first and second tokens in the instruction line (char * line).
   @ Description: The function checks the first token. If it is an instruction,
   it checks what is the type of the instruction, and yeilds error if there are illegal appearence of characters in the declaration.
   If it is a label declaration, it makes sure there is a valid instruction
   and its arguments afterwards, if the declaration is not valid it yeilds error.
   If the firstToken is not a label declaration or any type of legal instruction, it yeilds error.
   The function keeps on validating the whole line and reports all of the errors.
   If there aren't any mistake, the function returns true and if there is a vald label it adds it to the symbols table.
   Else, it returns false.
*/
Bool handleInstruction(int type, char *firstToken, char *nextTokens, char *line);

/*  @ Function: Bool handleLabel(char *labelName, char *nextToken, char *line)
    @ Arguments: The function gets char *labelName- the name of the label it handles,
    char *nextToken- one of the tokens in the line (char * line).
    @ Description: The function gets a line in the code that starts with a label declaration.
    The function checks if this is an instruction line or an operation line.
    If it encountered an error it yields (prints) the error.
     The function keeps on validating the whole line and reports all of the errors.
    The function returns true if the line is valid, andfalse if it ian't.
*/
Bool handleLabel(char *labelName, char *nextToken, char *line);

/*  @ Function: handleDefinition(char *name, char *value, char *line);
    @ Arguments: The function gets char *name, char *value, char *line)
    @ Description: The function handeling the .define key word.
*/
Bool handleDefinition(char *name, char *value, char *line);