# Kotlin 抽象類別（Abstract Class）重點筆記

> 對應範例檔案：`Class_4.kt`

## 1. 為什麼需要抽象類別

**動機說明**：當一群類別「一定會有某些共同行為/屬性，但每個子類別的實作方式不同」時（例如各種圖形都要能算面積，但公式不同），如果每個類別都重寫一次會很亂，也無法保證「一定有實作」。抽象類別讓你在父類別先訂出「規格」，強制子類別完成它，同時仍能共用已經寫好的共同邏輯。

**核心概念**
- `abstract class` 不能直接 `new`（不能用 `ClassName()` 建立實體），只能被繼承。
- `abstract var` / `abstract fun`：只宣告、不實作，**子類別必須 override**，否則編譯錯誤。
- 一般（非 abstract）屬性或方法可以有預設實作，子類別可直接繼承使用，不必重寫（如範例中的 `fun2()`）。
- 抽象類別可以同時擁有「抽象成員」與「一般成員」，這是它和 `interface`（早期版本不能有狀態）最大的差異之一。

**對照表：abstract class vs interface vs open class**

| 特性 | abstract class | interface | open class |
|---|---|---|---|
| 可否直接建立實體 | 不可 | 不可 | 可 |
| 可否有建構子/狀態(var 存值) | 可以 | 不建議（僅能宣告抽象屬性） | 可以 |
| 多重繼承 | 只能繼承一個 | 可以實作多個 | 只能繼承一個 |
| 用途 | 描述「是什麼」+ 共用邏輯 | 描述「能做什麼」的能力/契約 | 一般可被繼承的類別 |

**最小可執行範例**
```kotlin
abstract class Base {
    abstract var a: Int          // 抽象屬性，子類別必須 override
    var b = 0                    // 一般屬性，直接繼承
    abstract fun fun1()          // 抽象方法，子類別必須實作
    fun fun2() {                 // 一般方法，子類別可直接使用
        println("From base class")
    }
}

class Derived : Base() {
    override var a: Int = 0
    override fun fun1() {
        println("From Derived class")
    }
}
```

**常見誤區 / 注意事項**
- 忘記 `override`：抽象成員沒有實作會導致編譯錯誤，一定要看清楚錯誤訊息缺了哪個成員。
- `abstract var a: Int` 只是宣告型別，並沒有預設值，子類別 override 時必須自己給初始值（如 `override var a: Int = 0`）。
- 抽象方法不能有函式主體（大括號），只能用 `abstract fun fun1()` 這種宣告式寫法。

**實務應用**：Android 開發中的 `BaseActivity` / `BaseFragment` 常設計成抽象類別，把「共同的生命週期邏輯」(fun2 這種) 寫在父類別，把「畫面初始化」(fun1 這種) 設計成抽象方法讓每個頁面自己實作，這就是典型的 **Template Method Pattern**。

**實務上的替代方案**：如果子類別之間完全沒有「共用狀態或共用實作」，只是要求「有相同的方法簽名」，業界更常直接用 `interface`（Kotlin interface 也能給預設實作），因為 Kotlin 只允許單一繼承 abstract class，但可以實作多個 interface，彈性較高。只有在真的需要共享狀態（像 `var b = 0`）時，才選擇 abstract class。

---

## 2. 抽象類別的建構子與參數繼承

**動機說明**：抽象類別雖然不能直接建立實體，但它仍然可以有「主建構子」，用來統一初始化子類別共用的屬性，避免每個子類別重複寫一樣的初始化程式碼。

**核心概念**
- `abstract class Shape(p1: Float = 0.0f, p2: Float = 0.0f)`：抽象類別的主建構子可以有預設參數。
- 子類別繼承時要「呼叫」父類別建構子：`class Rect(p1: Float, p2: Float) : Shape(p1, p2)`。
- 父類別的屬性（`length`, `width`, `radius`）會被所有子類別繼承，即使某個子類別用不到某個屬性（如 `Circle` 不需要 `width`）。

**對照表**

| 類別 | 使用到的父類屬性 | 覆寫的抽象方法 |
|---|---|---|
| `Rect` | `length`, `width` | `calArea() = length * width` |
| `Circle` | `radius` | `calArea() = radius.pow(2) * 3.14159f` |

