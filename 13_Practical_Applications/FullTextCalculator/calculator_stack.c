/*
 * ============================================================
 *  文字型計算機 — 堆疊 + 後綴表達式版本  v1.0
 *
 *  【核心概念】Shunting-Yard 演算法 + 堆疊求值
 *
 *  計算一條算式分成兩個階段：
 *
 *  階段一：中綴 → 後綴（Infix to Postfix）
 *    使用 Shunting-Yard 演算法，把我們平常寫的算式
 *    （中綴：2 + 3 * 4）轉成後綴表達式（Postfix：2 3 4 * +）
 *    後綴又叫「逆波蘭表示法 RPN」，特點是不需要括號，
 *    優先順序已經內嵌在順序裡。
 *
 *  階段二：後綴求值（Postfix Evaluation）
 *    用一個數字堆疊，從左到右掃描後綴表達式：
 *      遇到數字 → 推入堆疊
 *      遇到運算子 → 從堆疊取出兩個數字，計算後推回去
 *    最後堆疊裡剩下的唯一數字就是答案。
 *
 *  【範例】 2 + 3 * 4
 *    中綴：  2 + 3 * 4
 *    後綴：  2 3 4 * +       ← Shunting-Yard 轉換
 *    求值：
 *      讀到 2     → 堆疊: [2]
 *      讀到 3     → 堆疊: [2, 3]
 *      讀到 4     → 堆疊: [2, 3, 4]
 *      讀到 *     → 取出 4 和 3，算 3*4=12，堆疊: [2, 12]
 *      讀到 +     → 取出 12 和 2，算 2+12=14，堆疊: [14]
 *      結束       → 答案是 14 ✓
 *
 * ============================================================
 *  對比遞迴下降版本：
 *    遞迴下降：邊解析邊計算，優先順序靠「函式呼叫層級」處理
 *    堆疊版本：先全部轉換成後綴，再統一計算，優先順序靠「兩個堆疊」處理
 * ============================================================
 */

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


/* ============================================================
 *  Token（詞元）：算式的最小單位
 *
 *  我們先把字串「切碎」成一個一個的 Token，
 *  就像把句子拆成一個個單詞再處理。
 *
 *  Token 有兩種類型：
 *    TOKEN_NUMBER  ：一個數字，例如 3.14、-2
 *    TOKEN_OPERATOR：一個運算子，例如 +、-、*、/、^
 *                    或括號 (、)
 * ============================================================ */
typedef enum {
    TOKEN_NUMBER,
    TOKEN_OPERATOR
} TokenType;

typedef struct {
    TokenType type;
    double    numberValue;   /* type == TOKEN_NUMBER 時使用   */
    char      operatorChar;  /* type == TOKEN_OPERATOR 時使用 */
} Token;


/* ============================================================
 *  堆疊資料結構
 *
 *  堆疊（Stack）是一種「後進先出 LIFO」的資料結構：
 *    push：把元素放到堆疊「頂端」
 *    pop ：從堆疊「頂端」取出元素
 *    peek：查看頂端元素但不取出
 *
 *  就像疊盤子：最後放上去的盤子，最先被取走。
 *
 *  我們需要兩種堆疊：
 *    OperatorStack：放運算子（char），用於 Shunting-Yard 演算法
 *    NumberStack  ：放數字（double），用於後綴求值
 * ============================================================ */

/* ── 運算子堆疊（存 char）── */
typedef struct {
    char data[MAX_STACK_SIZE];
    int  topIndex;   /* 指向目前頂端的索引，-1 表示空堆疊 */
} OperatorStack;

static void  operatorStackInit  (OperatorStack *stack) { stack->topIndex = -1; }
static int   operatorStackEmpty (OperatorStack *stack) { return stack->topIndex == -1; }
static int   operatorStackFull  (OperatorStack *stack) { return stack->topIndex == MAX_STACK_SIZE - 1; }

/* 推入：把 value 放到堆疊頂端 */
static CalcError operatorStackPush(OperatorStack *stack, char value)
{
    if (operatorStackFull(stack)) return CALC_ERR_OVERFLOW;
    stack->topIndex++;                    /* 頂端往上移一格 */
    stack->data[stack->topIndex] = value; /* 存入值         */
    return CALC_OK;
}

/* 取出並回傳頂端元素 */
static char operatorStackPop(OperatorStack *stack)
{
    return stack->data[stack->topIndex--]; /* 取值後頂端往下移 */
}

