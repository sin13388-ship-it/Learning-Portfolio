# Kotlin Lambda（匿名函式）重點筆記

## 1. Lambda 基礎語法

### 核心概念
- **Lambda** 是沒有名稱的匿名函式，用 `{}` 包裝，可賦值給變數或傳入函式
- **型別簽章**：`(參數型別) -> 回傳型別`，型別必須明確對應
- **隱式回傳**：Lambda 內最後一行自動作為回傳值，不需寫 `return`
- **`it` 參數**：單一參數時的預設名稱，可省略宣告（推薦用於簡短 Lambda）

### 對照表

| 特性 | 寫法 | 適用情景 |
|------|------|--------|
| 無參數，回傳字串 | `val f: () -> String = { "hello" }` | 常數型邏輯 |
| 單參數明確型別 | `val f: (Int) -> Int = { x: Int -> x + 1 }` | 型別複雜時 |
| 單參數用 `it` | `val f: (Int) -> Int = { it + 1 }` | 簡潔表達 |
| 多參數 | `val f: (Int, String) -> Boolean = { x, name -> x > 0 }` | 複數邏輯 |
| 無回傳值（Unit） | `val f: () -> Unit = { println("hi") }` | 副作用操作 |

### 最小可執行範例

```kotlin
fun main() {
    // 1. 基本 Lambda：明確型別
    val greeting: () -> String = { "Welcome to SimVillage" }
    println(greeting())  // 輸出：Welcome to SimVillage

    // 2. 帶參數的 Lambda
    val add: (Int, Int) -> Int = { x, y -> x + y }
    println(add(3, 5))  // 輸出：8

    // 3. 用 it 簡化
    val double: (Int) -> Int = { it * 2 }
    println(double(10))  // 輸出：20

    // 4. 無回傳值
    val log: () -> Unit = { println("Logging...") }
    log()  // 輸出：Logging...
}
```

### 常見誤區 / 注意事項
- ⚠️ **型別簽章必須完整**：若宣告 `(Int) -> Int`，Lambda 內參數就不能改型別
- ⚠️ **`it` 只能用於單參數**：多參數時必須明確命名（如 `{ x, y -> ... }`）
- ⚠️ **最後一行自動回傳**：不用寫 `return`，但若中途有 `return` 語句需要明確標記

---

## 2. Lambda 作為函式參數

### 核心概念
- **高階函式**：接受 Lambda 作為參數的函式，讓行為動態化
- **尾部 Lambda**：當 Lambda 是函式的最後一個參數時，可寫在 `()` 外面（語法糖）
- **具名參數**：傳遞 Lambda 時可用 `paramName = { ... }` 保持可讀性
- **動態替換**：變數存的 Lambda 可在執行時改變邏輯

### 對照表

| 情景 | Lambda 位置 | 程式碼 |
|------|-----------|--------|
| 一般參數 | 在 `()` 內 | `func(10, { it * 2 })` |
| 尾部參數 | 在 `()` 外 | `func(10) { it * 2 }` |
| 尾部參數（具名） | 在 `()` 外 | `func(10, process = { it * 2 })` |
| 多個 Lambda | 都在 `()` 內 | `func({ x -> x }, { y -> y })` |

### 最小可執行範例

```kotlin
// 接受 Lambda 參數的函式
fun bill(number: Int, calculate: (Int) -> Int): Int {
    return calculate(number)
}

fun main() {
    // 方式 1：Lambda 在括號內
    val result1 = bill(10, { it * 25 })
    println(result1)  // 輸出：250

    // 方式 2：Lambda 是最後參數，寫在括號外（尾部 Lambda）
    val result2 = bill(10) { it * 25 }
    println(result2)  // 輸出：250

    // 方式 3：先定義 Lambda，再傳入
    var cal: (Int) -> Int = { it * 23 }
    val result3 = bill(10, cal)
    println(result3)  // 輸出：230

    // 方式 4：動態改變 Lambda
    cal = { price -> price * 2 }
    val result4 = bill(10, cal)
    println(result4)  // 輸出：20
}
```

