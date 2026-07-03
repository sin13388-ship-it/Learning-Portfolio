# Kotlin object / companion object 重點筆記

> 對應範例檔案：`Object_1.kt`、`CompanionObject.kt`

## 1. object：單例（Singleton）宣告

**動機說明**：有些東西邏輯上「全域只需要一份」（例如一個 Logger、一組共用設定），如果用一般 `class` 還要自己控制「只能建立一個實體」，很容易出錯。Kotlin 的 `object` 關鍵字讓你直接宣告一個「天生只有一個實體」的物件，語言層級保證單例，不用自己寫 double-check locking 之類的邏輯。

**核心概念**
- `object Logger { ... }`：宣告即單例，不需要（也不能）用 `Logger()` 建立實體，直接用 `Logger.log(...)` 呼叫。
- `object` 內的 `init` 區塊**只會在第一次被使用時執行一次**，之後重複呼叫方法不會重新初始化。
- `object` 可以有 `var`/`val` 屬性當作「全域共享狀態」，例如 `Logger.count` 會隨每次呼叫累加，且所有呼叫端共用同一份數值。
- `object` 也可以用來實作介面（`object : LogMag { ... }`），或搭配 `object : 父類別(...) { override ... }` 做「匿名物件表達式」，一次性複寫某個開放類別的行為。

**對照表：object 用法**

| 用法 | 語法 | 用途 |
|---|---|---|
| 具名單例 | `object Logger { ... }` | 整個 App 共用一份的工具類/管理類 |
| 匿名物件（實作介面） | `object : LogMag { override fun log(...) {...} }` | 只需要一次性的介面實作，不想額外開 class |
| 匿名物件（繼承並覆寫） | `object : Car("Toyota") { override fun basicInfo(...) {...} }` | 針對某個 open class，臨時客製化一份實作 |

**最小可執行範例**
```kotlin
object Logger {
    var count: Int
    init {
        count = 0
        println("count= $count, Welcome to Logger")
    }
    fun log(message: String) {
        println("Log: $message")
        count++
    }
}

fun main() {
    println("count= ${Logger.logCount()}") // 第一次使用才會觸發 init
    Logger.log("test")                     // count 全域累加，所有呼叫共用同一份
}
```

**常見誤區 / 注意事項**
- `object` 裡的 `set` 自訂邏輯（如範例 `randNumber.num` 的 `set(value){ field = if(value<1) 1 else value }`）是**屬性層級**的驗證，可以防止外部設定不合法的值（例如長度小於 1）。
- 匿名物件表達式 `object : Car("Toyota") {...}` 產生的型別**不是** `Car`，而是一個匿名子類別，但因為賦值給 `var myCar: Car`，只能透過 `Car` 已知的成員存取，無法呼叫匿名類別新增的成員。
- `object` 是單例，所有呼叫端共用同一份狀態，如果誤以為每次呼叫都是「獨立乾淨的實例」（像一般 class），容易造成資料互相污染的 bug。

**實務應用**：App 的全域 `Logger`、`Config` 管理、資料庫連線管理員、或是 Android 的 `object EventBus` 常見都用這種單例寫法；而「匿名物件實作介面」則常見於臨時的 `Click` callback 或測試替身（stub）。

**實務上的替代方案**：如果這個「全域唯一」的物件其實需要延遲初始化、依賴注入、或是要方便做單元測試 mock，業界更常改用 **依賴注入框架（如 Hilt/Koin）管理的單例**，而不是語言內建的 `object`，因為 `object` 一旦被使用就無法替換成假的實作，會讓單元測試變困難。

---

## 2. companion object：類別層級的共用成員（類似 static）

**動機說明**：有時候我們需要「不透過建立實體，就能直接呼叫類別本身的方法/常數」（例如工廠方法 `User.create(...)`，或是取得一組隨機亂數 `RandomNumber.getNumbers(...)`）。Kotlin 沒有 Java 的 `static` 關鍵字，而是用 `companion object` 達到相同效果。

**核心概念**
- `companion object { ... }` 寫在 class 內部，裡面的方法/屬性可以直接用「類別名稱」呼叫，例如 `RandomNumber.getNumbers(5)`，不需要先 `RandomNumber()`。
- `const val TAG = "myTag"`：`companion object` 裡常放編譯期常數，效果類似 Java 的 `public static final`。
- 常見設計模式：**工廠方法（Factory Method）**——`companion object` 提供一個 `create(...)` 或 `newInstance(...)` 方法，內部呼叫私有/主建構子並回傳設定好的物件，隱藏建立細節（如 `DetailFragment.newInstance(...)`）。