/* 查看頂端元素（不取出） */
static char operatorStackPeek(OperatorStack *stack)
{
    return stack->data[stack->topIndex];
}

/* ── 數字堆疊（存 double）── */
typedef struct {
    double data[MAX_STACK_SIZE];
    int    topIndex;
} NumberStack;

static void  numberStackInit  (NumberStack *stack) { stack->topIndex = -1; }
static int   numberStackEmpty (NumberStack *stack) { return stack->topIndex == -1; }
static int   numberStackFull  (NumberStack *stack) { return stack->topIndex == MAX_STACK_SIZE - 1; }

static CalcError numberStackPush(NumberStack *stack, double value)
{
    if (numberStackFull(stack)) return CALC_ERR_OVERFLOW;
    stack->topIndex++;
    stack->data[stack->topIndex] = value;
    return CALC_OK;
}

static double numberStackPop(NumberStack *stack)
{
    return stack->data[stack->topIndex--];
}


/* ============================================================
 *  運算子優先順序
 *
 *  數字越大優先順序越高。
 *  Shunting-Yard 演算法靠比較優先順序來決定
 *  運算子要不要先從堆疊彈出。
 *
 *  括號不是真正的運算子，回傳 0 讓它永遠不會被彈出。
 * ============================================================ */
static int operatorPrecedence(char op)
{
    if (op == '+' || op == '-') return 1;   /* 最低 */
    if (op == '*' || op == '/') return 2;
    if (op == '^')              return 3;   /* 最高 */
    return 0;                               /* ( 或其他：不比較 */
}

/*
 *  右結合判斷：^ 是右結合，其餘都是左結合。
 *
 *  左結合：a - b - c = (a - b) - c  → 從左到右算
 *  右結合：a ^ b ^ c = a ^ (b ^ c)  → 從右到左算
 *
 *  這影響 Shunting-Yard 演算法中「何時彈出堆疊運算子」的條件。
 */
static int isRightAssociative(char op)
{
    return op == '^';
}


/* ============================================================
 *  階段一：將字串切成 Token 序列
 *
 *  輸入："2.5 + -3 * (4 ^ 2)"
 *  輸出：[2.5] [+] [-3] [*] [(] [4] [^] [2] [)]
 *
 *  重點：負號的處理
 *    '-' 在以下情況視為「一元負號」（屬於數字的一部分）：
 *      - 是算式的第一個字元
 *      - 前一個 Token 是運算子或左括號
 *    其他情況視為「二元減法運算子」
 * ============================================================ */
static CalcError tokenize(const char *expressionString,
                           Token       tokenList[],
                           int        *tokenCount)
{
    const char *cursor  = expressionString;
    *tokenCount = 0;

    /* 記錄「上一個 Token 是否為運算子或左括號」，用於判斷一元負號 */
    int lastWasOperatorOrStart = 1;  /* 1 = 是，0 = 否；初始值 1 表示算式開頭 */

    while (*cursor != '\0') {
        /* 跳過空白 */
        if (*cursor == ' ' || *cursor == '\t') {
            cursor++;
            continue;
        }

        /* 安全檢查：token 數量上限 */
        if (*tokenCount >= MAX_POSTFIX_TOKENS)
            return CALC_ERR_OVERFLOW;

        Token *currentToken = &tokenList[*tokenCount];

        /* ── 情況 A：數字（或一元負號開頭的負數）── */
        if (isdigit(*cursor) || *cursor == '.' ||
            (*cursor == '-' && lastWasOperatorOrStart) ||
            (*cursor == '+' && lastWasOperatorOrStart))
        {
            char  *endPointer;
            double parsedNumber = strtod(cursor, &endPointer);

            if (endPointer == cursor) return CALC_ERR_SYNTAX;

            currentToken->type        = TOKEN_NUMBER;
            currentToken->numberValue = parsedNumber;
            cursor = endPointer;
            lastWasOperatorOrStart = 0;   /* 剛讀完一個數字 */
        }
        /* ── 情況 B：運算子或括號 ── */
        else if (*cursor == '+' || *cursor == '-' ||
                 *cursor == '*' || *cursor == '/' ||
                 *cursor == '^' ||
                 *cursor == '(' || *cursor == ')')
        {
            currentToken->type         = TOKEN_OPERATOR;
            currentToken->operatorChar = *cursor;
            lastWasOperatorOrStart = (*cursor != ')'); /* ) 後面可能跟數字，視為非運算子 */
            cursor++;
        }
        /* ── 情況 C：無法識別的字元 ── */
        else {
            return CALC_ERR_SYNTAX;
        }

        (*tokenCount)++;
    }

    return CALC_OK;
}


