
Bool isRegistery(char *s);
/* @ Function: isRegistery
   @ Arguments: The function gets a char *s, the string it checks whether it is a register or not.
   @ Description: The function checks if char *s is a legal register by checking if the first char is 'r' and theothers are int numbers between 0-15.
   Returns true if it is a register, and false if it isn't.
*/

int getRegisteryNumber(char *s);
/* @ Function: getRegisteryNumber
    @ Arguments: The function gets a char *s, the string it checks from what is the number of the register.
    @ Description: The function checks what is the number of the register by checking the number at the end of the string
    Returns the number of the register.
*/