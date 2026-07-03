#include "Stack.h"

void      operatorStackInit  (OperatorStack *stack){ stack->topIndex=-1;}
int       operatorStackEmpty (OperatorStack *stack){return stack->topIndex==-1;}
int       operatorStackFull  (OperatorStack *stack){return stack->topIndex==MAX_STACK_SIZE-1;} //MAX_STACK_SIZE是長度，INDEX-1

/* 推入：把 value 放到堆疊頂端 */
CalcError operatorStackPush  (OperatorStack *stack, char value)
{
    if (operatorStackFull(stack)){return CALC_ERR_OVERFLOW ;}
    stack->topIndex++; //top 往上移一格
    stack->data[stack->topIndex]=value; //存入資料
    return  CALC_OK;
}
/* 取出並回傳頂端元素 */
char operatorStackPop(OperatorStack *stack)
{
    return stack->data[stack->topIndex--]; //取值後頂端下移
}
/* 查看頂端元素（不取出） */
 char operatorStackPeek(OperatorStack *stack)
{
    return stack->data[stack->topIndex]; //取值後不下移
}

void      numberStackInit  (NumberStack *stack){stack->topIndex=-1;}
int       numberStackEmpty (NumberStack *stack){return stack->topIndex==-1;}
int       numberStackFull  (NumberStack *stack){return stack->topIndex==MAX_STACK_SIZE-1;}

CalcError numberStackPush  (NumberStack *stack, double value)
{
    if(numberStackFull(stack)) 
    {
       return CALC_ERR_OVERFLOW;
    }
    stack->topIndex++;
    stack->data[stack->topIndex]=value;
    return CALC_OK;
}
 double    numberStackPop   (NumberStack *stack){
    return stack->data[stack->topIndex--];
}
 double numberStackPeek (NumberStack *stack){
    return stack->data[stack->topIndex];
}