### 常見誤區 / 注意事項
- ⚠️ **尾部 Lambda 規則**：只有 Lambda **是最後一個參數**時才能寫在 `()` 外；若後面還有其他參數，必須在 `()` 內
- ⚠️ **具名參數 + 尾部 Lambda**：可混合使用（如 `func(10, process = { ... })`）
- ⚠️ **型別簽章必須相符**：傳入的 Lambda 型別要完全符合函式宣告

---

## 3. 多參數 Lambda 與複雜邏輯

### 核心概念
- **多參數 Lambda**：`(Type1, Type2) -> ReturnType` 語法，參數間用逗號分隔
- **自動型別推斷**：若函式簽章已定義，Lambda 內參數可不寫型別
- **複雜邏輯**：Lambda 內可用多行程式碼，最後一行自動回傳
- **字串內插**：用 `${}` 在字串中引用 Lambda 參數

### 對照表

| 場景 | 寫法 |
|------|------|
| 二參數，型別推斷 | `{ name, age -> "Hi $name, age: $age" }` |
| 二參數，明確型別 | `{ name: String, age: Int -> "Hi $name, age: $age" }` |
| 多行邏輯 | `{ x, y -> val sum = x + y; sum * 2 }` 或換行 |
| 回傳值明確 | `{ x, y -> when(x) { ... } }` |

### 最小可執行範例

```kotlin
fun runSimulate(name: String, process: (String, Int) -> String) {
    val building = (1..10).random()  // 隨機 1~10
    println(process(name, building))
}

fun main() {
    // 方式 1：Lambda 在括號內，完整型別宣告
    runSimulate("Mary", funTwoParam = { name: String, age: Int ->
        "Hi $name, your age is $age"
    })

    // 方式 2：Lambda 拉出來，型別推斷
    runSimulate("John") { name, building ->
        val test = "$name, Welcome to building $building"
        test
    }
}
```

### 常見誤區 / 注意事項
- ⚠️ **型別推斷 vs 明確宣告**：若函式簽章清楚，Lambda 內可省略參數型別；否則需明確寫出
- ⚠️ **最後一行才是回傳**：中途的敘述句不會被回傳；如需多行複雜邏輯，最後一定要有該變數或表達式

---

## 4. 函式回傳 Lambda（高階函式進階）

### 核心概念
- **函式可回傳 Lambda**：型別簽章 `fun xxx(): (Param) -> Return { return { ... } }`
- **嵌套呼叫**：`func()(argument)` 先執行外層函式取得 Lambda，再用引數呼叫
- **Closure 閉包**：Lambda 可存取外層函式的變數，並記住其狀態
- **when 分支回傳**：根據條件回傳不同的 Lambda，實現動態函式工廠

### 對照表

| 特性 | 程式碼 | 用途 |
|------|--------|------|
| 簡單回傳 Lambda | `fun f(): (Int) -> Int { return { it * 2 } }` | 工廠模式 |
| 嵌套呼叫 | `f()(5)` | 先取 Lambda，再執行 |
| 條件回傳 | `when(x) { 'a' -> { ... }; else -> { ... } }` | 多邏輯工廠 |
| Closure | Lambda 內使用外層變數 | 狀態記憶 |

### 最小可執行範例

```kotlin
// 簡單例子：溫度轉換工廠
fun returnTmpConvert(caption: String): (Double) -> Double {
    return when(caption) {
        "C2F" -> { it * 1.8 + 32 }      // 攝氏轉華氏
        "F2C" -> { (it - 32) / 1.8 }    // 華氏轉攝氏
        else -> { -1.0 }
    }
}

fun main() {
    // 嵌套呼叫：先呼叫 returnTmpConvert("C2F") 取得 Lambda，再用 37.0 執行
    val F = returnTmpConvert("C2F")(37.0)
    println("C->F: $F")  // 輸出：C->F: 98.6

    val C = returnTmpConvert("F2C")(98.6)
    println("F->C: $C")  // 輸出：F->C: 37.0
}
```

