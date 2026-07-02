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

---

## 5. 例題章節：綜合泛型函式應用

### 題目背景

> 撰寫四個泛型函式，分別示範：
> 1. 單一型別參數印出任意項目
> 2. 雙型別參數印出兩個不同型別的值
> 3. 受 `Comparable` 約束的大小比較
> 4. 受 `Number` 約束的加法運算
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

fun main() {
    // 測試 add()
    println("sum= ${add(100, 32.4)}")
    // println("sum= ${add("Mary", 32.4)}") // ❌ 編譯錯誤

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
| `p1.toDouble()` | 將 Number 子型別統一轉為 Double |
| `.plus(other)` | Double 的加法，等同 `+` 運算子 |
| `when { t1 > t2 -> ... }` | 多條件分支，比較大小後分流 |

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
│   └─ Number → 可用 .toDouble()、.toInt() 等轉換
│
└─ 回傳型別
    ├─ 可宣告具體回傳型別（如 : Double）
    └─ 搭配約束，確保計算邏輯合法
```

---

> 📌 **一句話記憶**
> - 無約束泛型 `<T>` → 什麼都能傳，什麼特殊方法都不能用。
> - 有約束泛型 `<T: X>` → 只能傳 X 的子型別，但獲得 X 的所有方法。

