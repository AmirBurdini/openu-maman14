
Bool isValidImmediateParamter(char *s);
/* @ Function: isValidImmediateParamter
   @ Arguments: The function gets a char *s, the string it checks whether it is a valid immediate parameter or not.
   @ Description: The function checks if char *s is a valid immediate parameter by verifying the first token us a -, a + or a digit and the other vhars are digits.
   Returns true if it is a valid immediate parameter, and false if it isn't.

*/

Bool isValidIndexParameter(char *s);
/* @ Function: isValidIndexParamter
   @ Arguments: The function gets a char *s, the string it checks whether it is a valid index parameter or not.
   @ Description:The function checks if char *s is a valid index parameter by checkin if it is a label and a register (between 10-15) in parenthesis afterwards
   Returns true if it is a valid index parameter, and false if it isn't.
*/

Bool isIndexParameter(char *s);
/* @ Function: isIndexParameter
   @ Arguments: The function gets a char *s, the string it checks whether it is a index parameter or not.
   @ Description:The function checks if char *s is a valid index parameter by checkin if it is a label and a register (any register, not strict to 10-15) in parenthesis afterwards
   Returns true if it is a valid index parameter, and false if it isn't.
*/

AddressMethod convertBinaryToAddressMethod(AddressMethodsEncoding method);