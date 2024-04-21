Bool isMacroOpening(char *s);
/* @ Function: isMacroOpening
   @ Arguments: The function gets a char *s, the string it checks whether it is the opening of a macro or not.
   @ Description: The function checks if char *s is equal to "macro", returns true if it is, and false if it isn't
*/

Bool isMacroClosing(char *s);
/* @ Function: isMacroClosing
   @ Arguments: The function gets a char *s, the string it checks whether it is the closing of a macro or not.
   @ Description: The function checks if char *s is equal to "endm", returns true if it is, and false if it isn't
*/

Bool isPossiblyUseOfMacro(char *s);
/* @ Function: isPossiblyUseOfMacro
   @ Arguments: The function gets a char *s, the string it checks whether it can be a macro or not.
   @ Description: The function checks if char *s can be a macro, by illuminating the other things it can be (an instruction, a label...).
   Returns true if it could be a macro and false if it couldn't.
*/

Bool isLegalMacroName(char *s);
/* @ Function: isLegalMacroName
   @ Arguments: The function gets a char *s, the string it checks whether it is a legal macro name or not.
   @ Description: The function checks if char *s is a legal macro name by verifying that it's name is not a name of an instruction or an operation.
    Returns true if it is a legal macro name and false if it is not.
*/