/* ============================================================
 *  階段二：Shunting-Yard 演算法
 *  將 Token 序列（中綴）轉換為後綴表達式
 *
 *  演算法使用一個「運算子堆疊」和一個「輸出佇列」：
 *
 *  對每個 Token：
 *    如果是數字  → 直接放進輸出佇列
 *    如果是 (    → 推入運算子堆疊
 *    如果是 )    → 不斷把堆疊頂端彈出到輸出佇列，直到遇到 (
 *    如果是運算子 → 先把堆疊裡「優先順序 ≥ 自己」的運算子彈出，
 *                   再把自己推入堆疊
 *  最後把堆疊剩餘的運算子全部彈出到輸出佇列。
 *
 *  【範例】 2 + 3 * 4
 *
 *    Token   運算子堆疊   輸出佇列
 *    ─────   ──────────   ────────────
 *    2       []           [2]
 *    +       [+]          [2]
 *    3       [+]          [2, 3]
 *    *       [+, *]       [2, 3]         ← * 優先級 > +，不彈出 +
 *    4       [+, *]       [2, 3, 4]
 *    結束    []           [2, 3, 4, *, +] ← 堆疊清空，彈出 * 再彈出 +
 *
 *  後綴結果：2 3 4 * +
 * ============================================================ */
static CalcError shuntingYard(const Token inputTokens[],
                               int         inputTokenCount,
                               Token       outputPostfix[],
                               int        *outputTokenCount)
{
    OperatorStack operatorStack;
    operatorStackInit(&operatorStack);
    *outputTokenCount = 0;

    for (int i = 0; i < inputTokenCount; i++) {
        const Token *currentToken = &inputTokens[i];

        /* ── 數字：直接進輸出佇列 ── */
        if (currentToken->type == TOKEN_NUMBER) {
            outputPostfix[(*outputTokenCount)++] = *currentToken;
            continue;
        }

        char op = currentToken->operatorChar;

        /* ── 左括號：推入運算子堆疊，等待右括號來配對 ── */
        if (op == '(') {
            operatorStackPush(&operatorStack, op);
            continue;
        }

        /* ── 右括號：把堆疊裡的運算子彈出，直到遇到左括號 ── */
        if (op == ')') {
            while (!operatorStackEmpty(&operatorStack) &&
                   operatorStackPeek(&operatorStack) != '(') {
                /* 把彈出的運算子包成 Token 放進輸出佇列 */
                Token operatorToken;
                operatorToken.type         = TOKEN_OPERATOR;
                operatorToken.operatorChar = operatorStackPop(&operatorStack);
                outputPostfix[(*outputTokenCount)++] = operatorToken;
            }
            if (operatorStackEmpty(&operatorStack))
                return CALC_ERR_UNMATCHED;   /* 找不到對應的 ( */

            operatorStackPop(&operatorStack);   /* 丟掉 ( */
            continue;
        }

        /*
         * ── 一般運算子：比較優先順序後決定要不要先彈出堆疊 ──
         *
         * 彈出條件（兩者同時成立）：
         *   1. 堆疊頂端不是左括號
         *   2. 頂端運算子優先順序 > 自己，
         *      或（優先順序相同 且 自己是左結合）
         *
         * 右結合（^）的差異：
         *   左結合：2 - 3 - 4  先算 2-3，所以同優先的 - 要先彈出
         *   右結合：2 ^ 3 ^ 4  先算 3^4，所以同優先的 ^ 不能彈出
         */
        while (!operatorStackEmpty(&operatorStack) &&
               operatorStackPeek(&operatorStack) != '(' &&
               (operatorPrecedence(operatorStackPeek(&operatorStack)) > operatorPrecedence(op) ||
                (operatorPrecedence(operatorStackPeek(&operatorStack)) == operatorPrecedence(op) &&
                 !isRightAssociative(op))))
        {
            Token operatorToken;
            operatorToken.type         = TOKEN_OPERATOR;
            operatorToken.operatorChar = operatorStackPop(&operatorStack);
            outputPostfix[(*outputTokenCount)++] = operatorToken;
        }

        operatorStackPush(&operatorStack, op);   /* 把自己推入堆疊 */
    }

    /* 把堆疊剩餘的運算子全部清空到輸出佇列 */
    while (!operatorStackEmpty(&operatorStack)) {
        char remainingOp = operatorStackPop(&operatorStack);
        if (remainingOp == '(')
            return CALC_ERR_UNMATCHED;   /* 有多餘的 ( 沒被配對 */

        Token operatorToken;
        operatorToken.type         = TOKEN_OPERATOR;
        operatorToken.operatorChar = remainingOp;
        outputPostfix[(*outputTokenCount)++] = operatorToken;
    }

    return CALC_OK;
}


