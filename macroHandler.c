#include "data.h"

Bool isMacroOpening(char *s)
{
    return !strcmp(s, "mcr") ? True : False;
}

Bool isMacroClosing(char *s)
{
    return !strcmp(s, "endmcr") ? True : False;
}

Bool isLegalMacroName(char *s)
{
    return !isInstructionStrict(s) && !isOperation(s) ? True : False;
}

Bool isPossiblyUseOfMacro(char *s)
{
    return !isLabelDeclaration(s) && !isOperation(s) && !isComment(s) && !isInstructionStrict(s) && !isMacroClosing(s) && !isMacroOpening(s);
}