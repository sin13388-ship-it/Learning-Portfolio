# Kotlin 多執行緒與 `Thread` 建立方式 重點筆記

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

## 6. 容易混淆的觀念

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

## 快速總結

```text
Kotlin 多執行緒
├─ Thread
│  ├─ 可直接使用 Java 的 Thread
│  ├─ start()：真正啟動新執行緒
│  └─ run()：執行內容，不等於開新執行緒
├─ 建立方式
│  ├─ Thread { ... }
│  ├─ Thread({ ... })
│  └─ Thread({ ... }).start()
├─ 自訂執行緒
│  ├─ 繼承 Thread
│  ├─ override run()
│  └─ 把工作寫在 run() 裡
├─ 執行控制
│  ├─ sleep(ms)：暫停目前執行緒
│  └─ priority：只是提示，不保證順序
└─ 字元輸出
   ├─ Char(i + 64) → A, B, C...
   ├─ Char(i + 0x30) → 1, 2, 3...
   └─ Char(i + 0x61) → a, b, c...
```