### 常見誤區 / 注意事項
- ⚠️ **嵌套呼叫易混淆**：`func(arg1)(arg2)` 中，前者是函式呼叫，後者是 Lambda 呼叫
- ⚠️ **Closure 狀態**：Lambda 內修改外層變數時要用 `var`（非 `val`），且會保留狀態
- ⚠️ **when 內每支都要回傳 Lambda**：型別簽章固定，分支不能回傳 null 或其他型別

---

## 5. Lambda 與內建方法的結合

### 核心概念
- **擴展函式 + Lambda**：Kotlin 內建方法接受 Lambda，如 `count()`、`filter()`、`map()`
- **count() 計數**：不帶 Lambda 時計全部；帶條件 Lambda 時計符合項目
- **谓词 Lambda**：回傳 `Boolean` 的 Lambda，用於篩選條件
- **簡化語法**：當 Lambda 是尾部參數時，可省略外層括號

### 對照表

| 方法 | 功能 | Lambda 型別 |
|------|------|-----------|
| `count()` | 計全部元素 | N/A |
| `count { ... }` | 計符合條件的 | `(Elem) -> Boolean` |
| `filter { ... }` | 過濾符合條件 | `(Elem) -> Boolean` |
| `map { ... }` | 轉換每個元素 | `(Elem) -> NewType` |

### 最小可執行範例

```kotlin
fun main() {
    val data = "Mississippi"

    // 方式 1：計全部字元
    val total = data.count()
    println("All count: $total")  // 輸出：11

    // 方式 2：計特定字元（Lambda 在括號內）
    val countS1 = data.count({ letter -> letter == 's' })
    println("Count 's': $countS1")  // 輸出：4

    // 方式 3：計特定字元（尾部 Lambda 簡化）
    val countS2 = data.count { letter -> letter == 's' }
    println("Count 's': $countS2")  // 輸出：4

    // 方式 4：用 it 更簡潔
    val countS3 = data.count { it == 's' }
    println("Count 's': $countS3")  // 輸出：4
}
```

### 常見誤區 / 注意事項
- ⚠️ **括號位置**：`count({ ... })` 與 `count { ... }` 等效，但後者更簡潔（需 Lambda 是尾部參數）
- ⚠️ **型別推斷**：`count { it == 's' }` 時，`it` 型別自動推斷為 `Char`，無需明確宣告
- ⚠️ **集合 vs 字串**：`count()` 對字串和集合都適用，行為相同

---

## 例題 1：年齡驗證系統（Boolean Lambda）

### 題目背景
實現一個購酒年齡檢驗系統。根據使用者輸入的年齡，用 Lambda 判斷是否能購買，並支援多種年齡限制條件（18 歲、21 歲等）。

### 完整程式碼

```kotlin
// 接受條件 Lambda 的函式
fun buyWine(age: Int, condition: (Int) -> Boolean): String {
    val result: String
    
    if (condition(age))
        result = "You can buy wine"
    else
        result = "You are under 18"
    
    return result
}

fun main() {
    println("Input your age: ")
    val age = readln()?.toIntOrNull() ?: 0

    // 方式 1：尾部 Lambda，條件為 >= 18
    val msg1 = buyWine(age) { it >= 18 }
    println(msg1)

    // 方式 2：括號內 Lambda，條件為 > 20
    val msg2 = buyWine(age, { it > 20 })
    println(msg2)
}
```

### 執行流程說明

1. 程式提示使用者輸入年齡
2. 輸入被轉換為 `Int`（轉換失敗時預設為 0）
3. 第一次呼叫 `buyWine(age) { it >= 18 }`：
    - 外層 Lambda 條件為 `it >= 18`
    - 若年齡 >= 18，回傳 `"You can buy wine"`
    - 否則回傳 `"You are under 18"`
4. 第二次呼叫用不同條件 `it > 20` 再驗證一次

### 預期輸出（假設輸入 25）
```
Input your age: 
25
You can buy wine
You can buy wine
```

### 核心語法對照表

