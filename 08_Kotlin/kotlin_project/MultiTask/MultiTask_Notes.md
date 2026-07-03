# Kotlin 多執行緒與 Coroutine 重點筆記

## 1. 多執行緒基礎

### 核心概念
- **執行緒（Thread）** 是程式執行的最小單位。
- 同一個程式中可同時啟動多個執行緒，讓不同工作**交錯執行**。
- Kotlin 可以直接使用 Java 的 `Thread` 類別來建立執行緒。
- 執行緒彼此是**併發/並行**執行，不保證輸出順序。

### 對照表

| 名稱 | 說明 |
|---|---|
| `Thread` | Java 的執行緒類別，Kotlin 可直接使用 |
| `start()` | 真正啟動新執行緒 |
| `run()` | 執行執行緒內容的方法；直接呼叫不會開新執行緒 |
| `sleep(ms)` | 讓目前執行緒暫停指定毫秒數 |

### 最小可執行範例
```kotlin
fun main() {
    val t1 = Thread {
        println("Hello from thread")
    }
    t1.start()

    println("Hello from main")
}
```

### 常見誤區 / 注意事項
- **`run()` vs `start()`**：`run()` 是一般函式呼叫；`start()` 才會啟動新執行緒。
- 執行緒輸出順序**不一定固定**，不要假設每次都同樣排列。
- `sleep()` 只會暫停**目前呼叫它的那個執行緒**。

---

## 2. 繼承 `Thread` 並覆寫 `run()`

### 核心概念
- 可以透過**繼承 `Thread` 類別**來建立自訂執行緒。
- 必須覆寫 `run()`，把要執行的工作寫在裡面。
- 啟動時使用 `start()`，才會在新執行緒中執行 `run()`。

### 對照表

| 寫法 | 作用 |
|---|---|
| `class MyThread : Thread()` | 建立自訂執行緒類別 |
| `override fun run()` | 定義執行緒要執行的內容 |
| `super.run()` | 呼叫父類別的 `run()`，本例中通常可省略 |

### 最小可執行範例
```kotlin
class MyThread : Thread() {
    override fun run() {
        println("Thread start")
        for (i in 1..3) {
            println("Run $i")
            sleep(100)
        }
        println("Thread end")
    }
}

fun main() {
    MyThread().start()
}
```

### 常見誤區 / 注意事項
- **不要只呼叫 `run()`**，那不會開新執行緒。
- `super.run()` 在很多自訂情況下**可省略**，因為你已經自己定義工作內容。
- 執行緒類別通常是用來封裝**一段獨立工作流程**。

---

## 3. 建立執行緒的三種寫法

### 核心概念
- 這份程式碼示範了三種建立執行緒的方法：
  1. `Thread { ... }`
  2. `Thread({ ... })`
  3. `Thread({ ... }).start()`
- 它們本質上都是把要執行的工作交給 `Thread`。
- 差別主要在**語法形式**與**是否保留執行緒物件**。

### 對照表

| 寫法 | 特點 | 是否保留物件 |
|---|---|---|
| `Thread { taskFun() }` | 最簡潔 | 是 |
| `Thread({ ... })` | 舊式/較明確寫法 | 是 |
| `Thread({ ... }).start()` | 建立後立刻啟動 | 否（不保留變數） |

### 最小可執行範例
```kotlin
fun taskFun() {
    for (i in 1..3) {
        println("${Char(i + 64)}")
        Thread.sleep(200)
    }
}

fun main() {
    val thd1 = Thread { taskFun() }
    thd1.start()

    val thd2 = Thread({
        for (i in 1..3) {
            println("${Char(i + 48)}")
            Thread.sleep(150)
        }
    })
    thd2.start()

    Thread({
        for (i in 1..3) {
            println("${Char(i + 96)}")
            Thread.sleep(100)
        }
    }).start()
}
```

### 常見誤區 / 注意事項
- `Thread { ... }` 是**傳入執行內容**，不是直接執行。
- 若寫成 `Thread({ ... }).start()`，**無法再使用變數操作該執行緒**。
- 輸出可能交錯，屬於正常現象。

---

## 4. 執行緒優先權與暫停

### 核心概念
- `priority` 可以設定執行緒優先權，但**不保證一定照順序執行**。
- `Thread.MAX_PRIORITY` 是最高優先權。
- `Thread.sleep()` 常用來模擬耗時工作或讓輸出更容易看出交錯效果。

