#include "TextCalculator.h"
#include "Token.h"
#include "Stack.h"


/*
- 需要一個運算元堆疊
- 遍歷input token，數字直接放進佇列'
- 出現左括號放進operator 堆疊，作為mark
- 一般運算子要比較優先權再放入堆疊，高的放上面
- 出現右括號把堆疊中的運算子彈出放到佇列，直到出現左括號
- ->堆疊都空了還是沒有，輸出語法錯誤

*/

static CalcError shuntingYard(const Token inputToken[],
                              int inputTokenCount,
                            Token outputPostfix[],
                            int *outputTokenfixCount)
{
    OperatorStack _operatorStack;
    operatorStackInit(&_operatorStack);
    for(int i=0; i<inputTokenCount; i++){        

        const Token *currentToken=&inputToken[i];        /* 養成習慣，分裝到自己的盤子 */

        /* 處理數字的場合，直接放進佇列*/
        if (currentToken->type==TOKEN_NUMBER) 
        {
            outputPostfix[(*outputTokenfixCount)++]=*currentToken;
            continue;
        }

        
        char op=currentToken->operatorChar;
        /*遇到左括號，放進堆疊*/
        if (op=='(')
        {
            operatorStackPush(&_operatorStack,op);
            continue;
        }
        
        /*遇到右括號，除了'('其他的運算子全塞到佇列*/
         if (op==')')
        {
            while (!operatorStackEmpty(&_operatorStack) && 
                    operatorStackPeek(&_operatorStack)!='(')
                {
                    Token operatorToken;
                    operatorToken.type=TOKEN_OPERATOR;
                    operatorToken.operatorChar=operatorStackPop(&_operatorStack);
                    outputPostfix[(*outputTokenfixCount)++]= operatorToken;

                    /* 語法錯誤的判斷，找完還是沒有左括號 */
                    if(operatorStackEmpty(&_operatorStack))
                    return CALC_ERR_UNMATCHED;
                   
                }
                
            /*捨棄左括號 */
            operatorStackPop(&_operatorStack);
            continue;
        }       
        /*一般運算子，運算子堆疊中目前的優先順序，視需求交換*/
        /*如果遇到 5*3+1+1+8+3*2+2, operatorStack 可能會有連續同級的運算子 */
        /*用 while 才能一次彈出 */
        /*堆疊中的優先權如果大於當前則彈出，放到佇列去*/

        while(!operatorStackEmpty(&_operatorStack) &&
                operatorStackPeek(&_operatorStack)!='(' &&
                (operatorPrecedence(operatorStackPeek(&_operatorStack)) > operatorPrecedence(op) ||
                operatorPrecedence(operatorStackPeek(&_operatorStack)) == operatorPrecedence(op) &&
               !isRightAssociative(op))
            ) 
            {
               Token operatorToken;  
               
               operatorToken.type=TOKEN_OPERATOR;
               operatorToken.operatorChar=operatorStackPop(&_operatorStack);
               outputPostfix[(*outputTokenfixCount)++]=operatorToken;                             

            }
            operatorStackPush(&_operatorStack, op);        

     }
    /* 剩下的全部放到佇列，順便判斷是否括號不對稱 */
    while(!operatorStackEmpty(&_operatorStack))
    {
        
        char remainingOperator =operatorStackPop(&_operatorStack);
        if(remainingOperator=='(') return CALC_ERR_UNMATCHED;            
        
        Token operatorToken;  
            
            operatorToken.type=TOKEN_OPERATOR;
            operatorToken.operatorChar=remainingOperator ;
            outputPostfix[(*outputTokenfixCount)++]=operatorToken;     
    }

   return CALC_OK;

}
/*四則運算*/
 int operatorPrecedence(char op)
{
    if(op=='+'||op=='-') return 1;
    if(op=='*'||op=='/') return 2;
    if(op=='^') return 3;
    return 0; /* 例外 */
}
/*右結合律*/
 int isRightAssociative(char op)
{
    return op=='^';
} 

CalcError evaluatePostfix(const Token outputPostfix[], int outputTokenfixCount, double *outputResult)
{
    NumberStack calculatedStack;
    numberStackInit(&calculatedStack);    

    for(int i=0; i< outputTokenfixCount; i++)    
    {
        /*關心變數的生命週期 ， 不會變動的加const*/
        const Token *currentToken =&outputPostfix[i];

        /* 數字直接推入堆疊，下一個 */
        /* 由誰檢查 error ? */
        if(currentToken->type==TOKEN_NUMBER) 
        {
            CalcError err; 
            err = numberStackPush(&calculatedStack, currentToken->numberValue);
            if (err != CALC_OK) return err;  
            continue;          
        }           

        
        /* 連續取出兩的運算元 */
        /* LIFO */
        
        if(numberStackEmpty(&calculatedStack)) return CALC_ERR_SYNTAX;
        double rightOperand =numberStackPop(&calculatedStack);


        if(numberStackEmpty(&calculatedStack)) return CALC_ERR_SYNTAX;
        double leftOperand =numberStackPop(&calculatedStack);


        /* 運算 */
        /*之後要考慮重構 */

        double computedResult;
        char op =currentToken->operatorChar;

        switch (op)
        {
        case '+':
            computedResult =leftOperand + rightOperand;           
            break;
        case '-':
            computedResult =leftOperand - rightOperand; 
            break;
        case '*':
           computedResult =leftOperand * rightOperand; 
           break;
        case '/' :
            if(rightOperand ==0.0) return CALC_ERR_DIV_ZERO;
            computedResult =leftOperand / rightOperand; 
            break;
        case '^' :
            computedResult =pow(leftOperand,rightOperand);
            break;
        default:
            return CALC_ERR_SYNTAX;
        }
        numberStackPush(&calculatedStack, computedResult);     
    }

    /* 最終只會剩下一個元素在堆疊裡 */
    if (numberStackEmpty(&calculatedStack)) return CALC_ERR_SYNTAX;
    *outputResult=numberStackPop(&calculatedStack);
    if (!numberStackEmpty(&calculatedStack)) return CALC_ERR_SYNTAX;

    return CALC_OK;

}

