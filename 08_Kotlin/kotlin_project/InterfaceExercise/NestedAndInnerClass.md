# Kotlin 巢狀類別（Nested Class）與內部類別（Inner Class）重點筆記

> 對應範例檔案：`NestedClass.kt`

## 1. Nested Class vs Inner Class：能不能存取外部類別的東西

**動機說明**：有些類別的存在意義「只跟某個特定類別有關」（例如 `Calculator` 裡的 `Adder`、`Phone` 裡的 `SimCard`），把它們寫成獨立的頂層類別會讓程式碼結構鬆散、難以看出彼此的從屬關係。Kotlin 允許把類別定義在另一個類別內部，藉此表達「這個類別是屬於外部類別的一部分」，並依需求決定要不要能存取外部類別的資料。

**核心概念**
- **Nested Class（巢狀類別，預設）**：用 `class Nested` 直接定義在外部類別裡，**不能**存取外部類別的屬性/方法，建立時**不需要**先有外部類別的實體：`Outer.Nested()`。
- **Inner Class（內部類別）**：要加上 `inner` 關鑑字，`inner class Inner`，**可以**直接存取外部類別的屬性/方法（如範例中的 `message`、`outerFun()`）；建立時**必須**先有外部類別的實體：`outerIn.Inner()`。
- 判斷依據很單純：**需不需要用到外部類別的資料** → 需要就用 `inner`，不需要就用一般巢狀類別即可。

**對照表：Nested vs Inner**

| 特性 | `class Nested`（巢狀） | `inner class Inner`（內部） |
|---|---|---|
| 能否存取外部類別成員 | 不能 | 可以 |
| 建立方式 | `Outer.Nested()` | `outerInstance.Inner()` |
| 是否依附外部實體 | 否，可獨立建立 | 是，必須先有外部物件 |
| 適用情境 | 純粹分組、邏輯相關但不需共享資料 | 需要用到外部類別的狀態或方法 |

**最小可執行範例**
```kotlin
class Outer {
    val message = "Hello from Outer"
    class Nested {
        fun greet(): String = "Hello from Nested"
    }
}

class OuterIn {
    val message = "Hello from OuterIn"
    fun outerFun() { println("This is outerIn function") }
    inner class Inner {
        fun greet() = "Message is $message"     // 可以直接用外部的 message
        fun innerFun() { outerFun() }           // 可以直接呼叫外部的方法
    }
}

fun main() {
    val nested = Outer.Nested()                 // 不需要 Outer 實體
    val outerIn = OuterIn()
    val inner = outerIn.Inner()                 // 必須先有 outerIn 實體
    println(inner.greet())
}
```

**常見誤區 / 注意事項**
- 忘記加 `inner`：如果 `Inner` 沒加 `inner` 關鍵字卻想在裡面直接用 `message`，會編譯錯誤，因為預設巢狀類別看不到外部類別的成員。
- 建立巢狀類別時寫成 `Outer().Nested()`（多此一舉建立了一個不會用到的 `Outer` 實體），正確寫法是 `Outer.Nested()`，因為巢狀類別跟外部實體無關。
- 建立內部類別時忘記先有外部實體，直接寫 `OuterIn.Inner()` 會編譯錯誤，必須是 `outerIn物件.Inner()`。

**實務應用**：Android 的 `RecyclerView.Adapter` 常搭配 `inner class ViewHolder`，因為 `ViewHolder` 常需要存取外部 `Adapter` 的資料列表或 context；而像 `Calculator.Adder`、`Phone.SimCard` 這類「純工具、不需共享狀態」的角色，則適合用一般巢狀類別，語意上也更清楚地告訴讀者「這個 Adder 跟 Calculator 實體無關」。

**實務上的替代方案**：如果巢狀類別/內部類別的邏輯已經變得複雜、或未來可能需要獨立測試、重複使用在多個地方，業界通常會把它**拆成獨立的頂層類別**，並用建構子參數或介面傳入所需要的外部資料（依賴注入的概念），而不是靠 `inner class` 隱含存取外部狀態，這樣程式碼耦合度較低、也比較好寫單元測試。

---

## 2. 例題章節：電話與 SIM 卡

**題目背景**：模擬「手機與其內部 SIM 卡」的關係——SIM 卡一定屬於某支手機，且需要知道手機的號碼，適合用 `inner class` 表達這種「從屬且需要共享資料」的關係。

**完整程式碼**
```kotlin
class Phone(val number: String) {
    inner class SimCard {
        fun showNumber() {
            println("Sim card number is :$number")
        }
    }
}

fun main() {
    val myPhone = Phone("123456")
    val sim = myPhone.SimCard()
    sim.showNumber()

    // inline 寫法
    Phone("9999").SimCard().showNumber()
}
```

**執行流程說明**
1. `Phone("123456")` 建立一支手機物件，`number` 被設為 `"123456"`。
2. `myPhone.SimCard()`：因為 `SimCard` 是 `inner class`，必須透過已存在的 `myPhone` 實體才能建立，建立出來的 `sim` 物件可以直接讀到 `myPhone` 的 `number`。
3. `sim.showNumber()` 印出對應手機的號碼。
4. `Phone("9999").SimCard().showNumber()`：把「建立手機」與「建立 SIM 卡」串在同一行，效果相同，只是寫法更精簡（inline 寫法）。

**預期輸出**
```
Sim card number is :123456
Sim card number is :9999
```

**核心語法對照表**

| 語法 | 說明 |
|---|---|
| `inner class SimCard` | 宣告內部類別，可存取外部類別 `Phone` 的成員 |
| `myPhone.SimCard()` | 透過外部類別實體建立內部類別實體 |
| `$number` | 內部類別直接讀取外部類別的建構子屬性 |

---

## 快速總結

```
巢狀 / 內部類別
├─ class Nested（預設巢狀類別）
│   ├─ 不能存取外部類別成員
│   └─ 建立：Outer.Nested()（不需要外部實體）
└─ inner class Inner（內部類別）
    ├─ 可直接存取外部類別的屬性/方法
    └─ 建立：外部實體.Inner()（必須先有外部實體）

判斷準則：需要用到外部類別的資料/方法嗎？
    是 → inner class
    否 → 一般巢狀 class
```