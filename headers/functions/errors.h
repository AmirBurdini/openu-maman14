
/*
##########################################################################################################
################################################# errors.c ###############################################
##########################################################################################################
This file is used for handling different errors our assembler might encounter during all the stages of the
assembler.
##########################################################################################################

*/

/* @ Function: Bool yieldError(Error err)
   @ Arguments: The function gets Error err - We are getting an error.
   @ Description: The function gets Error err, 
   and according to this error prints am error to the console, returns true if there is an error and false if there is no error.
*/
Bool yieldError(Error err);

/* @ Function: void yieldErrorIntoFile(Error err)
   @ Arguments: The function gets Error err - We are getting an error.
   @ Description: The function gets Error err, 
   if there is an error it prints it to errorsFile else it wont print.
*/
void yieldErrorIntoFile(Error err);

/* @ Function: Bool yieldWarning(Warning err)
   @ Arguments: The function gets Warning err - We are getting a warning err.
   @ Description: The function gets warning err, 
   if there is a warning it prints the relevant warning if there is no warning at all returns true.
*/
Bool yieldWarning(Warning err);

/* @ Function: void yieldWarningIntoFile(Warning err)
   @ Arguments: The function gets Warning err - We are getting a warning.
   @ Description: The function gets Warning err, 
  if there is a warning it prints it to warningsFile else it wont print.
*/
void yieldWarningIntoFile(Warning err);

/* @ Function: void fileOpeningFailure(char *fileName)
   @ Arguments: The function gets char *fileName - a file .
   @ Description: The function gets char *fileName, 
  if there is an error with opening the file it will throw an error and print it to errorsFile.
*/
void fileOpeningFailure(char *fileName);

/* @ Function: void fileCreationFailure(char *fileName)
   @ Arguments: The function gets char *fileName - a file .
   @ Description: The function gets char *fileName, 
  if there is an error with creating the file it will throw an error and print it to errorsFile.
*/
void fileCreationFailure(char *fileName);

/* @ Function: void closeOpenLogFiles()
   @ Arguments: The function gets nothing.
   @ Description: The function gets will close both errorsFile and warningsFile.
*/
void closeOpenLogFiles();
