#include "data.h"

Bool handleOperation(char *operationName, char *args)
{
    const Operation *p = getOperationByName(operationName);
    AddressMethodsEncoding active[2] = {{0,0}, {0, 0}};
    char *first = 0;
    char *second = 0;
    char *extra = 0;
    Bool areOperandsLegal;

    if (*args)
        areOperandsLegal = verifyCommaSyntax(args);

    first = strtok(args, _TOKEN_FORMAT_SECOND);
    if (first)
    {
        second = strtok(NULL, _TOKEN_FORMAT_SECOND);
        if (second)
        {
            extra = strtok(NULL, _TOKEN_FORMAT_SECOND);
            if (extra)
                return yieldError(extraOperandsPassed);
        }
        else
            second = 0;
    }
    areOperandsLegal = parseOperands(first, second, p, active) && areOperandsLegal;

    if (areOperandsLegal)
    {
        int size = 1;
        AddressMethod firstMethod = convertBinaryToAddressMethod(active[0]);
        AddressMethod secondMethod = convertBinaryToAddressMethod(active[1]);

        if ((firstMethod.immediate || secondMethod.immediate) || (firstMethod.direct || secondMethod.direct))
            size++;
        if (firstMethod.index || secondMethod.index)
            size += 2;
        if (!firstMethod.immediate && !firstMethod.direct && !firstMethod.index && !firstMethod.reg && 
            !secondMethod.immediate && !secondMethod.direct && !secondMethod.index && !secondMethod.reg)
            size = 1;

        active[0].firstDigit = active[0].secondDigit = 0;
        active[1].firstDigit = active[1].secondDigit = 0;
        increaseInstructionCounter(size);
    }

    return areOperandsLegal;
}

Bool parseOperands(char *src, char *des, const Operation *op, AddressMethodsEncoding active[2])
{
    int expectedOperandsCount = 0;
    int operandsPassedCount = 0;
    Bool isValid = True;

    Bool hasSource = (op->src.direct || op->src.immediate || op->src.reg || op->src.index);
    Bool hasDestination = (op->des.direct || op->des.immediate || op->des.reg || op->des.index);

    if (src)
        operandsPassedCount++;
    if (des)
        operandsPassedCount++;
    if (hasSource)
        expectedOperandsCount++;
    if (hasDestination)
        expectedOperandsCount++;

    if (expectedOperandsCount == 1 && operandsPassedCount == 1)
    {
        des = src;
        src = 0;
    }

    if ((expectedOperandsCount == operandsPassedCount) && expectedOperandsCount == 0)
        return True;


    if (operandsPassedCount > expectedOperandsCount)
        isValid = yieldError(extraOperandsPassed);

    if (hasSource)
    {
        isValid = !src? yieldError(requiredSourceOperandIsMissing) : validateOperandMatch(op->src, active, src, 0) && isValid;
    }
    if (hasDestination)
    {
        isValid = !des? yieldError(requiredDestinationOperandIsMissing) : validateOperandMatch(op->des, active, des, 1) && isValid;
    }

    return isValid;
}

Bool validateOperandMatch(AddressMethod allowedAddrs, AddressMethodsEncoding active[2], char *operand, int type)
{
    Bool isAny = isValidImmediateParamter(operand) || isValidIndexParameter(operand) || isRegistery(operand) || verifyLabelNaming(operand);
    Bool isImmediate = isValidImmediateParamter(operand);
    Bool isDirectIndex = !isImmediate && isValidIndexParameter(operand);
    Bool isReg = !isDirectIndex && !isImmediate && isRegistery(operand);
    Bool isDirect = !isReg && !isDirectIndex && !isImmediate && verifyLabelNaming(operand);

    if (isValidIndexParameter(operand) && !isDirectIndex)
        return yieldError(IndexOperandParameterNoNumber);

    if (!isAny)
        return type == 1 ? yieldError(illegalInputPassedAsOperandDesOperand) : yieldError(illegalInputPassedAsOperandSrcOperand);

    else if (!allowedAddrs.reg && isReg)
        return type == 1 ? yieldError(desOperandTypeIsNotAllowed) : yieldError(srcOperandTypeIsNotAllowed);
    else if (!allowedAddrs.immediate && isImmediate)
        return type == 1 ? yieldError(desOperandTypeIsNotAllowed) : yieldError(srcOperandTypeIsNotAllowed);
    else if (!allowedAddrs.direct && isDirect)
        return type == 1 ? yieldError(desOperandTypeIsNotAllowed) : yieldError(srcOperandTypeIsNotAllowed);
    else if (!allowedAddrs.index && isDirectIndex)
        return type == 1 ? yieldError(desOperandTypeIsNotAllowed) : yieldError(srcOperandTypeIsNotAllowed);

    if (isImmediate) {
        active->firstDigit = 0;
        active->secondDigit = 0;
    } else if (isDirect) {
        active->firstDigit = 1;
        active->secondDigit = 0;
    } else if (isDirectIndex) {
        active->firstDigit = 0;
        active->secondDigit = 1;
    } else {
        active->firstDigit = 1;
        active->secondDigit = 1;
    }

    return True;
}

