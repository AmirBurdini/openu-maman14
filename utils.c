#include "data.h"

Bool isInstruction(char *s)
{
    if (strstr(s, DATA) != NULL || strstr(s, STRING) != NULL || strstr(s, ENTRY) != NULL || strstr(s, EXTERNAL) != NULL || strstr(s, DEFINE) != NULL)
    {
        return True;
    }
    else
        return False;
}

Bool isInstructionStrict(char *s)
{
    return ((!strcmp(s, DATA) || !strcmp(s, STRING) || !strcmp(s, ENTRY) || !strcmp(s, EXTERNAL) || !strcmp(s, DEFINE))) ? True : False;
}

Bool isComment(char *s)
{
    s = trimFromLeft(s);
    return s[0] == ';' ? True : False;
}

Bool isOperation(char *s)
{
    return (getOperationByName(s) != NULL) ? True : False;
}

Bool isLabelDeclarationStrict(char *s)
{
    return s[strlen(s) - 1] == ':' ? True : False;
}

Bool isLabelDeclaration(char *s)
{
    return strchr(s, ':') != NULL ? True : False;
}

int getInstructionType(char *s)
{
    if (strstr(s, DATA) != NULL)
        return _TYPE_DATA;
    if (strstr(s, STRING) != NULL)
        return _TYPE_STRING;
    if (strstr(s, ENTRY) != NULL)
        return _TYPE_ENTRY;
    if (strstr(s, EXTERNAL) != NULL)
        return _TYPE_EXTERNAL;
    if (strstr(s, DEFINE) != NULL)
        return _TYPE_DEFINE;
    return False;
}

char *getInstructionNameByType(int type)
{
    switch (type)
    {
    case _TYPE_DATA:
        return strcat(DATA, "\0");

    case _TYPE_STRING:
        return strcat(STRING, "\0");

    case _TYPE_ENTRY:
        return strcat(ENTRY, "\0");

    case _TYPE_EXTERNAL:
        return strcat(EXTERNAL, "\0");

    case _TYPE_DEFINE:
        return strcat(DEFINE, "\0");

    default:
        break;
    }

    return NULL;
}

char *getInstructionName(char *s)
{
    if (strstr(s, DATA) != NULL)
        return DATA;
    if (strstr(s, STRING) != NULL)
        return STRING;
    if (strstr(s, ENTRY) != NULL)
        return ENTRY;
    if (strstr(s, EXTERNAL) != NULL)
        return EXTERNAL;
    if (strstr(s, DEFINE) != NULL)
        return DEFINE;
    return 0;
}

Bool verifyLabelNaming(char *s)
{
    int i = 0;
    int labelLength = strlen(s);

    /* if label name does not start with a alphabet letter */
    if (isalpha(s[0]) == 0)
        return False;

    /* maximum label name length is 31 characters */
    if (labelLength > MAX_LABEL_LEN || labelLength < 1)
        return False;

    if (isRegistery(s))
        return False;

    else if (isOperationName(s))
        return False;
    else
    {

        while (i < labelLength)
        {
            if (!isalnum(s[i]))
                return False;

            i++;
        }
    }

    return True;
}

Bool verifyLabelNamingAndPrintErrors(char *s)
{
    int i = 0;
    int labelLength = strlen(s);

    /* if label name does not start with a alphabet letter */
    if (isalpha(s[0]) == 0)
        return yieldError(illegalLabelNameUseOfCharacters);

    /* maximum label name length is 31 characters */
    else if (labelLength > MAX_LABEL_LEN)
        return yieldError(illegalLabelNameLength);
    else if (labelLength < 1)
        return yieldError(illegalLabelNameLength);

    else if (isRegistery(s))
        return yieldError(illegalLabelNameUseOfSavedKeywordUsingRegisteryName);

    else if (isOperationName(s))
        return yieldError(illegalLabelNameUseOfSavedKeywordUsingOperationName);

    else
    {

        while (i < labelLength)
        {
            if (!isalnum(s[i]))
                return yieldError(illegalLabelNameUseOfCharacters);

            i++;
        }
    }

    return True;
}

Bool isDefinition(char *s) {

    return (strchr(s, '=') != NULL) && (strstr(s, DEFINE) != NULL) ? True : False;
}