# Kotlin 泛型（Generics）重點筆記

> 適合對象：初學者到中階 ｜ 語言：Kotlin ｜ 主題：泛型函式與型別約束

---

## 1. 什麼是泛型（Generic）

### 核心概念

- **泛型** 讓函式或類別可以接受「任意型別」的參數，而不需要為每種型別各寫一個版本。
- 用 `<T>` 宣告型別參數，`T` 只是慣用名稱，可自訂（如 `T1`、`T2`、`E`）。
- 呼叫時，Kotlin 可從傳入的引數**自動推斷型別**，通常不需要手動指定。
- 泛型提高**程式碼重用性**，同時保有編譯期的型別安全。
- 型別參數只在宣告該函式/類別的範圍內有效。

### 對照表：一般函式 vs 泛型函式

| 比較項目 | 一般函式 | 泛型函式 |
|---|---|---|
| 參數型別 | 固定（如 `String`） | 任意（`T`） |
| 重用性 | 低（每種型別各寫） | 高（一份程式碼通用） |
| 型別安全 | ✅ 編譯期檢查 | ✅ 編譯期檢查 |
| 宣告語法 | `fun foo(x: String)` | `fun <T> foo(x: T)` |

### 最小可執行範例

```kotlin
fun <T> printItem(item: T) {
    println("Item : $item")
}

fun main() {
    printItem("Mary")   // T 推斷為 String
    printItem(100)      // T 推斷為 Int
    printItem(true)     // T 推斷為 Boolean
}
```

**預期輸出：**
```
Item : Mary
Item : 100
Item : true
```

### 常見誤區 / 注意事項

- ⚠️ `T` 在函式內部無法直接取得型別資訊（如 `T::class`），需要額外使用 `reified` 關鍵字（進階主題）。
- ⚠️ 型別參數 `<T>` 必須寫在 `fun` 關鍵字之後、函式名稱之前：`fun <T> 函式名`。

---

## 2. 多個型別參數

### 核心概念

- 一個函式可以宣告多個型別參數，以逗號分隔：`<T1, T2>`。
- 每個型別參數各自獨立，可以是完全不同的型別。
- 多型別參數讓函式能同時處理**異質**資料（如整數 + 字串）。

### 最小可執行範例

```kotlin
fun <T1, T2> myFun(p1: T1, p2: T2) {
    println("p1= $p1")
    println("p2= $p2")
    println()
}

fun main() {
    myFun(100, 200)       // T1=Int,    T2=Int
    myFun(100, "Mary")    // T1=Int,    T2=String
    myFun("Mary", "Bob")  // T1=String, T2=String
    myFun(false, 100)     // T1=Boolean,T2=Int
}
```

**預期輸出：**
```
p1= 100
p2= 200

p1= 100
p2= Mary

p1= Mary
p2= Bob

p1= false
p2= 100
```

### 常見誤區 / 注意事項

- ⚠️ 多個型別參數彼此**沒有關聯**，`T1` 和 `T2` 可以是任意型別，但不能互換使用。
- ⚠️ 若傳入的引數與宣告順序不符，Kotlin 不會自動重排，務必對齊位置。

---

## 3. 型別約束（Type Constraint）：`T: 上界`

### 核心概念

- 使用 `<T: 上界型別>` 限制 `T` 只能是指定型別或其子型別。
- **目的**：讓函式能呼叫該型別特有的方法，否則 `T` 只能使用 `Any` 的方法。
- `Comparable<T>` 是 Kotlin 內建介面，實作後可使用 `>` `<` `==` 比較大小。
- `Number` 是 Kotlin 數值型別的共同父類別，限制後可呼叫 `.toDouble()`、`.toInt()` 等轉換方法。
- 若傳入不符合約束的型別，**編譯期即報錯**，不會等到執行時。

### 對照表：常用型別約束

| 約束寫法 | 允許的型別 | 可用的方法/操作 |
|---|---|---|
| `<T: Comparable<T>>` | `Int`, `Double`, `String`, `Char`… | `>`, `<`, `==`, `compareTo()` |
| `<T: Number>` | `Int`, `Double`, `Float`, `Long`… | `.toDouble()`, `.toInt()`, `.toLong()` 等 |
| `<T: Any>` | 所有非 null 型別（預設） | `toString()`, `equals()`, `hashCode()` |

