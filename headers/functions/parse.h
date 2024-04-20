
/*
##########################################################################################################
##########################################################################################################
#################################### preProccesor.c/h General Overview: ##################################
##########################################################################################################
##########################################################################################################

This file purpose is to be the main file that is responsible for parsing of the expanded assembly code.
while parsing the code in this file we are invoking different functions that exists in the firstRun.c
and the secondRun.c depending on the global state of our assembler (firstRun/SecondRun).

##########################################################################################################
##########################################################################################################
##########################################################################################################
*/

/* @ Function: verifyCommaSyntax
   @ Arguments: char * which will hold the content of some line of code.
   @ Description:The function validates the comma syntax in some line of code,
   it checks that between any 2 arguments their exist only one comma and that
   there are not commas in the end or the beginning of the line. If a line
   found to be violating these comma syntax rules, it yields the relevant error
   message.
*/

Bool verifyCommaSyntax(char *line);

/* @ Function: verifyDataArguments
   @ Arguments: char *line - the operation's name.
   @ Description: checks if the operation name is valid.
   @ Returns: returns true if the operation name is valid, false otherwise.
*/

Bool verifyDataArguments(char *line);

/* @ Function: verifyStringArguments
   @ Arguments: the function gets char * token which is the current token that we are about to parse the string argument from.
   @ Description: The function extracts the argument string of the .string instruction, than the function analyses\ parses the string.
   If the function encounter errors- no opening or closing  (or no opening and closing) quotes, it yields (prints) the relevant error message and keeps on parsing the rest of the line in order to find and report all the errors.
   While the function parsing the arguments, ir also counts the length of the .string string (including the \0 at the end) that will take size in the data memory.
   In the end of the function, if after parsing the line turns out to be valid, it increases the data counter with the size in memory that the current .string instruction will take.
*/
Bool verifyStringArguments(char *line);

/* @ Function: parseLine
   @ Arguments: The function gets char * token which is the first token of the line that we are about to parse and char *line which is the current line being parsed
   @ Description: The function checks what is the current currentCompilerState, than checks what is the first token (an instruction, an operation, a label declaration...)
    If the currentCompilerState is equal to firstRun, according to the first token, it finds out what kind of line is the current line and calls other function so they can handle the line.
    If the currentCompilerState is equal to secondRun, according to the first token, it calls function to write the compiled memory.
    If it finds some errors, it yields (prints) the relevant error message.
    If the line turns out to be valid, it returns true, else it returns false.
*/
Bool parseLine(char *token, char *line);

/* @ Function:handleSingleLine
   @ Arguments: This function gets char *line which is the current line that is being parsed.
   @ Description: The function checks what is the current currentCompilerState, and by that decides how to split the line into tokens (what is the delimeter). 
   Than the function calls the function parseLine in order to check if there are errors in the line.
   Than its increases by 1 the number of line it parses (for the next line to come).
   Returns true if the line is valid and false if it isn't.
*/
Bool handleSingleLine(char *line);

Bool verifyDefinitionArguments(char *line);

/* @ Function:parseAssemblyCode
   @ Arguments: The function gets FILE *src which is a file after the pre proccesoring.
   @ Description: The function parses the file, splits it to tokens and calls the right functions to complete the first and second run.
*/
void parseAssemblyCode(FILE *src);