### 對照表

| API / 屬性 | 作用 |
|---|---|
| `priority` | 設定執行緒優先權 |
| `Thread.MAX_PRIORITY` | 最高優先權常數 |
| `Thread.sleep(300)` | 暫停目前執行緒 300 毫秒 |

### 最小可執行範例
```kotlin
fun main() {
    val thd = Thread {
        for (i in 1..5) {
            println("Worker $i")
            Thread.sleep(100)
        }
    }

    thd.priority = Thread.MAX_PRIORITY
    thd.start()
}
```

### 常見誤區 / 注意事項
- **優先權不是保證**，只能當作執行提示，不能依賴它控制絕對順序。
- `sleep()` 不會停止整個程式，只會暫停**目前那個執行緒**。
- 多執行緒輸出順序受排程影響，可能每次執行都不同。

---

## 5. 例題：三個執行緒同時輸出字母、數字與小寫字母

### 題目背景
設計一個程式，同時啟動三個執行緒：
1. 第一個執行緒印出 `A~E`
2. 第二個執行緒印出 `1~5`
3. 第三個執行緒印出 `a~e`

每個執行緒都加入不同的暫停時間，觀察輸出交錯情況。

### 完整程式碼
```kotlin
import kotlin.concurrent.thread

fun taskFun() {
    for (i in 1..5) {
        println("${Char(i + 64)}")
        Thread.sleep(500)
    }
}

/* 繼承 Thread 的類別
 * 有固定結構，要去 override run()
 */
class MyThread : Thread() {
    override fun run() {
        super.run()
        println("Thread start.")
        for (i in 10..15) {
            println("Running $i")
            sleep(100)
        }
        println("Thread end")
    }
}

fun main() {
    MyThread().start()

    // 寫法1
    val thd1 = Thread { taskFun() }
    thd1.start()

    // 寫法2
    var thd2 = Thread({
        for (i in 1..5) {
            println("${Char(i + 0x30)}")
            Thread.sleep(300)
        }
    })
    thd2.priority = Thread.MAX_PRIORITY
    thd2.start()

    // 寫法3
    var thd3 = Thread({
        for (i in 1..5) {
            println("${Char(i + 0x61)}")
            Thread.sleep(200)
        }
    }).start()
}
```

### 執行流程說明
1. `main()` 先啟動 `MyThread()`。
2. `MyThread` 進入 `run()`，印出 `Thread start.`，再印出 `Running 10 ~ Running 15`。
3. `thd1` 執行 `taskFun()`，輸出 `A ~ E`，每次停 500ms。
4. `thd2` 輸出 `1 ~ 5`，每次停 300ms，並設定為最高優先權。
5. `thd3` 直接建立並啟動，輸出 `a ~ e`，每次停 200ms。
6. 因為有多個執行緒同時運作，畫面上的輸出順序會交錯。

### 預期輸出
> 下面只是**可能的**輸出順序之一，實際順序每次可能不同。

```text
Thread start.
Running 10
A
1
a
Running 11
Running 12
b
2
...
Thread end
```

### 核心語法對照表

| 語法 | 作用 |
|---|---|
| `Thread { ... }` | 建立執行緒並指定執行內容 |
| `start()` | 開始執行執行緒 |
| `override fun run()` | 自訂執行緒執行邏輯 |
| `Thread.sleep(ms)` | 暫停目前執行緒 |
| `priority` | 設定執行緒優先權 |
| `Thread.MAX_PRIORITY` | 最高優先權值 |
| `Char(i + 64)` | 將數字轉成對應字元，例如 65 -> `A` |

### 常見誤區 / 注意事項
- `var thd3 = Thread({ ... }).start()` 之後，`thd3` 會是 `Unit`，**不是 Thread 物件**。
- `Char(i + 64)` 是利用 ASCII 編碼把數字轉成字元。
- `0x30`、`0x61` 分別是數字 `0` 與小寫 `a` 的 ASCII 起點。
- `import kotlin.concurrent.thread` 在這份程式中**沒有實際使用**，屬於可省略的匯入。

---

## 6. 容易混淆的觀念（Thread 篇）

