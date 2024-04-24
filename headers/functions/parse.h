
/*
##########################################################################################################
############################################## preProccesor.c ############################################
##########################################################################################################

This file serves as the primary module responsible for parsing the expanded assembly code. 
It orchestrates the parsing process by invoking various functions from "firstRun.c" and "secondRun.c" 
based on the current state of the assembler(whether it's in the first run or the second run).

##########################################################################################################
*/

/* @ Function: Bool verifyCommaSyntax(char *line)
   @ Arguments: char *line - which will contain the content of a specific line of code.
   @ Description:The function validates the comma syntax in a line of code. 
   It ensures that between any two arguments, there exists only one comma, and there are no commas at the beginning or end of the line. 
   If a line is found to violate these comma syntax rules, it yields the relevant error message.
*/
Bool verifyCommaSyntax(char *line);

/* @ Function: Bool verifyDataArguments(char *line)
   @ Arguments: char *line - the operation's name.
   @ Description: The function checks whether the operation name is valid and returns true if it is, 
   otherwise it returns false.
*/
Bool verifyDataArguments(char *line);

/* @ Function: Bool verifyStringArguments(char *line)
   @ Arguments: char *line - token which is the current token that we are about to parse the string argument from.
   @ Description: The function extracts and analyzes the argument string of the .string instruction. 
   It checks for errors such as missing opening or closing quotes, and continues parsing to report all errors. 
   It also counts the length of the string (including the \0 at the end) for memory size calculation. 
   If the line is valid, it increases the data counter by the size in memory that the .string instruction will occupy.
*/
Bool verifyStringArguments(char *line);

/* @ Function: Bool parseLine(char *token, char *line)
   @ Arguments: char *token, char *line - which is the first token of the line that we are about to parse and char *line which is the current line being parsed
   @ Description: The function examines the currentCompilerState and the first token of the line. 
   If in the firstRun state, it determines the type of line and delegates handling to other functions. 
   In the secondRun state, it calls functions to write the compiled memory. 
   It prints relevant error messages if errors are found. 
   If the line is valid, it returns true; otherwise, it returns false..
*/
Bool parseLine(char *token, char *line);

/* @ Function: Bool handleSingleLine(char *line)
   @ Arguments: char *line -  which is the current line that is being parsed.
   @ Description: The function determines the currentCompilerState and uses that information to decide how to split the line into tokens, selecting the appropriate delimiter. 
   Then, it calls the parseLine function to check for errors in the line. 
   After parsing, it increments the line number by 1 for the next line. 
   Finally, it returns true if the line is valid and false if it isn't.
*/
Bool handleSingleLine(char *line);

/* @ Function: Bool verifyDefinitionArguments(char *line);
   @ Arguments: char *line - which is line that we want to verify if define is correct.
   @ Description: The function checks whether the defined syntax is valid.
*/
Bool verifyDefinitionArguments(char *line);

/* @ Function: void parseAssemblyCode(FILE *src)
   @ Arguments: FILE *src - which is a file after the pre proccesoring.
   @ Description: The function parses the file, dividing it into tokens, and invokes the appropriate functions to complete both the first and second runs.
*/
void parseAssemblyCode(FILE *src);
