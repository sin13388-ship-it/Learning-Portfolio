#include "Token.h"

/*
* 需要將公式拆成一個個詞元(token)
* 步驟拆解和Coding的相關概念，寫在markdown 裡

*/


CalcError tokenize(const char *expressionString,
                   Token       tokenList[],
                   int        *tokenCount)
{
    const char *cursor =expressionString;
    int lastWasOperatorOrStart=1; /* 1 =true，0 = false；初始值 1 表示算式開頭 */

    /*開始解析，遍歷不定陣列用while，直到字串結尾符號 '\0'  null character */

    while (*cursor !='\0')
    {

        /*處理空白, Tab*/
        if (*cursor == ' ' || *cursor=='\t')
        {
            cursor++;
            continue;
        }
        
        /*邊界檢查*/
        if (*tokenCount >= MAX_POSTFIX_TOKENS) return CALC_ERR_OVERFLOW;
        
        Token *currentToken =&tokenList[*tokenCount]; /*current token 本來就只存活一次，建立最小範圍職責的習慣*/        
        
        /*小數點, 處理正負號*/
        if( isdigit(*cursor) || *cursor=='.' ||
            (*cursor=='+' && lastWasOperatorOrStart)||
            (*cursor=='-' && lastWasOperatorOrStart))
        {
            char *endpointer;
            double parseNumber=strtod(cursor, &endpointer);

            if(endpointer==cursor) return CALC_ERR_SYNTAX; /*解析失敗會傳回初始的指標*/

            currentToken->type=TOKEN_NUMBER;
            currentToken->numberValue=parseNumber;
            
            cursor=endpointer; /*指向剩下的位置*/

            lastWasOperatorOrStart=0; /*解析完一個數字*/

        }
        /*運算子或括號*/
        else if (*cursor=='+' || *cursor=='-' ||
                 *cursor=='*' || *cursor=='/' ||
                 *cursor=='^' ||
                 *cursor=='(' || *cursor==')')
        {
            char parseOperator=(*cursor);
            currentToken->type=TOKEN_OPERATOR;
            currentToken->operatorChar=parseOperator;           
            /*出現右括號時下一個還是運算元，不然視為解析完畢*/
            lastWasOperatorOrStart=(*cursor !=')');
            cursor++;
        }
        else 
        {
            return  CALC_ERR_SYNTAX;
        }

        (*tokenCount)++; //注意優先順序，寫成 *tokenCount++ 只會增加指標值

       
    }
     return CALC_OK;

}