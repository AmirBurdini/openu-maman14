#include "data.h"

Bool writeOperationBinary(char *operationName, char *args)
{
    const Operation *op = getOperationByName(operationName);
    char *src, *dest;
    int wordCount = 0;
    Bool desReg = False, srcReg=False;
    AddressMethodsEncoding active[2] = {{0, 0}, {0, 0}};
    src = strtok(args, _TOKEN_FORMAT_SECOND);
    dest = strtok(NULL, _TOKEN_FORMAT_SECOND);

    printf("AFTER STRTOK src: %s + dest: %s \n",src, dest);

    if (src && (detectOperandType(src, active, 0)))
    {
        
        if (active[0].firstDigit && active[0].secondDigit) {
            srcReg=True;
        }else wordCount++;
    }

    if (dest && (detectOperandType(dest, active, 1)))
    {   
        
        if (active[1].firstDigit && active[1].secondDigit) {
            desReg = True;
        }else wordCount++;
    }

    writeFirstWord(src, dest, active, op);
    if (srcReg || desReg) {
        writeRegisterOperandWord(src, dest);
    }
    if (wordCount ==1 && srcReg) {
        writeAdditionalOperandsWords(op, active[1], dest);
    }
    if (wordCount ==1 && desReg) {
         writeAdditionalOperandsWords(op, active[0], src);
    }
    
    if (wordCount == 1 && !srcReg && !desReg) {
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
    } else if (method.direct) 
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
    unsigned address = 0;
    if (item == NULL) {
        /*yieldError*/
    }
    
    if (isExternal(labelName))
    {   
        address = getIC();
        addWord((E) | address, Code);
        printf ("direct external : %s , %u \n", labelName, address);
        updateExtPositionData(labelName, address);
    }
    else
    {
        address = getSymbolAddress(labelName);
        addWord((R) | address, Code);
    }
}

void writeIndexOperandWord(char *value)
{
    char *offset = strchr(value, '[');
    char *labelName = strtok(value, " [");

    Item *labelSymbol = getSymbol(labelName);
    Item *offsetAddress;
    unsigned valueAddress, arrAddress;
    
    if (labelSymbol == NULL) {
        /*yieldError*/
    }
    arrAddress = labelSymbol->val.s.value;
    if (!isValidIndexParameter(offset)) {
        /*yieldError*/
    }

    offsetAddress = getSymbol(value);
    if (offsetAddress != NULL) {
        valueAddress = offsetAddress->val.s.value;
    } else {
        valueAddress = atoi(value);
    }

    if (isExternal(labelName))
    {
        printf ("index external : %s , %u , %u \n", labelName, arrAddress, valueAddress);
        addWord((unsigned)(E) | arrAddress, Code);
        addWord((unsigned)(E) | valueAddress, Code);
        updateExtPositionData(labelName, arrAddress);
    }
    else
    {
        addWord((unsigned)(R) | arrAddress, Code);
        addWord((unsigned)(R) | valueAddress, Code);
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
        /* solution might be here Amir*/
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
