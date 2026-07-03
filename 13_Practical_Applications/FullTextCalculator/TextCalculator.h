#ifndef TEXT_CALCULATOR_H
#define TEXT_CALCULATOR_H

//引用會用到的庫
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>



/* ── ANSI 顏色碼 ─────────────────────────────────────────── */
#define COLOR_RESET   "\033[0m"
#define COLOR_TITLE   "\033[1;36m"
#define COLOR_PROMPT  "\033[1;33m"
#define COLOR_RESULT  "\033[1;32m"
#define COLOR_ERROR   "\033[1;31m"
#define COLOR_INFO    "\033[0;37m"

/* ── 常數 ────────────────────────────────────────────────── */
#define INPUT_BUFFER_SIZE   512   /* 使用者輸入的最大長度       */
#define MAX_STACK_SIZE      256   /* 堆疊的最大容量             */
#define MAX_POSTFIX_TOKENS  256   /* 後綴表達式最多幾個 token   */

/* ── 錯誤碼 ──────────────────────────────────────────────── */
typedef enum {
    CALC_OK            =  0,
    CALC_ERR_SYNTAX    = -1,
    CALC_ERR_DIV_ZERO  = -2,
    CALC_ERR_UNMATCHED = -3,
    CALC_ERR_OVERFLOW  = -4    /* 堆疊滿了 */
} CalcError;

 int operatorPrecedence(char op);
 int isRightAssociative(char op);



#endif // TEXT_CALCULATOR_H