### 核心概念
- **`start()` vs `run()`**：`start()` 會開新執行緒；`run()` 只是普通方法呼叫。
- **優先權 vs 排程結果**：`priority` 只是提示，不代表一定先執行。
- **建立物件 vs 立刻啟動**：`Thread { ... }` 是建立；`.start()` 才是真正執行。

### 對照一句話
- **值比較 vs 參考比較**：若之後遇到字串或物件比較，`==` 通常比內容，`===` 比的是是否同一個物件。

### 常見誤區 / 注意事項
- 不要把 `start()` 當成可省略的附屬語法。
- 不要以為 `priority` 能精準控制誰先印出來。
- 多執行緒結果本來就可能不固定，這是正常現象。

---

## 7. Coroutine 啟動方式：Lambda vs 具名 suspend 函式

> 對照範例：`MutiTask_2.kt`

### 核心概念
- **動機**：`Thread` 太「重」（每條約需數百 KB 記憶體、建立/切換要透過作業系統），如果要同時處理成百上千個工作（例如同時更新多個 UI 元件、發出多個網路請求），開等量的 `Thread` 會拖垮效能。Coroutine 讓少數幾條 thread 就能「輪流」處理大量工作，因為它在等待時（如 `delay`、網路 I/O）會把 thread 讓出去，而不是像 `Thread.sleep()` 一樣霸占。
- `CoroutineScope(Dispatchers.Default)` 建立一個協程作用域，`Dispatchers.Default` 是適合 CPU 密集運算的執行緒池。
- `scope.launch { ... }` 裡的 lambda **本身就是 suspend 環境**，可以直接寫一般程式碼，也可以呼叫 `suspend fun`。
- `launch { sFun() }` 是呼叫**具名的 suspend 函式**，效果和寫在 lambda 裡是一樣的，只是把邏輯抽出去方便重用/測試。
- **實務應用**：Android 開發中，常把「發網路請求」「讀資料庫」封裝成 `suspend fun`（例如 Retrofit 的 API 介面方法），在 `ViewModel` 的 `viewModelScope.launch { }` 裡呼叫，畫面不會卡住。

### 對照表

| 寫法 | 說明 |
|---|---|
| `scope.launch { 一般程式碼 }` | lambda 本身是 suspend 環境，直接寫邏輯 |
| `scope.launch { sFun() }` | 呼叫外部具名的 `suspend fun` |
| `suspend fun sFun()` | 標記為可暫停函式，只能在 coroutine 或另一個 suspend fun 中呼叫 |
| `fun Fun2()`（一般函式） | 沒有暫停能力，若內含耗時操作會直接卡住呼叫它的 thread |
| `repeat(n) { ... }` | Kotlin 標準函式，重複執行 n 次 |

### 最小可執行範例
```kotlin
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch

suspend fun sFun() {
    for (i in 100..102) {
        println(i)
        delay(200)   // 正確：使用 delay 而不是 Thread.sleep
    }
}

fun main() {
    val scope = CoroutineScope(Dispatchers.Default)
    scope.launch { sFun() }
    Thread.sleep(1000) // 讓 main thread 別太早結束
}
```

### 常見誤區 / 注意事項
- **`MutiTask_2.kt` 中的 `sFun()` 雖然標記了 `suspend`，但函式內部用的是 `Thread.sleep(500)` 而不是 `delay(500)`**。這是典型的誤用：宣告成 `suspend fun` 不代表內部就自動變成非阻塞，`Thread.sleep()` 依然會把該 coroutine 所在的 thread 整條卡住 500 毫秒，讓同一個 `Dispatchers.Default` thread pool 裡的其他 coroutine 沒辦法用這條 thread。正確寫法應該把 `Thread.sleep(500)` 換成 `delay(500)`。
- 若換成呼叫 `Fun2()`（一般 `fun`，非 suspend）：`launch { Fun2() }` **語法上合法**，因為 lambda 本身可以放一般程式碼；但因為 `Fun2()` 內部是同步阻塞的迴圈（`Thread.sleep`），coroutine 在執行它的期間**完全沒有暫停點可以讓出 thread**，等於這個 coroutine 把它借到的 thread 整個占用到 `Fun2()` 跑完為止，失去了 coroutine 協作式排程的意義。
- `main()` 裡用兩段 `for` 迴圈搭配 `Thread.sleep()` 只是土法煉鋼地讓 main thread 別提早結束，觀察 coroutine 的輸出交錯——**這不是正式寫法**。
- **實務上的替代方案**：與其用 `Thread.sleep()` 卡住 main thread 硬等，業界更常見的做法是：
  1. 保留 `Job` 物件並呼叫 `job.join()`（一個 suspend 函式，等待該 coroutine 結束），或
  2. 把整個 `main()` 包在 `runBlocking { }` 裡，讓 coroutine 執行完才讓程式結束（詳見第 9 章）。
     這樣才不會用「猜時間」的方式賭 coroutine 何時做完。
