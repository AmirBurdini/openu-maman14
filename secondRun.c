#include "data.h"

void writeAdditionalOperandsWords(const Operation *op, AddressMethodsEncoding active, char *value);

//Refactor needed
Bool writeOperationBinary(char *operationName, char *args)
{
    const Operation *op = getOperationByName(operationName);
    char *first, *second;
    AddressMethodsEncoding active[2] = {{0, 0}, {0, 0}};
    first = strtok(args, ", \t\n\f\r");
    second = strtok(NULL, ", \t\n\f\r");
    writeFirstWord(op);

    if (first && second && (detectOperandType(first, active, 0) && detectOperandType(second, active, 1)))
    {
        writeSecondWord(first, second, active, op);
        writeAdditionalOperandsWords(op, active[0], first);
        writeAdditionalOperandsWords(op, active[1], second);
    }
    else if (!second && first && detectOperandType(first, active, 1))
    {
        second = first;
        writeSecondWord(first, second, active, op);
        writeAdditionalOperandsWords(op, active[1], second);
    }
    else if (!first && !second)
        return True;

    else
        return False;

    return True;
}

void writeAdditionalOperandsWords(const Operation *op, AddressMethodsEncoding active, char *value)
{
    AddressMethod method = convertBinaryToAddressMethod(active);

    if (method.index)
    {
        parseLabelNameFromIndexAddrOperand(value);
        writeDirectOperandWord(value);
    }
    else if (method.direct)
        writeDirectOperandWord(value);
    else if (method.immediate)
        writeImmediateOperandWord(value);
}

Bool writeDataInstruction(char *token)
{
    int num;
    while (token != NULL)
    {
        num = atoi(token);
        addWord((A) | num, Data);
        token = strtok(NULL, ", \t\n\f\r");
    }
    return True;
}

//Refactor needed
Bool writeStringInstruction(char *s)
{
    char *start = strchr(s, '\"');
    int i, len;
    start++;
    len = strlen(start);
    for (i = 0; i < len - 2; i++)
        addWord((A << 16) | start[i], Data);

    addWord((A << 16) | '\0', Data);
    return True;
}

//Refactor needed
void writeSecondWord(char *first, char *second, AddressMethodsEncoding active[2], const Operation *op)
{
    AddressMethod sourceMethod = convertBinaryToAddressMethod(active[0]);
    AddressMethod destMethod = convertBinaryToAddressMethod(active[1]);

    unsigned secondWord = (A << 16) | (op->op << 12);
    if (first && (sourceMethod.reg || sourceMethod.index))
        secondWord = secondWord | (sourceMethod.reg ? (getRegisteryNumber(first) << 8) : (parseRegNumberFromIndexAddrOperand(first) << 8)) | (sourceMethod.reg ? (REGISTER_DIRECT_ADDR << 6) : (INDEX_ADDR << 6));
    else if (first && (sourceMethod.direct || sourceMethod.immediate))
        secondWord = secondWord | (0 << 8) | (sourceMethod.direct ? (DIRECT_ADDR << 6) : (IMMEDIATE_ADDR << 6));
    if (second && (destMethod.reg || destMethod.index))
        secondWord = secondWord | (destMethod.reg ? (getRegisteryNumber(second) << 2) : (parseRegNumberFromIndexAddrOperand(second) << 2)) | (destMethod.reg ? (REGISTER_DIRECT_ADDR) : (INDEX_ADDR));
    else if (second && (destMethod.direct || destMethod.immediate))
        secondWord = secondWord | (0 << 2) | (destMethod.direct ? (DIRECT_ADDR) : (IMMEDIATE_ADDR));

    addWord(secondWord, Code);
}

void writeFirstWord(const Operation *op)
{
    unsigned firstWord = (A << 10) | op->op;
    addWord(firstWord, Code);
}

void writeDirectOperandWord(char *labelName)
{

    if (isExternal(labelName))
    {
        addWord((E), Code);
        updateExtPositionData(labelName);
    }

    else
    {
        addWord((R), Code);
    }
}

void writeImmediateOperandWord(char *n)
{
    n++;
    if ((*n & A) == 0) {
    addWord((A) | atoi(n), Code);
    }
}

Bool detectOperandType(char *operand, AddressMethodsEncoding active[2], int type)
{
    AddressMethod method = convertBinaryToAddressMethod(active[type]);
    if (isRegistery(operand))
        method.reg = True;
    else if (isValidImmediateParamter(operand))
        method.immediate = True;
    else if (isValidIndexParameter(operand))
        method.index = True;
    else
    {
        if (isSymbolExist(operand))
        {
            if (isEntry(operand) && !isNonEmptyEntry(operand))
                return yieldError(entryDeclaredButNotDefined);
            method.direct = True;
        }
        else
            return yieldError(labelNotExist);
    }
    return True;
}

char *parseLabelNameFromIndexAddrOperand(char *s)
{
    char *p = strchr(s, '[');

    *p = 0;

    return s;
}

int parseRegNumberFromIndexAddrOperand(char *s)
{
    char *p = strchr(s, ']');

    s = strchr(s, '[');
    s++;
    if (p)
        *p = 0;

    return getRegisteryNumber(s);
}