/* ============================================================
 *  階段三：後綴表達式求值
 *
 *  使用一個數字堆疊，從左到右掃描後綴表達式的每個 Token：
 *
 *    遇到數字  → push 進數字堆疊
 *    遇到運算子 → pop 出兩個數字（right 先出，left 後出）
 *                  計算結果後 push 回去
 *
 *  注意 pop 的順序：
 *    堆疊是後進先出，所以先 pop 出來的是「右運算元」，
 *    後 pop 出來的才是「左運算元」。
 *    例如堆疊 [2, 3]，遇到 -：
 *      rightOperand = pop() → 3
 *      leftOperand  = pop() → 2
 *      結果 = 2 - 3 = -1  ✓（不是 3 - 2 = 1）
 * ============================================================ */
static CalcError evaluatePostfix(const Token postfixTokens[],
                                  int         tokenCount,
                                  double     *resultOut)
{
    NumberStack numberStack;
    numberStackInit(&numberStack);

    for (int i = 0; i < tokenCount; i++) {
        const Token *currentToken = &postfixTokens[i];

        /* ── 數字：直接推入堆疊 ── */
        if (currentToken->type == TOKEN_NUMBER) {
            CalcError err = numberStackPush(&numberStack, currentToken->numberValue);
            if (err != CALC_OK) return err;
            continue;
        }

        /* ── 運算子：取出兩個運算元，計算後推回 ── */
        if (numberStackEmpty(&numberStack)) return CALC_ERR_SYNTAX;
        double rightOperand = numberStackPop(&numberStack);   /* 右邊先出 */

        if (numberStackEmpty(&numberStack)) return CALC_ERR_SYNTAX;
        double leftOperand  = numberStackPop(&numberStack);   /* 左邊後出 */

        double computedResult;
        char op = currentToken->operatorChar;

        switch (op) {
            case '+': computedResult = leftOperand + rightOperand; break;
            case '-': computedResult = leftOperand - rightOperand; break;
            case '*': computedResult = leftOperand * rightOperand; break;
            case '/':
                if (rightOperand == 0.0) return CALC_ERR_DIV_ZERO;
                computedResult = leftOperand / rightOperand;
                break;
            case '^':
                computedResult = pow(leftOperand, rightOperand);
                break;
            default:
                return CALC_ERR_SYNTAX;
        }

        numberStackPush(&numberStack, computedResult);   /* 結果推回堆疊 */
    }

    /* 正常情況下堆疊裡應該剩下恰好一個數字，就是最終答案 */
    if (numberStackEmpty(&numberStack)) return CALC_ERR_SYNTAX;
    *resultOut = numberStackPop(&numberStack);

    /* 如果堆疊還有剩餘，表示算式有多餘數字，語法錯誤 */
    if (!numberStackEmpty(&numberStack)) return CALC_ERR_SYNTAX;

    return CALC_OK;
}


/* ============================================================
 *  對外介面：整合三個階段
 *
 *  expressionString → tokenize → shuntingYard → evaluatePostfix → result
 * ============================================================ */
static CalcError evaluateExpression(const char *expressionString,
                                    double      *resultOut)
{
    Token  infixTokens  [MAX_POSTFIX_TOKENS];   /* 中綴 Token 序列 */
    Token  postfixTokens[MAX_POSTFIX_TOKENS];   /* 後綴 Token 序列 */
    int    infixCount  = 0;
    int    postfixCount = 0;
    CalcError errorCode;

    /* 階段一：切割 Token */
    errorCode = tokenize(expressionString, infixTokens, &infixCount);
    if (errorCode != CALC_OK) return errorCode;

    if (infixCount == 0) return CALC_ERR_SYNTAX;

    /* 階段二：中綴轉後綴 */
    errorCode = shuntingYard(infixTokens, infixCount,
                              postfixTokens, &postfixCount);
    if (errorCode != CALC_OK) return errorCode;

    /* 階段三：後綴求值 */
    return evaluatePostfix(postfixTokens, postfixCount, resultOut);
}