**對照表：object vs companion object**

| 特性 | `object` | `companion object` |
|---|---|---|
| 歸屬 | 獨立的單例，本身就是完整類別 | 依附在某個 class 內部 |
| 呼叫方式 | `ObjectName.method()` | `ClassName.method()` |
| 用途 | 全域共用的單例物件 | 類似 Java static，工廠方法、常數 |

**最小可執行範例**
```kotlin
class User(val name: String) {
    companion object {
        const val TAG = "myTag"
        fun create(name: String): User {
            return User(name)
        }
    }
    fun userInfo() = println("Tag = $TAG, name= $name")
}

fun main() {
    val user1 = User.create("John")  // 不用 new，直接透過類別呼叫
    user1.userInfo()
}
```

**常見誤區 / 注意事項**
- `companion object` 方法內部**仍然是呼叫一般建構子**（`User(name)`）建立實體，並不是單例，每次呼叫 `create()` 都會產生新的 `User` 物件——不要跟 `object` 單例搞混。
- 一個類別**最多只能有一個** `companion object`（可以不具名，也可以取名字，但同一個類別只能有一份）。
- `NewDice` 範例中，`val rolledValue get() = (1..6).shuffled().first()` 是**實體屬性**（每次建立物件才能取得），而 `companion object { fun randomValue() }` 則不需要建立實體即可呼叫，兩者呼叫方式不同，容易混淆。

**實務應用**：Android 開發中 `Fragment.newInstance(...)` 是官方推薦的工廠模式標準寫法（如範例 `DetailFragment`），用來確保 Fragment 建立時一定會正確設定好參數；後端專案中，`companion object` 也常用來放 `TAG`（logging 用）、常數設定值。

**實務上的替代方案**：如果「共用邏輯」跟某個特定類別完全無關，只是想放一些通用的工具方法（例如字串處理），業界更常用**頂層函式（top-level function）**直接寫在檔案裡，而不是硬塞進某個 class 的 `companion object`，因為頂層函式不需要透過類別名稱前綴，使用起來更直覺，也避免類別職責混雜。

---

## 3. 例題章節：亂數產生器（object 生成工具）

**題目背景**：使用 `object` 建立一個可設定長度、產生指定數量亂數的工具，體驗「單例」與「屬性 setter 驗證」的搭配使用。

**完整程式碼**
```kotlin
object randNumber {
    var num: Int = 1
        set(value) {
            field = if (value < 1) 1 else value
        }
    var id: Int
    init {
        id = 100
    }
    fun getNumber(): IntArray {
        var numbers = IntArray(num).apply {
            for (i in this.indices) {
                this[i] = Random.nextInt(1, 11)
            }
        }
        return numbers
    }
}

fun main() {
    randNumber.num = 5
    var numbers = randNumber.getNumber()
    numbers.forEach { print("$it, ") }
}
```

**執行流程說明**
1. `randNumber.num = 5`：呼叫自訂 `set`，因為 `5 >= 1`，所以 `field` 直接被設為 `5`。
2. `randNumber.getNumber()`：建立長度為 `num`（5）的 `IntArray`，用 `apply` 搭配迴圈把每個元素填入 `1~10` 的隨機整數。
3. `forEach` 印出所有產生的亂數。

**預期輸出（數值每次執行皆隨機，長度固定為 5）**
```
7, 3, 10, 1, 9, 
```

**核心語法對照表**

| 語法 | 說明 |
|---|---|
| `object randNumber { ... }` | 宣告單例物件 |
| `set(value) { field = ... }` | 自訂屬性的 setter，`field` 代表實際儲存值 |
| `IntArray(num).apply { ... }` | 建立指定長度陣列並用 `apply` 在同一個範圍內初始化每個元素 |
| `Random.nextInt(1, 11)` | 產生 `[1, 11)` 區間的隨機整數，也就是 1~10 |

---

## 快速總結

```
object 相關語法
├─ object（單例宣告）
│   ├─ 語言保證只有一個實體
│   ├─ init 只執行一次
│   └─ 可實作介面 / 繼承並覆寫 (匿名物件表達式)
├─ companion object（類別內的靜態成員）
│   ├─ 用「類別名稱」呼叫，不需要建立實體
│   ├─ 常見用途：const 常數、工廠方法 (create/newInstance)
│   └─ 一個類別最多一個 companion object
└─ 容易混淆點
    ├─ object 單例 vs companion object 工廠方法(仍會 new 出新物件)
    └─ 實體屬性 (需要建立物件) vs companion object 方法 (不需要建立物件)
```