### 最小可執行範例

```kotlin
// 約束：T 必須可比較
fun <T: Comparable<T>> compare(t1: T, t2: T) {
    when {
        t1 > t2 -> println("$t1 > $t2")
        t1 < t2 -> println("$t1 < $t2")
        else    -> println("$t1 = $t2")
    }
}

fun main() {
    compare(50, 30)           // Int 比較
    compare("Mary", "John")   // String 字典序比較
    compare(12.45, 12.45)     // Double 比較
}
```

**預期輸出：**
```
50 > 30
Mary > John
12.45 = 12.45
```

### 常見誤區 / 注意事項

- ⚠️ `String` 的 `>` `<` 比較是**字典序（lexicographic）**，`"Mary" > "John"` 因為 `M` 的 Unicode 碼比 `J` 大。
- ⚠️ 沒有加 `Comparable` 約束時，直接用 `>` 比較兩個 `T` 會**編譯失敗**。

---

## 4. 數值型別約束與回傳值

### 核心概念

- 同時約束**多個型別參數**各有不同上界：`<T1: Number, T2: Number>`。
- `p1.toDouble()` — 將任意 `Number` 子型別轉為 `Double`，**這個方法讓不同數值型別得以統一計算**。
- `.plus(other)` — `Double` 的加法方法，等同於 `+` 運算子。
- 函式回傳型別明確宣告為 `Double`，確保呼叫端知道結果型別。
- 透過約束 `Number`，可以拒絕傳入 `String` 等非數值型別，在編譯期防止錯誤。

### 對照表：Number 子型別轉換方法

| 方法 | 說明 |
|---|---|
| `.toDouble()` | 轉換為 64 位元浮點數（`Double`） |
| `.toInt()` | 轉換為 32 位元整數（`Int`），**小數部分截斷** |
| `.toLong()` | 轉換為 64 位元整數（`Long`） |
| `.toFloat()` | 轉換為 32 位元浮點數（`Float`） |

### 最小可執行範例

```kotlin
fun <T1: Number, T2: Number> add(p1: T1, p2: T2): Double {
    val sum = p1.toDouble().plus(p2.toDouble())
    return sum
}

fun main() {
    println("sum= ${add(100, 32.4)}")       // Int + Double
    // println("sum= ${add("Mary", 32.4)}") // ❌ 編譯錯誤：String 不是 Number
}
```

**預期輸出：**
```
sum= 132.4
```

### 常見誤區 / 注意事項

- ⚠️ **值比較 vs 參考比較**：`==` 比較值（呼叫 `equals()`），`===` 比較記憶體參考，數值計算結果請用 `==`。
- ⚠️ `Int + Double` 在一般運算中 Kotlin 不允許直接相加，泛型搭配 `.toDouble()` 是一種解決方式。

### 進階：使用 `where` 連接多個泛型約束

- 當同一個型別參數需要同時滿足**多個條件**時，可以使用 `where` 來寫更清楚的約束。
- 語法格式：`fun <T> 函式名(...) where T: 條件1, T: 條件2`
- `where` 常用在約束較多、宣告太長時，讓程式更容易讀。
- 你提供的 `compare1()` 中，`T` 必須同時是 `Number`，又必須是 `Comparable<T>`。
- 這樣就能同時做到：**可比較大小**、**也符合數值型別**。

### 對照表：`<T: ...>` vs `where`

| 寫法 | 適用情況 | 範例 |
|---|---|---|
| `<T: Comparable<T>>` | 只有一個約束 | `fun <T: Comparable<T>> compare(...)` |
| `where T: Number, T: Comparable<T>` | 多個約束 | `fun <T> compare1(...) where T:Number, T:Comparable<T>` |

### 最小可執行範例

