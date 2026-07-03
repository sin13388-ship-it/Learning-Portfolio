#ifndef STACK_H
#define STACK_H

#include "TextCalculator.h"

/* 運算子堆疊 */
typedef struct {
    char data[MAX_STACK_SIZE];
    int  topIndex;
} OperatorStack;

//改成公開出去不能加static

void      operatorStackInit  (OperatorStack *stack);
int       operatorStackEmpty (OperatorStack *stack);
int       operatorStackFull  (OperatorStack *stack);
CalcError operatorStackPush  (OperatorStack *stack, char value);
char      operatorStackPop   (OperatorStack *stack);
char      operatorStackPeek  (OperatorStack *stack);

/* 數字堆疊 */
typedef struct {
    double data[MAX_STACK_SIZE];
    int    topIndex;
} NumberStack;

void      numberStackInit  (NumberStack *stack);
int       numberStackEmpty (NumberStack *stack);
int       numberStackFull  (NumberStack *stack);
CalcError numberStackPush  (NumberStack *stack, double value);
double    numberStackPop   (NumberStack *stack);
double    numberStackPeek  (NumberStack  *stack);

#endif