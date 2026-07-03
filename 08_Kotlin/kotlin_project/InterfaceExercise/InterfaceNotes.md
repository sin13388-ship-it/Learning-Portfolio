# Kotlin 介面（Interface）重點筆記

> 對應範例檔案：`Interface_1.kt`、`Interface_2.kt`、`InterfaceFunction.kt`

## 1. 介面的基本概念與多重實作

**動機說明**：現實中一個類別常常需要同時具備多種「能力」（例如一個 `Report` 同時具有「顯示個資」和「顯示成績」兩種能力）。Kotlin 只允許單一繼承（一個父類別），但允許一次實作多個 `interface`，這解決了「一個物件要具備多種行為」卻不需要多重繼承的問題。

**核心概念**
- `interface` 可以宣告抽象屬性（`var name: String`）與帶預設實作的方法（`fun show() {...}`）。
- 一個類別可以用逗號同時實作多個 interface：`class Report(...) : IntfA, IntfB`。
- 當兩個介面有**同名方法**（這裡都叫 `show()`）時，子類別必須自己 override 並用 `super<介面名>.方法()` 明確指定要呼叫哪一個，否則編譯器無法判斷。

**對照表：super 的呼叫方式**

| 語法 | 用途 |
|---|---|
| `super.show()` | 只有單一父類別/介面時可用 |
| `super<IntfA>.show()` | 多個介面有同名方法時，指定呼叫 `IntfA` 版本 |
| `super<IntfB>.show()` | 指定呼叫 `IntfB` 版本 |

**最小可執行範例**
```kotlin
interface IntfA {
    var name: String
    fun show() { println("name= $name") }
}
interface IntfB {
    var math: Int
    fun show() { println("math= $math") }
}
class Report(_name: String, _math: Int) : IntfA, IntfB {
    override var name: String = _name
    override var math: Int = _math
    override fun show() {
        super<IntfA>.show()
        super<IntfB>.show()
    }
}
```

**常見誤區 / 注意事項**
- 介面裡的 `var name: String` 只是「宣告有這個屬性」，並沒有預設值，實作端一定要自己 `override var name: String = ...` 給值，介面本身不能存放有初始值的 `var`（沒有 backing field）。
- 兩個介面方法同名卻沒有在子類別 override + 指定 `super<X>`，會編譯錯誤（衝突無法自動解決）。

**實務應用**：Android 的 `View` 常同時實作 `Comparable`、`OnClickListener` 等多個介面；後端 API 設計中，一個 Service 類別可能同時實作 `Loggable`、`Cacheable` 等能力介面，這種「多重能力組合」正是 interface 多重實作最常見的用法。

**實務上的替代方案**：如果介面之間本來就有明確的「主從」關係（例如 `IntfB` 其實是 `IntfA` 的特化版本），更常見的做法是用**介面繼承**（`interface IntfB : IntfA`）取代平行實作兩個獨立介面，可以減少同名方法衝突的機會。

---

## 2. 介面實現多型（Polymorphism）

**動機說明**：當我們有多種圖形（矩形、圓形）都要計算面積與周長時，如果分別寫成不相關的類別，日後想「把所有圖形放進一個清單統一處理」會很困難。介面讓不同類別擁有共同的「型別骨架」，因此可以用**同一種型別的容器**（`List<IShape>`）統一操作不同的實作。

**核心概念**
- `interface IShape { fun area(): Double; fun perimeter(): Double }` 定義共同契約。
- `Rectangle`、`Circle` 分別實作 `IShape`，但內部公式完全不同。
- `mutableListOf<IShape>(rect, circle)`：把不同類別的物件放進**同一個介面型別**的清單，遍歷時呼叫 `item.area()` 會自動執行對應類別的版本（多型）。

**對照表**

| 類別 | area() 公式 | perimeter() 公式 |
|---|---|---|
| `Rectangle` | `width * length` | `(width+length)*2` |
| `Circle` | `π * r²` | `2πr` |

**常見誤區 / 注意事項**
- 若用一般 `class SimpleCircle : Drawable`、`class Button : Drawable, Click` 這種只實作單一功能介面（`draw()`, `click()`）的寫法，要注意介面裡沒有預設實作時，該方法一定要在類別內完全實作，不能留空。
- 用 `for (item in shapes)` 遍歷介面型別清單時，只能呼叫介面裡宣告過的方法（如 `area()`），無法直接呼叫 `Rectangle` 專屬的 `showInfo()`，除非額外做型別轉換 (`is Rectangle`)。

**實務應用**：這是 Android/後端最常見的「策略模式」雛型——例如支付系統定義 `interface PaymentMethod { fun pay(amount: Double) }`，讓信用卡、電子錢包各自實作，主程式只依賴 `PaymentMethod` 介面，未來新增付款方式不用修改既有程式碼（開閉原則）。

**實務上的替代方案**：如果 `IShape` 的實作種類是**固定且有限**的（不會再新增），業界也常改用 `sealed class` + `when`，好處是編譯器會強制檢查所有分支都有處理；而 `interface` 更適合「未來還會不斷擴充新實作」的開放情境（例如插件系統、第三方套件）。

---

## 3. fun interface（SAM，單一抽象方法介面）