- Kotlin coroutine 的 `Dispatchers.Default` 執行緒池預設**不是 daemon thread**，所以就算 `main()` 函式本體跑完，只要背景 coroutine 還沒結束，JVM 通常還是會繼續等它們跑完才真正關閉程式（這點和一般 Java `Thread` 的行為不完全一樣，別搞混）。

---

## 8. Job 與 SupervisorJob：例外傳播範圍

> 對照範例：`MultiTask_3.kt`（第一、二段）

### 核心概念
- **動機**：多個 coroutine 常常是「同一組任務」，但你會希望「一個失敗，其他要不要也跟著失敗？」這個問題沒有標準答案，取決於任務之間是否互相依賴，所以 Kotlin 提供兩種 Job 策略讓你選。
- `CoroutineScope(Dispatchers.Default + Job())`：用一般 `Job()` 當作 scope 的父工作。**只要子 coroutine 中有一個丟出未捕捉的例外，這個例外會往上取消整個父 Job，連帶取消所有兄弟 coroutine**（即使它們還沒執行完）。
- `CoroutineScope(SupervisorJob())`：用 `SupervisorJob()` 取代 `Job()`。**子 coroutine 之間互相獨立，一個失敗不會影響其他兄弟**，適合「多個彼此無關的任務」情境。
- **實務應用**：例如一個畫面同時要抓「使用者資料」和「推薦清單」兩個 API，兩者互不相關——用 `SupervisorJob`，某個 API 失敗不該讓另一個也被取消。但如果是「一筆訂單裡的多個子步驟必須全部成功」，用一般 `Job()` 讓一個失敗就整組取消，反而才是對的行為。

### 對照表

| 寫法 | 一個子任務失敗時的行為 | 適用情境 |
|---|---|---|
| `CoroutineScope(Dispatchers.Default + Job())` | 取消整個 scope 下所有 coroutine | 任務彼此依賴、要嘛全成功要嘛全失敗 |
| `CoroutineScope(SupervisorJob())` | 只有失敗的那個 coroutine 受影響，其他繼續跑 | 任務彼此獨立，互不影響 |
| `error("...")` | 拋出 `IllegalStateException`，模擬失敗情境 | 測試錯誤傳播用 |

### 最小可執行範例
```kotlin
import kotlinx.coroutines.*

fun main() {
    val scope = CoroutineScope(Dispatchers.Default + Job())
    scope.launch {
        delay(100)
        error("job1 fail")   // 這會連帶取消下面的 job2
    }
    scope.launch {
        delay(200)
        println("job2 is ok")   // 可能永遠不會印出
    }
    Thread.sleep(1000)

    val scope1 = CoroutineScope(SupervisorJob())
    scope1.launch {
        delay(100)
        error("job3 fail")   // 只有自己失敗
    }
    scope1.launch {
        delay(200)
        println("job4 is ok")   // 仍然會印出
    }
    Thread.sleep(1000)
}
```

### 常見誤區 / 注意事項
- 不要以為 `Job()` 和 `SupervisorJob()` 只是命名不同——**錯誤傳播的範圍完全不同**，選錯會讓原本該獨立的任務被莫名取消，或該一起失敗的任務卻各跑各的。
- `error(msg)` 是 Kotlin 標準函式，等同於 `throw IllegalStateException(msg)`，常用來在範例中「模擬」一個會失敗的任務。
- **實務上的替代方案**：正式專案中通常不會讓例外直接讓程式印出堆疊訊息了事，而是搭配 `CoroutineExceptionHandler` 統一攔截、記錄 log 或顯示錯誤訊息給使用者，而不是單純依賴 `Job` / `SupervisorJob` 的取消行為。