| 語法 | 說明 |
|------|------|
| `readln()?.toIntOrNull() ?: 0` | Safe call：若轉換失敗回傳 null，Elvis 運算子 `?:` 預設為 0 |
| `buyWine(age) { it >= 18 }` | 尾部 Lambda 語法；Lambda 型別推斷為 `(Int) -> Boolean` |
| `{ it > 20 }` | 單參數用 `it`；括號內 Lambda 也支援 |
| `condition(age)` | 呼叫 Lambda，`age` 傳入參數，`condition` 回傳 `Boolean` |

---

## 例題 2：計算機工廠（多分支回傳 Lambda）

### 題目背景
實現一個計算機工廠，根據選擇的運算符（`+`, `-`, `*`, `/`），動態回傳對應的計算 Lambda。使用者可連鎖呼叫 `numProcess(op)(x, y)` 直接得到結果。

### 完整程式碼

```kotlin
// 函式回傳 Lambda：根據運算符回傳對應的計算方法
fun numProcess(dir: Char): (Int, Int) -> Int {
    return when(dir) {
        '+' -> { x: Int, y: Int -> x + y }
        '-' -> { x: Int, y: Int -> x - y }
        '*' -> { x: Int, y: Int -> x * y }
        '/' -> { x: Int, y: Int -> x / y }
        else -> { x: Int, y: Int -> -1 }
    }
}

fun main() {
    // 方式 1：先取得 Lambda，再使用
    val add: (Int, Int) -> Int = numProcess('+')
    val sum1 = add(10, 20)
    println("10 + 20 = $sum1")  // 輸出：30

    // 方式 2：嵌套呼叫（連鎖 ()()）
    val sum2 = numProcess('-')(10, 20)
    println("10 - 20 = $sum2")  // 輸出：-10

    val sum3 = numProcess('*')(10, 20)
    println("10 * 20 = $sum3")  // 輸出：200

    val sum4 = numProcess('/')(20, 4)
    println("20 / 4 = $sum4")  // 輸出：5

    val sum5 = numProcess('%')(10, 20)
    println("10 % 20 = $sum5")  // 輸出：-1（未支援）
}
```

### 執行流程說明

1. `numProcess('+')` 執行：
    - `when` 分支匹配 `'+'`
    - 回傳 Lambda `{ x: Int, y: Int -> x + y }`
2. `(10, 20)` 呼叫回傳的 Lambda：
    - `x = 10`, `y = 20`
    - 計算 `10 + 20 = 30`
    - 回傳結果
3. 嵌套呼叫 `numProcess('-')(10, 20)` 同理

### 預期輸出
```
10 + 20 = 30
10 - 20 = -10
10 * 20 = 200
20 / 4 = 5
10 % 20 = -1
```

### 核心語法對照表

| 語法 | 說明 |
|------|------|
| `fun numProcess(...): (Int, Int) -> Int` | 函式回傳型別為 `(Int, Int) -> Int` |
| `when(dir) { ... }` | `when` 每支必須回傳符合型別的 Lambda |
| `numProcess('+')(10, 20)` | 嵌套 `()()` 呼叫：先執行外層函式，再執行 Lambda |
| `{ x: Int, y: Int -> ... }` | 多參數 Lambda 必須明確參數型別（或推斷後省略） |

---

## 例題 3：溫度轉換系統與閉包（Closure）

### 題目背景
建立溫度轉換 Lambda 工廠 + 客服問候系統，展示 **函式工廠**、**嵌套呼叫** 和 **Closure 狀態記憶**。

### 完整程式碼

```kotlin
// 工廠 1：溫度轉換
fun returnTmpConvert(caption: String): (Double) -> Double {
    return when(caption) {
        "C2F" -> { it * 1.8 + 32 }
        "F2C" -> { (it - 32) / 1.8 }
        else -> { -1.0 }
    }
}

// 工廠 2：客服問候（示範 Closure 狀態）
fun ConfigGreeting(): (String) -> String {
    val name = "hospital"
    var numBuilding = 5  // var：可變狀態
    
    return { playerName: String ->
        numBuilding += 1  // Closure 修改外層變數
        println("Adding $numBuilding $name")
        "Welcome to new village, $playerName"
    }
}

fun main() {
    // ===== 溫度轉換 =====
    val F = returnTmpConvert("C2F")(37.0)
    println("C->F: $F")  // 輸出：98.6

    val C = returnTmpConvert("F2C")(98.6)
    println("F->C: $C")  // 輸出：37.0

    // ===== 客服問候（Closure） =====
    val greeting = ConfigGreeting()
    val msg1 = greeting("Mary")
    println(msg1)  // 輸出：Welcome to new village, Mary
                   // （上一行輸出：Adding 6 hospital）

    val msg2 = greeting("John")
    println(msg2)  // 輸出：Welcome to new village, John
                   // （上一行輸出：Adding 7 hospital）
}
```

