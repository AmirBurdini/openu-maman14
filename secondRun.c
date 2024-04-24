#include "data.h"

Bool writeOperationBinary(char *operationName, char *args)
{
    const Operation *op = getOperationByName(operationName);
    char *src, *dest;
    int wordCount = 0;
    AddressMethodsEncoding active[2] = {{0, 0}, {0, 0}};
    src = strtok(args, _TOKEN_FORMAT_SECOND);
    dest = strtok(NULL, _TOKEN_FORMAT_SECOND);

    if (src && (detectOperandType(src, active, 0)))
    {
        wordCount++;
        if (active[0].firstDigit && active[0].secondDigit) {
            wordCount = wordCount + 10;
        }
    }

    if (dest && (detectOperandType(dest, active, 1)))
    {   
        wordCount++;
        if (active[1].firstDigit && active[1].secondDigit) {
            wordCount = wordCount + 10;
        }
    }

    printf("%d \n", wordCount);
    writeFirstWord(src, dest, active, op);
    if (wordCount > 9) {
        writeRegisterOperandWord(src, dest);
    }
    if (wordCount == 1) {
        dest = src;
        src = NULL;
        writeFirstWord(src, dest, active, op);
        writeAdditionalOperandsWords(op, active[1], dest);
    } else if (wordCount == 2){
        writeAdditionalOperandsWords(op, active[0], src);
        writeAdditionalOperandsWords(op, active[1], dest);
    }

    return True;
}

void writeAdditionalOperandsWords(const Operation *op, AddressMethodsEncoding active, char *value)
{   
    AddressMethod method = convertBinaryToAddressMethod(active);

    if (method.index)
    {
        writeIndexOperandWord(value);
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
        addWord(num, Data);
        token = strtok(NULL, _TOKEN_FORMAT_SECOND);
    }
    return True;
}

Bool writeStringInstruction(char *s)
{
    char *start = strchr(s, '\"');
    int i, len;
    start++;
    len = strlen(start);
    for (i = 0; i < len - 2; i++)
        addWord(start[i], Data);

    addWord('\0', Data);
    return True;
}

void writeFirstWord(char *first, char *second, AddressMethodsEncoding active[2], const Operation *op)
{
    AddressMethod sourceMethod = convertBinaryToAddressMethod(active[0]);
    AddressMethod destMethod = convertBinaryToAddressMethod(active[1]);

    unsigned word =  (op->opcode << 6);
    if (first && (sourceMethod.reg || sourceMethod.index))
        word = word | (sourceMethod.reg ? (REGISTER_DIRECT_ADDR << 4) : (INDEX_ADDR << 4));
    else if (first && (sourceMethod.direct || sourceMethod.immediate))
        word = word | (sourceMethod.direct ? (DIRECT_ADDR << 4) : (IMMEDIATE_ADDR << 4));
    if (second && (destMethod.reg || destMethod.index))
        word = word | (destMethod.reg ? (REGISTER_DIRECT_ADDR << 2) : (INDEX_ADDR << 2));
    else if (second && (destMethod.direct || destMethod.immediate))
        word = word | (destMethod.direct ? (DIRECT_ADDR << 2) : (IMMEDIATE_ADDR << 2));

    addWord(word, Code);
}

void writeDirectOperandWord(char *labelName)
{
    Item *item = getSymbol(labelName);

    printf("im trying to writeDirectOperandWord : %s\n", labelName);


    if (item == NULL) {
        /*yieldError*/
    }
    
    if (isExternal(labelName))
    {
        addWord((E) | item->val.s.value, Code);
        updateExtPositionData(labelName);
    }
    else
    {
        addWord((R) | item->val.s.value, Code);
    }
}

void writeIndexOperandWord(char *value)
{
    char *offset = strchr(value, '[');
    char *labelName = strtok(value, " [");

    Item *arrAddres = getSymbol(labelName);
    Item *offsetAddress;
    unsigned result;
    
    printf("im trying to writeIndexOperandWord : %s\n", value);

    if (arrAddres == NULL) {
        /*yieldError*/
    }

    if (!isValidIndexParameter(offset)) {
        /*yieldError*/
    }

    offsetAddress = getSymbol(value);
    if (offsetAddress != NULL) {
        result = offsetAddress->val.s.value;
    } else {
        result = atoi(value);
    }

    if (isExternal(labelName))
    {
        addWord((unsigned)(E) | arrAddres->val.s.value, Code);
        addWord((unsigned)(E) | result, Code);
        updateExtPositionData(labelName);
    }
    else
    {
        addWord((unsigned)(R) | arrAddres->val.s.value, Code);
        addWord((unsigned)(R) | result, Code);
    }
}

void writeImmediateOperandWord(char *operand)
{
    Item *item = getSymbol(operand);    

    if (item != NULL) {
        addWord(item->val.s.value, Code);
    } else {
        operand++;
        if ((*operand & A) == 0) {
            addWord(atoi(operand), Code);
        }
    }
}

void writeRegisterOperandWord(char *source, char *destination)
{
    int srcNumber = source != NULL ? getRegisteryNumber(source) : 0;
    int destNumber = destination != NULL ?  getRegisteryNumber(destination) : 0;

    unsigned word = (srcNumber << 5) & (destNumber << 2);

    addWord(word, Code);
}

Bool detectOperandType(char *operand, AddressMethodsEncoding active[2], int type)
{
    if (isRegistery(operand)) {
        active[type].firstDigit = 1;
        active[type].secondDigit = 1;
    } else if (isValidImmediateParamter(operand)) {
        active[type].firstDigit = 0;
        active[type].secondDigit = 0;
    }
    else if (isValidIndexParameter(operand)) {
        active[type].firstDigit = 0;
        active[type].secondDigit = 1;
    } else
    {
        if (isSymbolExist(operand))
        {
            if (isEntry(operand) && !isNonEmptyEntry(operand))
                return yieldError(entryDeclaredButNotDefined);
            active[type].firstDigit = 1;
            active[type].secondDigit = 0;
        }
        else
            return yieldError(labelNotExist);
    }
    return True;
}