Bool handleInstruction(int type, char *firstToken, char *nextTokens, char *line)
{
    if (isInstruction(firstToken))
    {
        if (type == _TYPE_DATA)
        {
            return verifyDataArguments(line) ? True : False;
        }
        else if (type == _TYPE_STRING)
            return verifyStringArguments(line) ? True : False;

        if (type == _TYPE_ENTRY || type == _TYPE_EXTERNAL)
        {
            if (nextTokens)
            {
                char *labelName = cloneString(nextTokens);
                nextTokens = strtok(NULL, _TOKEN_FORMAT);
                if (nextTokens)
                {
                    yieldError(illegalApearenceOfCharactersInTheEndOfTheLine);
                    return False;
                }
                else
                {
                    if (type == _TYPE_ENTRY)
                        return addSymbol(labelName, 0, 0, 0, 1, 0, 0) ? True : False;
                    if (type == _TYPE_EXTERNAL)
                        return addSymbol(labelName, 0, 0, 0, 0, 1, 0) ? True : False;
                }

                free(labelName);
            }
            else
            {
                yieldError(emptyDeclaretionOfEntryOrExternalVariables);
                return False;
            }
        }
    }
    else if (isLabelDeclaration(firstToken))
    {
        int dataCounter = getDC();
        Bool isLabelNameAvailable;
        firstToken[strlen(firstToken) - 1] = '\0';
        isLabelNameAvailable = !isLabelNameAlreadyTaken(firstToken, Symbol);
        if (!isLabelNameAvailable)
            yieldError(illegalSymbolNameAlreadyInUse);

        if (((type == _TYPE_DATA && verifyDataArguments(line)) || 
            (type == _TYPE_STRING && verifyStringArguments(line))) && isLabelNameAvailable)

        {
            return addSymbol(firstToken, dataCounter, 0, 1, 0, 0, 0) ? True : False;
        } else
            return False;
    } else
        yieldError(undefinedOperation);

    return False;
}

Bool handleLabel(char *labelName, char *nextToken, char *line)
{
    Bool isValid = True;
    if (!labelName || !nextToken || !line)
        return False;
    if (isInstruction(nextToken))
    {
        int instruction = getInstructionType(nextToken);
        if (!isInstructionStrict(nextToken))
        {
            isValid = yieldError(missinSpaceAfterInstruction);
            nextToken = getInstructionNameByType(instruction);
        }

        if (instruction == _TYPE_ENTRY || instruction == _TYPE_EXTERNAL)
        {
            char *next = strtok(NULL, _TOKEN_FORMAT);
            if (next)
                return handleInstruction(instruction, nextToken, next, line) && isValid;
            else
                return yieldWarning(emptyLabelDecleration);
        }
        else
            return handleInstruction(instruction, labelName, nextToken, line) && isValid;
    }

    else if (isOperationName(nextToken))
    {
        int icAddress = getIC();
        char args[MAX_LINE_LEN] = {0};
        int offset = (int)(strlen(labelName) + strlen(nextToken) + 1);
        strcpy(args, &line[offset]);
        if (handleOperation(nextToken, args))
            return addSymbol(labelName, icAddress, 1, 0, 0, 0, 0) ? True : False;
        else
            return False;
    } 
    else {
        yieldError(illegalLabelUseExpectedOperationOrInstruction);
    }
    return False;
}


Bool handleDefinition(char *name, char *line)
{
    Bool isValid = True;
    int dcAddress;
    if (!name || !line)
        return False;
    if (!verifyDefinitionArguments(line))
    {
        yieldError(illegalLabelUseExpectedOperationOrInstruction);
        return False;
    }
    dcAddress = getDC();
    return addSymbol(name, dcAddress, 0, 0, 0, 0, 1) ? True : False;
}