---

## 9. `async` / `await` 與 `runBlocking`：取得非同步結果並讓主執行緒等待

> 對照範例：`MultiTask_3.kt`（第三段）

### 核心概念
- **動機**：`launch` 回傳 `Job`，你拿不到「執行結果」，只知道它跑完了沒有；但很多時候你需要的是**回傳值**（例如兩個 API 各自回傳一筆資料，最後要合併使用）。`async` 就是為了這個而生。
- `scope.async { ... }` 會回傳 `Deferred<T>`（`Job` 的子型別），內部程式碼跑完後的**回傳值**可以用 `.await()`（一個 suspend 函式）取得。
- `value1.await()` 和 `value2.await()` 如果分開寫成兩行依序呼叫，兩個 `async` 其實**已經同時在背景平行執行**了（因為 `async` 呼叫當下就啟動），`await()` 只是「等它做完、把結果拿出來」，不是重新觸發執行。
- `runBlocking { ... }` 會**阻塞呼叫它的 thread**（本例中是 main thread），直到裡面的 coroutine 全部執行完畢才繼續往下走。常用在 `main()` 函式或單元測試，讓「非同步的世界」和「同步的 main 函式」銜接起來。
- **實務應用**：`async`/`await` 常見於「同時發出多個獨立網路請求，全部完成後再統一處理」的情境，例如同時抓取商品資訊與庫存數量；`runBlocking` 則常見於 `main()` 進入點或 JUnit 測試（`runTest`/`runBlocking` 讓測試函式可以呼叫 suspend 函式）。

### 對照表

| API | 回傳型別 | 用途 |
|---|---|---|
| `launch { }` | `Job` | 執行一段工作，不需要回傳值 |
| `async { }` | `Deferred<T>` | 執行一段工作，之後用 `.await()` 取得回傳值 |
| `.await()` | `T` | suspend 函式，等待並取得 `async` 的結果 |
| `runBlocking { }` | 一般函式回傳值 | 阻塞目前 thread，等內部 coroutine 全部跑完 |

### 最小可執行範例
```kotlin
import kotlinx.coroutines.*

fun main() = runBlocking {
    val scope = CoroutineScope(SupervisorJob())
    val value1 = scope.async {
        delay(100)
        100
    }
    val value2 = scope.async {
        delay(200)
        200
    }
    // 兩個 async 已經平行在跑，這裡只是依序取值
    println("value1=${value1.await()}, value2=${value2.await()}")
}
```

### 常見誤區 / 注意事項
- **`launch` vs `async` 選錯**：不需要回傳值卻用 `async` 會讓程式碼多一層不必要的 `Deferred`；需要回傳值卻用 `launch` 則根本拿不到結果。一句話：**要結果用 `async`，不要結果用 `launch`。**
- `runBlocking` 會**真的卡住呼叫的 thread**，如果誤用在 Android 的 UI thread 上，效果等同於 `Thread.sleep()`，畫面會凍結——`runBlocking` 主要用在 `main()` 進入點或測試程式，正式的 Android/後端程式碼中很少直接使用。
- `MultiTask_3.kt` 在 `runBlocking` 之後又寫了一次 `Thread.sleep(1000)`——因為 `runBlocking` 本身就已經等待內部 coroutine 做完才會往下執行，這裡的 `Thread.sleep(1000)` 其實是多餘的，只是延長 main 函式壽命的保險寫法，不是必要語法。
- **實務上的替代方案**：如果任務不是「一次性」，而是「持續有新資料進來」（例如即時股價、聊天訊息、感測器數值），`Flow`（`SharedFlow` / `StateFlow`）通常比反覆呼叫 `launch`/`async` 更適合，因為 `Flow` 對取消、背壓（backpressure）、多次收集有更完整的支援。

---

## 10. 例題：Job 錯誤傳播、SupervisorJob 隔離與 async 取值的完整流程

### 題目背景
設計一個程式，展示三種 coroutine 進階行為：
1. 用一般 `Job()` 的 scope：其中一個 coroutine 失敗，觀察是否影響另一個。
2. 用 `SupervisorJob()` 的 scope：其中一個 coroutine 失敗，觀察另一個是否仍正常執行。
3. 用 `async` 同時取得兩個工作的回傳值，並用 `runBlocking` 讓 main thread 等待完成。