**常見誤區 / 注意事項**
- 範例中 `Circle` 其實只用到 `radius`，卻仍然繼承了 `length`、`width` 兩個用不到的屬性，這是**設計上不夠精簡**的示範，容易讓後續維護者搞不清楚哪個屬性才是真正有意義的。
- 子類別呼叫父類建構子時，參數順序與型別要完全對應，型別不符會直接編譯錯誤。

**實務應用**：計算幾何圖形、UI 元件（例如各種 View 的 `width`/`height`）、或是各種訂單類型共用 `price`/`quantity` 等基礎屬性時，都可以用這種「共用建構子參數」設計。

**實務上的替代方案**：如果每種圖形需要的參數差異很大（像 `Circle` 只要半徑、`Rect` 要長寬），業界更常用 **sealed class** 搭配 `when` 表達式，讓每個子類別自己定義專屬參數，而不是共用一組容易誤用的父類參數：
```kotlin
sealed class Shape2 {
    data class Rect2(val length: Float, val width: Float) : Shape2()
    data class Circle2(val radius: Float) : Shape2()
}
fun calArea(shape: Shape2): Float = when (shape) {
    is Shape2.Rect2 -> shape.length * shape.width
    is Shape2.Circle2 -> shape.radius * shape.radius * 3.14159f
}
```
這樣可以避免「繼承了用不到的屬性」的問題，且 `when` 搭配 sealed class 編譯器會強制檢查是否涵蓋所有分支。

---

## 3. 例題章節：圖形面積計算系統

**題目背景**：設計一個抽象類別 `Shape`，讓 `Rect`（矩形）與 `Circle`（圓形）繼承，並各自實作 `calArea()` 計算面積。

**完整程式碼**
```kotlin
abstract class Shape(p1: Float = 0.0f, p2: Float = 0.0f) {
    var length: Float = p1
    var width: Float = p2
    var radius: Float = p1
    abstract fun calArea(): Float
}

class Rect(p1: Float = 0.0f, p2: Float = 0.0f) : Shape(p1, p2) {
    override fun calArea(): Float {
        return length * width
    }
}

class Circle(p1: Float = 0.0f, p2: Float = 0.0f) : Shape(p1, p2) {
    override fun calArea(): Float {
        return radius.pow(2.0f) * 3.14159f
    }
}

fun main() {
    var rect = Rect(10.0f, 15.0f)
    var circle = Circle(12.3f)
    println("The area of rectangle : ${rect.calArea()}")
    println("The area of circle : ${circle.calArea()}")
}
```

**執行流程說明**
1. `Rect(10.0f, 15.0f)` 呼叫 `Shape(10.0f, 15.0f)`，把 `length=10.0f`、`width=15.0f` 初始化。
2. `Circle(12.3f)` 呼叫 `Shape(12.3f)`（第二個參數用預設值 `0.0f`），此時 `radius = p1 = 12.3f`。
3. 呼叫 `calArea()` 時，因為是多型（polymorphism），實際執行的是各自 override 的版本。

**預期輸出**
```
The area of rectangle : 150.0
The area of circle : 475.2926
```

**核心語法對照表**

| 語法 | 說明 |
|---|---|
| `abstract fun calArea(): Float` | 宣告抽象方法，只定義簽名不定義內容 |
| `p1: Float = 0.0f` | 建構子參數預設值，呼叫時可省略 |
| `radius.pow(2.0f)` | `kotlin.math.pow` 擴充函式，計算次方 |
| `: Shape(p1, p2)` | 子類別繼承並呼叫父類主建構子 |

---

## 快速總結

```
抽象類別 (abstract class)
├─ 不能直接建立實體
├─ 抽象成員 (abstract var / abstract fun)
│   └─ 子類別「必須」override
├─ 一般成員 (var / fun)
│   └─ 子類別可直接繼承使用，不必重寫
├─ 主建構子
│   └─ 子類別需用 `: Parent(args)` 呼叫
└─ 適用情境
    ├─ 需要共用狀態 + 強制規格 → abstract class
    ├─ 只需要規格、無共用狀態 → interface
    └─ 類別種類固定、參數差異大 → sealed class
```