```kotlin
fun <T> compare1(t1: T, t2: T) where T: Number, T: Comparable<T> {
    when {
        t1 > t2 -> println("$t1 > $t2")
        t1 < t2 -> println("$t1 < $t2")
        else -> println("$t1 = $t2")
    }
}

fun main() {
    compare1(12, 56)
}
```

**預期輸出：**
```text
12 < 56
```

### 常見誤區 / 注意事項

- ⚠️ `where` 不是用來取代泛型，而是用來**補充多個限制條件**。
- ⚠️ `compare1(12, 56)` 會正常執行，但 `println(compare1(12,56))` 會另外印出 `kotlin.Unit`，因為 `compare1()` 的回傳型別是 `Unit`。
- ⚠️ 如果型別只符合其中一個條件，例如只有 `Number` 但不能比較大小，就不能通過編譯。

---

## 5. 例題章節：綜合泛型函式應用

### 題目背景

> 撰寫四個泛型函式，分別示範：
> 1. 單一型別參數印出任意項目
> 2. 雙型別參數印出兩個不同型別的值
> 3. 受 `Comparable` 約束的大小比較
> 4. 受 `Number` 約束的加法運算
> 5. 使用 `where` 連接多個泛型約束
>
> 並在 `main()` 中逐一呼叫，觀察輸出結果。

### 完整程式碼

```kotlin
// ① 單一型別參數：印出任意項目
fun <T> printItem(item: T) {
    println("Item : $item")
}

// ② 雙型別參數：印出兩個不同型別的值
fun <T1, T2> myFun(p1: T1, p2: T2) {
    println("p1= $p1")
    println("p2= $p2")
    println()
}

// ③ Comparable 約束：比較大小
fun <T: Comparable<T>> compare(t1: T, t2: T) {
    when {
        t1 > t2 -> println("$t1 > $t2")
        t1 < t2 -> println("$t1 < $t2")
        else    -> println("$t1 = $t2")
    }
}

// ④ Number 約束：任意數值相加，回傳 Double
fun <T1: Number, T2: Number> add(p1: T1, p2: T2): Double {
    return p1.toDouble().plus(p2.toDouble())
}

// ⑤ where：約束 T 同時是 Number 與 Comparable<T>
fun <T> compare1(t1: T, t2: T) where T: Number, T: Comparable<T> {
    when {
        t1 > t2 -> println("$t1 > $t2")
        t1 < t2 -> println("$t1 < $t2")
        else -> println("$t1 = $t2")
    }
}

fun main() {
    // 測試 add()
    println("sum= ${add(100, 32.4)}")
    // println("sum= ${add("Mary", 32.4)}") // ❌ 編譯錯誤

    // 測試 compare1()：同時要求 Number + Comparable
    compare1(12, 56)

    // 測試 compare()
    compare(50, 30)
    compare("Mary", "John")
    compare(12.45, 12.45)
    println()

    // 測試 printItem()
    printItem("Mary")
    printItem(100)
    println(true)
    println()

    // 測試 myFun()
    myFun(100, 200)
    myFun(100, "Mary")
    myFun("Mary", "Bob")
    myFun(false, 100)
}
```

### 執行流程說明

```
main()
 ├─ add(100, 32.4)
 │    ├─ T1=Int, T2=Double
 │    ├─ 100.toDouble() → 100.0
 │    ├─ 100.0.plus(32.4) → 132.4
 │    └─ 回傳 132.4，印出 "sum= 132.4"
 │
 ├─ compare1(12, 56)
 │    ├─ T=Int
 │    ├─ 同時滿足 Number 與 Comparable<Int>
 │    └─ 12 < 56
 │
 ├─ compare(50, 30)        → T=Int,    50 > 30   ✅
 ├─ compare("Mary","John") → T=String, M > J (字典序) ✅
 ├─ compare(12.45,12.45)   → T=Double, 相等 ✅
 │
 ├─ printItem("Mary")      → T=String
 ├─ printItem(100)         → T=Int
 │
 ├─ myFun(100, 200)        → T1=Int,     T2=Int
 ├─ myFun(100, "Mary")     → T1=Int,     T2=String
 ├─ myFun("Mary", "Bob")   → T1=String,  T2=String
 └─ myFun(false, 100)      → T1=Boolean, T2=Int
```

