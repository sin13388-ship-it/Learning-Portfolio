# Learning-Portfolio
職訓局IoT學習歷程

## 寫在前面
- 之前都是用Notion寫，之後會陸續把內容移轉過來
[數位筆記連結](https://www.notion.so/IoT-Learning-323fbfb24ec0800c8d35ddb46b4f26d6?source=copy_link)

- 前期的筆記會記錄的比較完整，後期的只會紀錄課程反思、自主學習和比較生疏的部分
- 訓練期間(26.3~26.9)，因為就業提前離訓，不會有完整的內容
- Android 的檔案太大，暫時只會放上layout跟 MainActivity的內容

## 各項目的日程
滾動式調整



## 課程內容

1. 數位邏輯系統(32小時)
   <details>  
   <summary>感想</summary>         
      只有4堂課，內容與高職上過的數位邏輯相同，所以沒有做什麼筆記。Arduino 實作好玩一點。
   </details>
   <details>   
   <summary>基本概念</summary> 

     - 基本的邏輯閘介紹
     - 布林代數的定理
     - C語言的邏輯運算指令與邏輯閘的關係
     - 數字系統介紹
     - 常用的組合邏輯電路和循序邏輯電路
     </details>
   <details>
   <summary>MCU的基本概念 (有筆記)</summary>
     
     - [MCU的基本架構及運作原理](./04_DigitalLogic/README.md#mcu的基本架構及運作原理)
     </details>
   <details>
     <summary>Arduino 實作模組 (有筆記)</summary>  

      - [LED 閃爍](./04_DigitalLogic/README.md/#led-閃爍)

   
     </details>
2. C程式語言(72小時)
   <details>
      <summary>感想</summary>

      C語言在我心目中就是像Minecraft 一樣的存在，只要你有想法，它可以實現任何事。課程有包含了C基本常用的內容，上課的範例簡單，沒有實際應用的例子是比較遺憾的地方。透過自主練習補強 [文字計算機](./13_Practical_Applications/FullTextCalculator/README.md)      
   </details>
   <details>
     <summary>Basic concept</summary>
     
     - 程式的基本架構 
     - 變數與常數
     - 程式的運算與邏輯
     - 程式控制流程
     - 陣列與迴圈
     - 指標與結構
     </details>   
3. Java程式語言(96小時) [Java](./03_Java/Java/Code/README.md)
   <details>
      <summary>感想</summary>

      前份工作有花時間自學C#，幾乎(?)跟C#很相似，算是藉Java複習C#。比較不熟的部分是lambda跟多執行緒，後期上kotlin的時候突然全部都打通了。此課程並沒有教到GUI且和C語言一樣只包含基本語法跟簡單範例，實際應用範例可以詢問AI，會較完整。 [自主學習](./03_Java/Java/Code/JavaAdditonal/application/MonitorHandler/src/main/java/com/monitorhandler/MonitorHandler.java)      
   </details>
   <details>
     <summary>基本語法</summary>
     
     - 資料型態
     - 流程控制
     - 陣列
     - 方法
     </details>
   <details>
     <summary>物件導向基礎</summary>
     
     - 物件與類別
     - 封裝、繼承
     - 方法覆寫與多型
     </details>
   <details>
     <summary>進階特性</summary>
     
     - 抽象類別與抽象方法
     - 匿名、例外處理、泛型
     </details>
4. Kotlin程式語言(80小時)[Kotlin](./08_Kotlin/README.md)
   <details>
     <summary>感想</summary>
     
      之前沒學過的程式語言，雖然跟Java一組，但我還是覺得差異有點大。這門課的課本沒有甚麼範例，需要使用AI補強內容，作用域函數在練習之後有比較熟練一點，但還是經常搞錯用法。是我花比較多心力的一門課。
   </details>
   <details>
     <summary>內容</summary>
     
   - 資料型態(List、Set、Map)
   - 條件運算式
   - 函數與各種函數類型
   - 物件與類別
   - 繼承
   - 介面與抽象類別
   - 泛型
   </details>
   
5. 單晶片微控制器(120小時)
   <details>
     <summary>感想</summary>
     
      我最喜歡的課程之一。為了去往自己想去的目標，當我看到課綱上有這門課後直接報名，很慶幸自己做了正確的決定，每次上課、每次複習都讓我覺得自己正在往目標邁進。以前沒看懂的中斷服務、UART、SPI、I2C...都獲得了解答。
   </details>
   <details>
     <summary>內容</summary>
     
   - 微控制器基礎概念
   - MCU開發環境安裝與操作
   - 組合語言I/O控制與C語言複習
   - ADC與類比比較器
   - 中斷與計時模組之應用
   - MCU操作模式與省電操作
   - LCD與LCM原理與程式設計
   - NEC IR解碼控制
   - 手機、MCU與藍芽結合運用
   </details>


6. Android手機程式設計(160小時)
   - Android Studio 開發系統操作與設定
   - Android人機界面設計
   - Intent、Dialog
   - Menu、ListView
   - Firebase實作
   - 手機各種sensor控制
7. Linux作業系統(56小時)
   - Linux系統安裝
   - 作業系統基本操作
   - 資料流重導向操作
   - 帳號管理及權限
   - 例行性工作排程
   - MySQL架設
8. 資料庫系統(MySQL)(72小時)
   - 管理工具安裝
   - 結合與合併查詢
   - 實體關係模型與資料庫正規化
   - 字元集與資料庫
   - 索引/子查詢
   - Views
   - Prepared Statements
9. 網頁程式設計(96小時)
   - HTML語法
   - CSS語法
   - JavaScript語法
10. Python/Django動態網頁設計(96小時)
   - Python程式語言
   - 平台建置
   - 建立Django專案
   - 建立Application應用程式
   - 視圖(view)與url
   - 視圖、模版與Template語言
   - 以GET及POST傳送資料
   - Django與資料庫連結
   - 資料庫控制CRUD(新增、刪除、查詢、修改)的應用
   - Cookies與Sessions
   - 專案製作
11. 單晶片ARM cortex控制實習(80小時)
   - 介紹ARM Cortex-M0 Structure
   - Keil MDK開發系統操作與設定
   - STM CubeMx系統操作及程式架構介紹
   - 介紹意法半導體(STMicroelectronics)和M0 MCU-ST32F072其週邊功能 GPIO
   - USART、Timer、PWM、EXTI、ADC
   - 使用STM開發板實作各種應用
12. AI應用(56小時)
   - 生成式AI
   - 機器學習模型
13. 綜合應用(104小時)
   - <details>
     <summary>Self-learning</summary>
     
     - 自學補充專題-文字計算機 [文字計算機] (https://github.com/sin13388-ship-it/FullTextCalculator.git)
     </details>
   - Sensor的操作
   - JSON格式
   - Restful API
   - MQTT
   - 專案製作
14. 專題製作(32小時)
   - 學員分組
   - 題目確認
   - 學員實作討論
   - 成果發表