**動機說明**：如果一個介面只有「一個」需要實作的方法（例如「執行某個動作」），每次都要另外寫一個 `class` 去實作會很囉唆。`fun interface` 讓這種情況可以直接用 **lambda 表達式**當作介面的實作，大幅簡化程式碼，這也是 Kotlin 版的 Java 函式介面（Functional Interface / SAM）。

**核心概念**
- `fun interface Action { fun execute() }`：只能有一個抽象方法。
- 呼叫需要 `Action` 型別參數的函式時，可以直接傳入 lambda：`runAction { println("...") }`，不需要額外寫 class 或 object。
- 若 lambda 只有一個參數，可以省略參數名稱直接用隱含變數 `it` 代替（如 `StudentWork` 範例的 `execute(name: String)`）。
- 一般類別（如 `JobClass`）也可以照常用 `class JobClass : StudentWork { override fun execute(...) {...} }` 的方式實作 `fun interface`。

**對照表：三種實作 fun interface 的方式**

| 寫法 | 範例 | 適用情境 |
|---|---|---|
| class 實作 | `class DoAction : Action { override fun execute() {...} }` | 需要重複使用、有自己的狀態 |
| object 表達式 | `runAction(object : Action { override fun execute() {...} })` | 只用一次、想維持明確語法 |
| lambda（尾隨語法） | `runAction { println("...") }` | 只用一次、追求簡潔 |

**最小可執行範例**
```kotlin
fun interface Action { fun execute() }

fun runAction(action: Action) {
    println("Starting runAction")
    action.execute()
    println("end of runAction")
}

fun main() {
    runAction { println("function implement") }   // 最後一個參數是 lambda，可寫在括號外
}
```

**常見誤區 / 注意事項**
- `fun interface` 只能有**一個**抽象方法，多一個就無法用 lambda 簡化語法。
- 當 lambda 是函式的**最後一個參數**時，Kotlin 允許把它寫在小括號外面（`runAction() { ... }` 甚至可省略空括號寫成 `runAction { ... }`），這是「尾隨 lambda（trailing lambda）」語法糖，不是新的規則，只是省略寫法。
- lambda 只有一個參數時，可以省略具名參數改用 `it`：`task.execute(name)` 對應的 lambda 可簡寫成 `{ println("...${it}") }`。

**實務應用**：Android 的 `setOnClickListener { }`、Kotlin 標準庫的 `Comparator { a, b -> ... }` 都是 `fun interface` 的實際應用，讓 callback 風格的 API 使用起來像原生語法一樣簡潔。

**實務上的替代方案**：如果未來這個「動作」可能需要擴充成多個相關方法（例如除了 `execute()` 還要有 `cancel()`），就不適合用 `fun interface`，應該改回一般 `interface`，避免日後要拆成多個 SAM 介面。

---

## 4. 例題章節：任務指派系統（fun interface 實戰）

**題目背景**：設計一個 `TaskClass`，可以接受不同型式（class、匿名物件、lambda）的 `StudentWork` 實作來執行任務。

**完整程式碼**
```kotlin
fun interface StudentWork {
    fun execute(name: String)
}

class TaskClass(val name: String) {
    fun handleTask(task: StudentWork) {
        println("Task start")
        task.execute(name)
        println("Task end")
    }
}

class JobClass(val name: String) : StudentWork {
    override fun execute(name: String) {
        println("My job is done by $name")
    }
}

fun main() {
    val myJob = JobClass("John")
    val myTask2 = TaskClass("Jack")
    myTask2.handleTask(myJob)

    val myTask = TaskClass("John")
    myTask.handleTask { name: String -> println("myTask implement 2 -$name") }
    myTask.handleTask { println("myTask implement 2 -$it") }
}
```

**執行流程說明**
1. `myTask2.handleTask(myJob)`：傳入一般類別實作的 `JobClass` 物件。
2. `myTask.handleTask { name: String -> ... }`：用具名參數的 lambda 直接當作 `StudentWork` 實作傳入。
3. `myTask.handleTask { println("...${it}") }`：因為 lambda 只有一個參數，改用 `it` 代替，效果相同。

**預期輸出（節錄）**
```
Task start
My job is done by Jack
Task end
Task start
myTask implement 2 -John
Task end
Task start
myTask implement 2 -John
Task end
```

**核心語法對照表**

| 語法 | 說明 |
|---|---|
| `fun interface` | 定義單一抽象方法介面，可用 lambda 實作 |
| `task.execute(name)` | 呼叫傳入的介面實作（不論是 class 還是 lambda） |
| `{ name: String -> ... }` | 具名參數 lambda 寫法 |
| `{ ...it... }` | 單一參數時的隱含變數簡寫 |

---

## 快速總結

```
介面 (interface)
├─ 一般 interface
│   ├─ 可宣告抽象屬性 (var) → 實作端需 override 給值
│   ├─ 可有預設方法實作
│   ├─ 可多重實作 (class : IntfA, IntfB)
│   └─ 同名方法衝突 → 需 override + super<介面名>.方法()
├─ 多型應用
│   └─ 用 List<介面型別> 統一存放不同類別物件
└─ fun interface（SAM）
    ├─ 限定「只能一個」抽象方法
    ├─ 可用 lambda 直接實作，取代寫 class
    └─ 適合 callback / 單一動作情境
```