### 預期輸出

```
sum= 132.4
12 < 56
50 > 30
Mary > John
12.45 = 12.45

Item : Mary
Item : 100
true

p1= 100
p2= 200

p1= 100
p2= Mary

p1= Mary
p2= Bob

p1= false
p2= 100
```

### 核心語法對照表

| 語法 | 用途說明 |
|---|---|
| `fun <T> foo(x: T)` | 宣告單型別參數泛型函式 |
| `fun <T1, T2> foo(x: T1, y: T2)` | 宣告雙型別參數泛型函式 |
| `fun <T: Comparable<T>> foo(x: T, y: T)` | 限制 T 必須可比較大小 |
| `fun <T1: Number, T2: Number> foo(...)` | 限制 T1、T2 必須是數值型別 |
| `fun <T> foo(...) where T: A, T: B` | 限制同一個型別同時符合多個條件 |
| `p1.toDouble()` | 將 Number 子型別統一轉為 Double |
| `.plus(other)` | Double 的加法，等同 `+` 運算子 |
| `when { t1 > t2 -> ... }` | 多條件分支，比較大小後分流 |

---

## 6. 泛型類別與泛型介面

### 核心概念

- `class Rect<T>`：單一型別參數的泛型類別，`height` 和 `width` 必須同型別。
- `class PlayerClass<T1, T2>`：多型別參數的泛型類別，`name` 與 `score` 可用不同型別。
- `interface Process<T>`：泛型介面，將「要處理的資料型別」延後到實作類別決定。
- `class MyPrint : Process<String>`、`class MyData : Process<Data>`：實作時把 `T` 具體化。
- `data class Data(...)`：資料模型；`copy()` 可快速複製並改欄位、`equals()` 用於值比較。

### 對照表：泛型類別 vs 泛型介面

| 項目 | 泛型類別 | 泛型介面 |
|---|---|---|
| 目的 | 儲存泛型狀態/資料 | 定義泛型行為規格 |
| 宣告語法 | `class Name<T>(...)` | `interface Name<T> { ... }` |
| 使用方式 | 建立實例後讀寫屬性 | 由類別實作 `override` 方法 |
| 對應本課程式碼 | `Rect<T>`, `PlayerClass<T1,T2>` | `Process<T>` |

### 最小可執行範例

```kotlin
class Rect<T>(h: T, w: T) {
    var width: T = w
    var height: T = h
}

interface Process<T> {
    fun process(item: T)
}

class MyPrint : Process<String> {
    override fun process(item: String) {
        println("Item: $item")
    }
}

fun main() {
    val rect = Rect(10, 20)
    println("Rect: ${rect.height} x ${rect.width}")
    MyPrint().process("Mary")
}
```

### 常見誤區 / 注意事項

- ⚠️ `Rect<T>` 的兩個建構子參數都用同一個 `T`，不能一個 `Int` 一個 `Float`。
- ⚠️ 實作泛型介面時，型別要明確化（例如 `Process<String>`），否則無法完成方法簽章。
- ⚠️ **值比較 vs 參考比較**：`==` 比較內容（呼叫 `equals()`），`===` 比較是否同一物件參考。
- ⚠️ `data class` 預設提供 `copy()`、`equals()`、`toString()`；這些是資料模型常用 API。

---

## 7. 例題章節：泛型類別 + 泛型介面整合

### 題目背景

建立一個小型資料處理情境：
- 用 `Rect<T>` 表示不同數值型別的矩形資料。
- 用 `PlayerClass<T1, T2>` 表示玩家名稱與分數（分數型別可彈性）。
- 用 `Process<T>` 統一處理流程，分別處理 `String` 與 `Data`。

### 完整程式碼