### 完整程式碼
```kotlin
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.Job
import kotlinx.coroutines.SupervisorJob
import kotlinx.coroutines.async
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking

fun main() {

    var scope = CoroutineScope(Dispatchers.Default + Job())
    /*只要有一個error 另一個就無法執行*/
    scope.launch {
        delay(100)
        println("Job 1")
        error("job 1 fail")
    }
    scope.launch {
        delay(200)
        println("job2 is ok")
    }
    Thread.sleep(1000)
    println("waiting 1")
    println()

    /*supervisorJob 協同程式獨立，一個發生error 另一個還是可以執行*/
    var scope1 = CoroutineScope(SupervisorJob())
    scope1.launch {
        delay(100)
        println("Job 3")
        error("job 1 fail")
    }
    scope1.launch {
        delay(200)
        println("job4 is ok")
    }
    Thread.sleep(1000)
    println("waiting 2")
    println()

    /*runBlock 可以讓main thread 等block 做完在結束*/
    runBlocking {
        val value1 = scope1.async {
            delay(100)
            println("async job 1")
            100
        }
        val value2 = scope1.async {
            delay(200)
            println("async job 2")
            100
        }
        //await 會去取得數值
        println("value1= ${value1.await()}, value2 =${value2.await()}")
        println()
    }
    Thread.sleep(1000)
    println("waiting 3")
}
```

### 執行流程說明
1. 第一段用 `Job()`：`Job 1` 印出後立刻 `error(...)`，這個未捕捉例外會取消整個 `scope`，所以 `job2 is ok` **極可能不會被印出**。
2. `Thread.sleep(1000)` 讓 main thread 等待，確保上面的 coroutine 有機會執行完（或被取消）。
3. 第二段改用 `SupervisorJob()`：`Job 3` 印出後 `error(...)`，但因為是 SupervisorJob，`job4 is ok` **仍然會照常印出**，兩者互不影響。
4. 第三段用 `runBlocking` 包住兩個 `async`：`value1`、`value2` 幾乎同時啟動並平行倒數 delay，`await()` 依序取值後印出結果，`runBlocking` 會等這整段跑完才讓 `main()` 繼續往下。
5. 最後的 `Thread.sleep(1000)` 是保險寫法，此時 `runBlocking` 內容其實早已跑完。

### 預期輸出
> 下面只是**可能的**輸出順序之一，`job1`/`job3` 何時真正被印出可能因排程而略有差異。

```text
Job 1
waiting 1

Job 3
job4 is ok
waiting 2

async job 1
async job 2
value1= 100, value2 =100

waiting 3
```

### 核心語法對照表

| 語法 | 作用 |
|---|---|
| `CoroutineScope(Dispatchers.Default + Job())` | 建立一般 Job 作用域，子任務失敗會互相牽連 |
| `CoroutineScope(SupervisorJob())` | 建立獨立 Job 作用域，子任務失敗互不影響 |
| `scope.launch { }` | 啟動一個不需要回傳值的 coroutine |
| `scope.async { }` | 啟動一個需要回傳值的 coroutine，回傳 `Deferred<T>` |
| `.await()` | 取得 `async` 的執行結果，會 suspend 直到結果就緒 |
| `runBlocking { }` | 阻塞呼叫的 thread，等內部所有 coroutine 完成 |
| `error(msg)` | 拋出 `IllegalStateException`，模擬失敗 |

### 常見誤區 / 注意事項
- 這份程式全程用 `Thread.sleep()` 讓 main thread 等待 coroutine，是教學上「方便觀察輸出」的權宜寫法，正式專案應優先用 `job.join()` 或整個包在 `runBlocking { }` 裡。
- `error(...)` 丟出的例外若沒有用 `try/catch` 或 `CoroutineExceptionHandler` 攔截，在一般 `Job()` 底下會讓整個 scope 進入取消狀態，之後對這個 `scope` 再呼叫 `launch` 通常也不會執行。
- `value1.await()` 和 `value2.await()` 依序寫在同一行字串模板中，並不代表 `value2` 是等 `value1` 完全結束才開始執行——兩者的 `async {}` 在呼叫當下就已經同時啟動。

---

## 11. 容易混淆的觀念（Coroutine 篇）

