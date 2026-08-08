# 文字型計算機
    給自己的C語言期末考
## 為何想寫?
- 一開始只是在課堂上學到個位數的四則運算，例如 5+2, 5-4, ...etc. 於是好奇如果是有括號或是次方的話要怎麼寫?
- 本來以為很簡單，看了AI的說明和示範後發現事情並不是這麼單純
- AI提供的範例碼把我從實體課程和數位課程學到的內容都用上了，所以我覺得很適合自己練習
## 相關知識應用
- Shunting Yard Algorithm : Infix, Postfix 是甚麼?
- Stack : 標配方法和檢查
- Data structure : (如何去設計一個結構來處理資料)，何謂資料描述、資料容器
- 格式化輸出 : 如何把console 的文字套色
- string.h :　常用的function
## 架構
很粗淺的先分成3個模組
### V1的架構
- [Main](./TextCalculator.c)
    - 格式化輸出
    - Shunting Yard
    - Infix -> Postfix
    - 計算結果
- [Token](./Token.c)
    - Tokenize
- [Stack](./Stack.c)
    - Action : Pop , Push, Peek , Initialize
    - Flag : isEmpty, isFull

##　如何執行？

- 沒有建makefile 檔案，main.c = TextCalculator.c，用vscode run