/* ============================================================
 *  格式化輸出
 * ============================================================ */
static void printFormattedResult(double resultValue)
{
    if (resultValue == (long long)resultValue &&
        resultValue >= -1e15 && resultValue <= 1e15)
        printf(COLOR_RESULT "  = %.0f\n" COLOR_RESET, resultValue);
    else
        printf(COLOR_RESULT "  = %.10g\n" COLOR_RESET, resultValue);
}

/* ============================================================
 *  說明
 * ============================================================ */
static void printHelpMessage(void)
{
    printf(COLOR_INFO
        "  ┌──────────────────────────────────────────────┐\n"
        "  │  運算子  說明           範例                  │\n"
        "  │  ──────  ───────────   ──────────────────── │\n"
        "  │    +     加法           1 + 2 + 3             │\n"
        "  │    -     減法 / 負號    10 - -4               │\n"
        "  │    *     乘法           2 * 3 * 4             │\n"
        "  │    /     除法           100 / 5 / 4           │\n"
        "  │    ^     次方(右結合)   2 ^ 3 ^ 2 = 2^(3^2)  │\n"
        "  │    ( )   括號           (1 + 2) * (3 + 4)     │\n"
        "  │                                               │\n"
        "  │  優先順序：() > ^ > 負號 > * / > + -          │\n"
        "  │  輸入 h 說明，q 離開                          │\n"
        "  └──────────────────────────────────────────────┘\n"
        COLOR_RESET);
}

/* ============================================================
 *  主程式
 * ============================================================ */
int main(void)
{
    char   inputBuffer[INPUT_BUFFER_SIZE];
    double calculationResult;

    printf(COLOR_TITLE
        "\n"
        "  ╔══════════════════════════════════════════════╗\n"
        "  ║    文字型計算機  v1.0 — 堆疊 + 後綴版本     ║\n"
        "  ║  支援小數、負數、括號、連續多項運算          ║\n"
        "  ╚══════════════════════════════════════════════╝\n"
        COLOR_RESET "\n");

    printHelpMessage();
    printf("\n");

    while (1) {
        printf(COLOR_PROMPT "calc> " COLOR_RESET);
        fflush(stdout);

        if (fgets(inputBuffer, INPUT_BUFFER_SIZE, stdin) == NULL)
            break;

        inputBuffer[strcspn(inputBuffer, "\r\n")] = '\0';

        const char *trimmedInput = inputBuffer;
        while (*trimmedInput == ' ' || *trimmedInput == '\t')
            trimmedInput++;

        if (*trimmedInput == '\0') continue;

        if (strcmp(trimmedInput, "q")    == 0 ||
            strcmp(trimmedInput, "quit") == 0 ||
            strcmp(trimmedInput, "exit") == 0) {
            printf(COLOR_INFO "  掰掰！\n" COLOR_RESET);
            break;
        }

        if (strcmp(trimmedInput, "h")    == 0 ||
            strcmp(trimmedInput, "help") == 0) {
            printHelpMessage();
            printf("\n");
            continue;
        }

        CalcError errorCode = evaluateExpression(trimmedInput,
                                                 &calculationResult);
        switch (errorCode) {
            case CALC_OK:
                printf(COLOR_INFO "  %s\n" COLOR_RESET, trimmedInput);
                printFormattedResult(calculationResult);
                break;
            case CALC_ERR_DIV_ZERO:
                printf(COLOR_ERROR "  錯誤：除數不能為零！\n" COLOR_RESET);
                break;
            case CALC_ERR_UNMATCHED:
                printf(COLOR_ERROR "  錯誤：括號不對稱！\n" COLOR_RESET);
                break;
            case CALC_ERR_SYNTAX:
            default:
                printf(COLOR_ERROR
                    "  語法錯誤！範例：\n"
                    "    2 + 3 * 4\n"
                    "    (1 + 2) ^ 3\n"
                    "    -5.5 * 2 + 10 / 4\n"
                    COLOR_RESET);
                break;
        }

        printf("\n");
    }

    return 0;
}
