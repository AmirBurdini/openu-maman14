#include "data.h"

Bool isValidImmediateParamter(char *s)
{
    int i, len = strlen(s);
    if (s[0] != '#')
        return False;
    
    if (isLabelNameAlreadyTaken(&s[1], Symbol)) {
        return True;
    }

    if (s[1] == '-' && !isdigit(s[2]))
        return False;

    for (i = 2; i < len; i++)
        if (!isdigit(s[i]))
            return False;
    return True;
}

Bool isIndexParameter(char *s)
{
    int len = strlen(s);
    char *opening = strchr(s, '[');
    char *closing = strchr(s, ']');
    Bool result = True;
    if (len < 4)
        return False;
    if (opening == NULL || closing == NULL)
        return False;
    if (closing < opening || (s[len - 1] != ']'))
        return False;
    if (isLabelNameAlreadyTaken(opening + 1, Symbol)) {
        return True;
    }
    else
    {
        opening++;
        *closing = '\0';
        if (!isRegistery(opening))
            result = False;
        *closing = ']';
    }
    return result;
}

Bool isValidIndexParameter(char *s)
{
    int len = strlen(s);
    Bool result = True;
    if (len < 6)
        return False;

    else if (!(s[len - 1] == ']' && s[len - 4] == 'r' && s[len - 5] == '['))
        return False;
    else
    {
        char *opening = 0;
        opening = strchr(s, '[');
        opening++;
        s[len - 1] = '\0';

        if (isRegistery(opening) && getRegisteryNumber(opening) < 10)
        {
            result = False;
        }
        s[len - 1] = ']';
    }
    return result;
}

AddressMethod convertBinaryToAddressMethod(AddressMethodsEncoding method) {
    
    int decimal = 1 *method.firstDigit + 2 *method.secondDigit;
    AddressMethod result = {0, 0, 0, 0};

    switch (decimal)
    {
    case 0:
        result.immediate = 1;
        break;
    case 1:
        result.direct = 1;
        break;
    case 2:
        result.index = 1;
        break;
    case 3:
        result.reg = 1;
        break;
    default:
        break;
    }

    return result;
}