### 核心概念
- **`delay()` vs `Thread.sleep()`**：`delay()` 只暫停「這個 coroutine」，會把 thread 讓出去給別的 coroutine 用；`Thread.sleep()` 是把「整條 thread」卡死，該 thread 上其他排隊的 coroutine 全部要等。誤用 `Thread.sleep()` 取代 `delay()`（如 `MutiTask_2.kt` 的 `sFun()`）會讓 coroutine 失去輕量、協作式排程的優勢。
- **`launch` vs `async`**：`launch` 回傳 `Job`，只關心「做完了沒」；`async` 回傳 `Deferred<T>`，關心「做完後的結果是什麼」。
- **`Job()` vs `SupervisorJob()`**：一句話——`Job()` 是「一人生病，全班隔離」；`SupervisorJob()` 是「一人生病，其他人正常上課」。
- **`suspend fun` 不等於「自動非阻塞」**：標記 `suspend` 只表示這個函式**可以**包含暫停點（例如呼叫 `delay()`），但函式內部若寫的是 `Thread.sleep()` 這種阻塞呼叫，該函式依然會卡住執行它的 thread。
- **一般 `fun` vs `suspend fun`**：`launch{}` 內可以呼叫一般 `fun`，語法上不會出錯，但一般 `fun` 沒有暫停能力，若其中有耗時操作，coroutine 會整個被卡住，等同於白白浪費了開 coroutine 的意義。

### 常見誤區 / 注意事項
- 不要看到 `suspend` 關鍵字就以為「這個函式一定不會卡住 thread」，要看函式**內部**用的是 `delay()` 還是 `Thread.sleep()`。
- 不要把 `runBlocking` 當成一般寫法到處用——它是刻意「把非同步接回同步世界」的橋接工具，用在不該用的地方（如 UI thread）會讓畫面凍結。
- `Job()` 與 `SupervisorJob()` 選錯，最常見的症狀就是「明明兩個任務互不相關，卻因為其中一個失敗，另一個莫名其妙沒有執行」。

---

## 快速總結

```text
Kotlin 多執行緒與 Coroutine
├─ Thread（傳統執行緒）
│  ├─ 可直接使用 Java 的 Thread
│  ├─ start()：真正啟動新執行緒
│  ├─ run()：執行內容，不等於開新執行緒
│  ├─ 建立方式：Thread { }／Thread({ })／Thread({ }).start()
│  ├─ 繼承 Thread + override run()
│  └─ priority：只是提示，不保證順序
│
├─ Coroutine（協程，跑在 Thread 之上，不是 Thread 的一種）
│  ├─ 為什麼需要：Thread 太重，Coroutine 用少量 thread 處理大量併發
│  ├─ CoroutineScope(Dispatchers.Default) + launch { }
│  │   ├─ lambda 本身是 suspend 環境，可直接寫邏輯或呼叫 suspend fun
│  │   └─ 呼叫一般 fun（非 suspend）：語法合法，但耗時操作會卡住 thread
│  ├─ suspend fun
│  │   ├─ 標記可暫停，只能在 coroutine / 另一個 suspend fun 中呼叫
│  │   └─ 內部仍需用 delay() 而非 Thread.sleep()，否則等於白標記
│  ├─ delay() vs Thread.sleep()
│  │   ├─ delay()：只暫停該 coroutine，讓出 thread 給別人用
│  │   └─ Thread.sleep()：卡住整條 thread，其他 coroutine 要排隊
│  ├─ Job() vs SupervisorJob()
│  │   ├─ Job()：一個子任務失敗，牽連取消所有兄弟任務
│  │   └─ SupervisorJob()：子任務彼此獨立，互不影響
│  ├─ launch { } vs async { }
│  │   ├─ launch → Job，不需要回傳值
│  │   └─ async → Deferred<T>，用 .await() 取得回傳值
│  └─ runBlocking { }
│      └─ 阻塞呼叫的 thread，等內部 coroutine 全部跑完，常用於 main() / 測試
│
└─ 容易混淆一句話
   ├─ 值比較 vs 參考比較：== 比內容，=== 比是否同一物件
   ├─ delay() 是「禮貌讓出資源」，Thread.sleep() 是「霸占資源硬躺著」
   └─ Job() 是「一人生病全班隔離」，SupervisorJob() 是「一人生病其他人照常上課」
```