### 執行流程說明

**溫度轉換部分：**
1. `returnTmpConvert("C2F")` 回傳 Lambda `{ it * 1.8 + 32 }`
2. `(37.0)` 執行該 Lambda，得 37.0 * 1.8 + 32 = 98.6

**Closure 部分：**
1. `ConfigGreeting()` 回傳 Lambda，Lambda 記住外層變數 `numBuilding = 5`
2. 首次執行 `greeting("Mary")`：
    - `numBuilding += 1` 變成 6
    - 輸出 `"Adding 6 hospital"`
    - 回傳問候訊息
3. 再次執行 `greeting("John")`：
    - `numBuilding` **仍保持 6**，再 `+= 1` 變成 7（狀態記憶）
    - 輸出 `"Adding 7 hospital"`

### 預期輸出
```
C->F: 98.6
F->C: 37.0
Adding 6 hospital
Welcome to new village, Mary
Adding 7 hospital
Welcome to new village, John
```

### 核心語法對照表

| 語法 | 說明 |
|------|------|
| `{ it * 1.8 + 32 }` | 單參數 Lambda 用 `it` 簡化 |
| `(37.0)` | 執行 Lambda，相當於 `lambda.invoke(37.0)` |
| `var numBuilding = 5` | **必須用 `var`** 才能在 Closure 內修改 |
| `numBuilding += 1` | Lambda 內修改外層變數，狀態被記憶 |
| `ConfigGreeting()("Mary")` | 連鎖呼叫，前者取 Lambda，後者執行 |

---

## 快速總結

```
Kotlin Lambda（匿名函式）
├─ 基礎語法
│  ├─ 型別簽章：(參數) -> 回傳值
│  ├─ 賦值變數：val f: (Int) -> Int = { it * 2 }
│  ├─ 單參數用 it：省略型別宣告
│  └─ 隱式回傳：最後一行自動 return
│
├─ 作為函式參數（高階函式）
│  ├─ 在括號內：func(x, { ... })
│  ├─ 尾部 Lambda：func(x) { ... }（最後參數時）
│  ├─ 型別推斷：Lambda 型別由函式簽章決定
│  └─ 動態替換：可用變數存 Lambda，執行時修改
│
├─ 多參數 Lambda
│  ├─ 明確型別：{ x: Int, y: String -> ... }
│  ├─ 型別推斷：{ x, y -> ... }（由函式決定）
│  ├─ 多行邏輯：最後一行自動回傳
│  └─ 字串內插：用 "${變數}" 插入參數
│
├─ 函式回傳 Lambda（工廠模式）
│  ├─ 簽章：fun f(): (P) -> R { return { ... } }
│  ├─ 嵌套呼叫：f(arg)(value) 先取後執行
│  ├─ when 分支：各分支回傳不同 Lambda
│  └─ Closure 閉包：Lambda 記住外層 var 狀態
│
├─ 內建方法 + Lambda
│  ├─ count { ... }：計符合條件
│  ├─ filter { ... }：過濾元素
│  ├─ map { ... }：轉換元素
│  └─ 謂詞 Lambda：回傳 Boolean 條件
│
└─ 關鍵差異
   ├─ 值比較 vs 參考比較：Lambda 無此問題（函式是物件）
   ├─ var vs val：Closure 內修改外層變數需用 var
   ├─ 尾部 Lambda 規則：只有最後參數才能寫在 () 外
   └─ 型別簽章必須完全相符：傳入 Lambda 型別要符合函式宣告
```

---