```kotlin
class Rect<T>(h: T, w: T) {
    var width: T = w
    var height: T = h
}

class PlayerClass<T1, T2>(n: T1, s: T2) {
    var name = n
    var score = s
}

interface Process<T> {
    fun process(item: T)
}

class MyPrint : Process<String> {
    override fun process(item: String) {
        println("Item: $item")
    }
}

data class Data(val name: String, val id: Int)

class MyData : Process<Data> {
    override fun process(item: Data) {
        println("name: ${item.name}, id: ${item.id}")
    }
}

fun main() {
    val myData = MyData()
    myData.process(Data("Mary", 100))
    myData.process(Data("Bob", 101))

    val rect = Rect(10, 20)
    val rect1 = Rect(100.2F, 100.5F)

    val player = PlayerClass("Mary", 100)
    val players = PlayerClass("Mary", "Bob")

    MyPrint().process("Mary")
    val myPrint = MyPrint()
    myPrint.process("Bob")

    // data class 常用 API
    val d1 = Data("Mary", 100)
    val d2 = d1.copy(name = "Mary-2")
    println(d1 == d2) // equals()：值比較
}
```

### 執行流程說明

```
main()
 ├─ 建立 MyData 並處理兩筆 Data
 │   ├─ Data("Mary",100)
 │   └─ Data("Bob",101)
 │
 ├─ 建立 Rect<Int> 與 Rect<Float>
 │   ├─ Rect(10,20)
 │   └─ Rect(100.2F,100.5F)
 │
 ├─ 建立 PlayerClass<String,Int> 與 PlayerClass<String,String>
 │
 ├─ 建立 MyPrint 並處理字串 Mary / Bob
 │
 └─ Data.copy() 建立新物件，使用 == 觸發 equals() 做值比較
```

### 預期輸出

```text
name: Mary, id: 100
name: Bob, id: 101
Item: Mary
Item: Bob
false
```

### 核心語法對照表

| 語法 / API | 這個屬性/方法是做什麼 |
|---|---|
| `class Rect<T>(h: T, w: T)` | 宣告單型別參數泛型類別，讓寬高共用同型別 |
| `class PlayerClass<T1, T2>(n: T1, s: T2)` | 宣告雙型別參數泛型類別，讓欄位型別可分離 |
| `interface Process<T> { fun process(item: T) }` | 定義可重用的泛型處理規格 |
| `class MyPrint : Process<String>` | 將 `T` 具體指定為 `String` 的介面實作 |
| `class MyData : Process<Data>` | 將 `T` 具體指定為 `Data` 的介面實作 |
| `item.name` | 存取 `Data` 的 `name` 屬性 |
| `d1.copy(name = "Mary-2")` | 複製物件並只修改指定欄位 |
| `d1 == d2` (`equals()`) | 比較兩個物件的欄位值是否相等 |

---

## 快速總結

```
Kotlin 泛型（Generics）
│
├─ 基本泛型函式
│   ├─ 語法：fun <T> 函式名(參數: T)
│   ├─ T 可為任意型別（String、Int、Boolean…）
│   └─ 呼叫時自動推斷，不需手動指定
│
├─ 多型別參數
│   ├─ 語法：fun <T1, T2> 函式名(p1: T1, p2: T2)
│   └─ 各參數型別互相獨立
│
├─ 型別約束（上界）
│   ├─ 語法：<T: 上界型別>
│   ├─ Comparable<T> → 可用 >、<、== 比較
│   ├─ Number → 可用 .toDouble()、.toInt() 等轉換
│   └─ where 可連接多重約束（例：T 同時是 Number + Comparable）
│
├─ 泛型類別
│   ├─ Rect<T>：同型別欄位資料
│   └─ PlayerClass<T1,T2>：不同型別欄位資料
│
├─ 泛型介面
│   ├─ Process<T>：先定義行為，再由實作類別指定型別
│   └─ MyPrint / MyData：String 與 Data 的具體化實作
│
└─ data class 常用 API
    ├─ copy()：複製並改局部欄位
    ├─ equals()：值比較（`==`）
    └─ 參考比較用 `===`
```

---

> 📌 **一句話記憶**
> - 無約束泛型 `<T>` → 什麼都能傳，什麼特殊方法都不能用。
> - 有約束泛型 `<T: X>` → 只能傳 X 的子型別，但獲得 X 的所有方法。

