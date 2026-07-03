#ifndef TOKEN_H
#define TOKEN_H

#include "TextCalculator.h"

typedef enum {
    TOKEN_NUMBER,
    TOKEN_OPERATOR
} TokenType;

typedef struct {
    TokenType type;
    double    numberValue;
    char      operatorChar;
} Token;

/* 函式宣告 */
CalcError tokenize(const char *expressionString,
                   Token       tokenList[],
                   int        *tokenCount);

#endif