CalcError evaluateInputString(const char* inputString, double *calculatedResult){    
    Token       testTokens[MAX_POSTFIX_TOKENS];
    int         tokenCount = 0;

    CalcError errorCode = tokenize(inputString, testTokens, &tokenCount);
    if (errorCode != CALC_OK) return errorCode;

    Token postfixTestTokens[MAX_POSTFIX_TOKENS];
    int postfixTokenCount=0;

    errorCode=shuntingYard(testTokens,tokenCount,postfixTestTokens,&postfixTokenCount);
    if (errorCode != CALC_OK) return errorCode;

    double Result;
    errorCode=evaluatePostfix(postfixTestTokens, postfixTokenCount,&Result);
    if (errorCode != CALC_OK) return errorCode;

    *calculatedResult=Result;  
    
    return CALC_OK;
}

const char* getErrorMessage(CalcError errorCode)
{
    switch (errorCode)
    {
        case -1:
            return "Syntax error!";
        case -2:
            return "Division by zero!";
        case -3:
            return "Mismatched parentheses!";
        case -4:
            return "Stack overflow!";
        default:
            return "Unexpected error!";
    }
}

/* ============================================================
 *  說明
 * ============================================================ */
static void printHelpMessage(void)
{
    printf(COLOR_INFO
        "  ┌──────────────────────────────────────────────┐\n"
        "  │  運算子  說明           範例                  │\n"
        "  │  ──────  ───────────   ────────────────────  │\n"
        "  │    +     加法           1 + 2 + 3             │\n"
        "  │    -     減法 / 負號    10 - -4               │\n"
        "  │    *     乘法           2 * 3 * 4            │\n"
        "  │    /     除法           100 / 5 / 4          │\n"
        "  │    ^     次方(右結合)   2 ^ 3 ^ 2 = 2^(3^2)   │\n"
        "  │    ( )   括號           (1 + 2) * (3 + 4)    │\n"
        "  │                                              │\n"
        "  │  優先順序：() > ^ > 負號 > * / > + -          │\n"
        "  │  輸入 h 說明，q 離開                          │\n"
        "  └──────────────────────────────────────────────┘\n"
        COLOR_RESET);
}

static void printFormattedRsult(double calculatedResult){

    /* 格式化結果，如果結果是整數，不顯示.0 */
    /* 若浮點數則使用通用格式，顯示長度為10 */
    /* 整數顯示範圍為 long long */

    /* 確定是否為整數型態 */
    if(calculatedResult ==(long long)calculatedResult &&
        calculatedResult>= -1e15 && calculatedResult <=1e15)
    {
        printf(COLOR_RESULT"%.0f\n"COLOR_RESET,calculatedResult);
    }
    else
        printf(COLOR_RESULT"%10g\n"COLOR_RESET,calculatedResult);
}



int main (void)
{    
    char inputString[INPUT_BUFFER_SIZE];
    CalcError errorCode;

    printf(COLOR_TITLE 
            "\n"
            "-------------------------------\n"
            "- Text Calulator Stack version-\n"          
            "-----     Q/q/Exit exit    ----\n"
            "-----     h/help manual    ----\n");  

    while(1)
    {
        printf(COLOR_PROMPT "calc> " COLOR_RESET);
        fflush(stdout); /* 強迫輸出 */
        if(fgets(inputString, INPUT_BUFFER_SIZE,stdin)==NULL) break;
        /* 把結束字元換成字串字元 */
        inputString[strcspn(inputString,"\r\n")]='\0';
        /* 移除空白或空白行 */
        const char *trimmedString=inputString;
        while (*trimmedString ==' ' | *trimmedString =='\t')
        {
            trimmedString++;
        }
        if(*trimmedString=='\0') continue;
        if(strcmp(trimmedString,"q")==0 ||
            strcmp(trimmedString, "quit")==0 ||
            strcmp(trimmedString, "Exit")==0 )
            {
                printf(COLOR_INFO "ByeBye...\n" COLOR_RESET);
                break;
            }
            
        if(strcasecmp(trimmedString,"h")==0 ||
            strcmp(trimmedString, "help")==0){
                printHelpMessage();
                continue;
            }

        double calculatedResult;   
        errorCode= evaluateInputString(trimmedString,&calculatedResult);

        if(errorCode!=CALC_OK) {
            printf(COLOR_ERROR "Error code  %d : %s \n" COLOR_RESET, errorCode, getErrorMessage(errorCode) );
        }
        else {            
            printFormattedRsult(calculatedResult);
        }        
    }

    return 0;
}

