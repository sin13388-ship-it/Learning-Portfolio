# Kotlin 物件導向重點筆記（屬性初始化、建構子、繼承與多型）

> 依據課堂檔案整理：`PlayerClass.kt`、`InfoClass.kt`、`InheritClass.kt`、`NewCar.kt`、`Class_1~3.kt`

---

## 1. 屬性初始化與基本類別

### 核心概念
- Kotlin 類別的屬性（`var`/`val`）**沒有預設值就必須初始化**，這是為了在編譯期就杜絕「忘記賦值」造成的 NullPointerException 類問題，比 Java 更早攔截錯誤。
- 一般方法（如 `show()`）直接讀寫屬性即可，不需要額外的 `this` 除非有參數名稱衝突。
- `private var` 屬性只能在類別內部存取，是最基本的封裝手段。

### 動機說明
在真實專案中，一個物件建立後如果屬性是「半初始化」狀態，後續呼叫方法很容易噴例外。Kotlin 強制初始化，逼你在設計類別時就想清楚「這個物件一出生該長什麼樣子」。

### 最小可執行範例
```kotlin
class PlayerClass {
    var name: String = ""
    var score: Int = 0

    fun show() {
        println("name= $name, score= $score")
    }
}

fun main() {
    val player = PlayerClass()
    player.name = "Mary"
    player.score = 100
    player.show() // name= Mary, score= 100
}
```

### 常見誤區
- 忘記給預設值又沒在建構子賦值 → 編譯錯誤，這是 Kotlin 的保護機制，不是 bug。
- `private var newName` 這種私有屬性只能透過類別提供的方法（如 `setData()`）修改，直接從外部存取會編譯失敗。

---

## 2. Getter / Setter 客製化

### 核心概念
- Kotlin 屬性背後其實都有預設的 getter/setter，你可以**覆寫**它們來加入資料驗證、格式轉換等邏輯。
- 自訂 setter 內用 `field` 代表「實際儲存的值」，**不能直接寫屬性名稱**，否則會造成無窮遞迴。
- 一個屬性只能有一個 getter、一個 setter，寫在屬性宣告的正下方（縮排對齊）。

### 對照表
| 語法 | 說明 |
|---|---|
| `set(value) { field = ... }` | 自訂賦值時的處理邏輯（例如驗證、trim、大小寫轉換） |
| `get() { return ... }` | 自訂讀取時回傳的內容（可以做格式化，不影響實際儲存值） |
| `field` | 唯一能在 getter/setter 內代表底層儲存空間的關鍵字 |

### 最小可執行範例
```kotlin
class ToUpper {
    var str: String = ""
        set(value) {
            field = if (value.isEmpty()) "No data" else value.uppercase()
        }
        get() = "transfer data : $field"
}

fun main() {
    val d = ToUpper()
    d.str = "hello, Mary"
    println(d.str) // transfer data : HELLO, MARY
}
```

`Player` 類別是更完整的驗證範例：`id` 的 setter 檢查數值範圍、`email` 的 setter 檢查長度、`name` 的 getter 統一轉大寫，`get()=field+100` 則示範讀取時可以疊加運算，不影響實際存的值。

### 動機說明
真實系統的資料常常需要驗證（Email 格式、ID 範圍）、正規化（trim 空白、統一大小寫）。與其在每個呼叫端重複檢查，不如把規則封裝進屬性本身，這是**封裝（Encapsulation）**最直接的體現。

### 實務應用
Android／後端開發中，這種「setter 驗證」模式常見於 ViewModel 的欄位驗證，或 Entity 類別在存進資料庫前的格式清理（例如手機號碼去除空白、Email 轉小寫）。

### 實務上的替代方案
- 如果驗證邏輯複雜（跨多個欄位、要回傳錯誤訊息），業界更常用**獨立的驗證函式 / Validator 類別**或例外拋出（`require()`、`check()`），而不是把邏輯全塞進 setter，避免 setter 「看起來只是賦值，實際上卻會丟例外」造成呼叫端困惑。
- 值比較 vs 參考比較：一般 class 的 `==` 預設比較的是參考（記憶體位置相同才相等），若要比較「內容相同」，通常改用 `data class`（見下方建構子章節的延伸建議）。

---

## 3. 主建構子與次建構子（Constructor）

### 核心概念
- **主建構子**寫在類別名稱後面 `class Info(var name: String, var age: Int)`，是最常用、最簡潔的初始化方式。
- **次建構子**用 `constructor(...)` 宣告，必須直接或間接透過 `: this(...)` 呼叫到主建構子，這是 Kotlin 的硬性規定。
- 次建構子**不能**用 `var`/`val` 宣告參數（那是主建構子的專利）。
- `init {}` 區塊會在主建構子執行時依序執行，適合放初始化邏輯或驗證。

### 對照表
| 寫法 | 用途 |
|---|---|
| `class X(val a: Int)` | 主建構子，最簡潔，適合大多數情境 |
| `constructor(...) : this(...)` | 次建構子，提供「多種初始化方式」的彈性 |
| `init { ... }` | 主建構子執行流程中的初始化邏輯 |
| 參數預設值 `var b: Int = 0` | 現代 Kotlin 常用來**取代**多個次建構子 |

### 最小可執行範例（節錄自 InfoClass.kt）
```kotlin
class Info(var name: String, var age: Int) {
    var email = "ab@gmail.com"

    constructor(_name: String, _age: Int, _email: String) : this(name = _name, age = _age) {
        this.email = _email
    }

    fun dataPrint() = println("name=$name, age=$age, email=$email")
}
```
呼叫 `Info("John", 30, "john22@iot.com")` 時，流程是：先跑主建構子（設定 name、age、預設 email），再跑次建構子的 `init` 之後、`this.email=_email1` 才覆蓋 email。

### 常見誤區
- 誤以為次建構子可以獨立存在，其實它一定要鏈回主建構子，否則編譯錯誤。
- `CarInfo` 範例中，`constructor(_brand, _model) : this(_brand, _model, 2026, 30)` 這種多個次建構子疊加呼叫，容易讓人搞不清楚「到底哪個值最後生效」。閱讀時建議**由外往內追**，最先被呼叫的是最外層傳進來的參數。

### 動機說明
次建構子解決的是「同一個類別，希望依不同輸入資料組合都能建立物件」的需求（例如：有 email 就設 email，沒有就用預設值）。

### 實務上的替代方案
現代 Kotlin 更常用**主建構子 + 具名參數 + 預設值**取代多個次建構子，因為呼叫端可讀性更高、也不用背「哪個次建構子對應哪種情境」：
```kotlin
class Info(
    var name: String,
    var age: Int,
    var email: String = "ab@gmail.com",
    var phone: String = "123456789",
    var id: Int = 0
)
// 呼叫時：Info(name="John", age=30, email="john22@iot.com")
```
只有在「初始化邏輯本身很複雜、無法用預設值表達」時，才建議用次建構子。

---

## 4. 繼承基礎：`open` / `override`

### 核心概念
- Kotlin 類別**預設是 `final`**（不可被繼承），這跟 Java 相反，是刻意的安全設計，逼你明確宣告「這個類別/屬性/方法允許被覆寫」。
- 父類別要被繼承 → 類別本身要加 `open`。
- 父類別的方法/屬性要被子類別覆寫 → 該方法/屬性也要加 `open`，子類別用 `override`。
- `super.xxx()` 可以在子類別中呼叫父類別原本的實作（通常用來「疊加」而不是「取代」邏輯）。

### 對照表
| 修飾字 | 意義 |
|---|---|
| `open class` | 允許被繼承 |
| `open fun` / `open var` | 允許被子類別覆寫 |
| `override` | 子類別實際執行覆寫 |
| `super.xxx()` | 呼叫父類別原始實作 |

### 最小可執行範例（節錄自 InheritClass.kt）
```kotlin
open class PClass1(pName: String) {
    open var name = pName
    open fun show() = println("PClass name= $name")
}

class CClass1(pName: String, val age: Int) : PClass1(pName) {
    override var name: String = pName.uppercase()
    override fun show() {
        super.show()
        println("CClass name= $name, age= $age")
    }
}
```

### 常見誤區
- `PClass`／`CClass`（沒有 `1`）的版本中，`show()` **沒有** `open`，所以 `CClass` 只能新增自己的 `show1()`，無法覆寫 `show()`——這示範了「忘記加 open」會導致子類別無法覆寫的情境，是課堂上刻意做的對照組。
- 子類別建構子裡的參數名稱（如 `CClass(pname, page)`）和父類別建構子參數名稱重複，不代表它們是同一個變數，只是把值傳進去而已。

### 動機說明
繼承的目的是**共用共同行為、只客製差異部分**。強制 `open` 則是避免「不小心讓別人繼承並覆寫了你沒設計成可覆寫的邏輯」，這在多人協作的大型專案中能有效防止 bug。

---

## 5. 多層繼承與多型（Polymorphism）

### 核心概念
- Kotlin 允許多層繼承（`Game → CGame → CCGame`），每一層都可以再 `override`。
- **多型的關鍵**：宣告變數的型別是父類別，實際指向的是子類別物件時，呼叫方法會執行**子類別的版本**（動態綁定 / dynamic dispatch）。
- `super.dataPrint()` 在多層繼承中會呼叫**直接父類別**的版本，而不是最頂層。

### 最小可執行範例（節錄自 InheritClass.kt）
```kotlin
open class Game(val player: String, _level: Int) {
    open var level = _level
    open val score = 60
    open fun dataPrint() = println("Game player=$player, level=$level, score=$score")
}

open class CGame(player: String, score: Int) : Game(player, 10) {
    override var level = 5
    override var score = score
    override fun dataPrint() {
        super.dataPrint()
        println("CGame player=$player, level=$level, score=$score")
    }
}
```
執行流程：`var game: Game = CGame("BBB", 77)` → 呼叫 `game.dataPrint()` 時，因為是多型，實際跑的是 `CGame.dataPrint()`，內部又先呼叫 `super.dataPrint()` 印出 `Game` 那層的訊息，再印自己的。

### 常見誤區
- 容易誤以為 `super.dataPrint()` 會一路往上呼叫到最頂層祖先，實際上**只會呼叫直接父類別那一層**；如果 `CCGame` 呼叫 `super.dataPrint()`，跑的是 `CGame` 的版本，而 `CGame` 內部又呼叫了自己的 `super`，才間接印出 `Game` 的內容——是「一層層往上疊」，不是「一步跳到頂層」。

### 實務應用
多型是 Android 的 `RecyclerView.Adapter`、後端框架的 Controller 基底類別等設計的核心：定義統一介面（父類別方法），各自子類別各自實作細節，呼叫端完全不用管實際是哪個子類別。

---

## 6. 向上轉型（Upcasting）與 `is` 判斷

### 核心概念
- 子類別物件可以直接指派給父類別型別的變數，這叫**向上轉型（Upcasting）**，是安全、自動的，不需要 `as`。
- `as` 關鍵字用於**明確轉型**，例如把已知是子類別的父類型變數轉回子類別型別（Downcasting），若型別不符會丟 `ClassCastException`。
- `is` 用於執行期檢查「這個物件實際上是不是某個類別的實例」，常搭配 `when` 做分支處理。

### 最小可執行範例（節錄自 Class_3.kt）
```kotlin
fun checkClass(className: PClass) {
    when (className) {
        is CClass -> className.show1()
        is PClass1 -> className.show()
    }
}

fun printInfo(game: Game) {  // 參數型別宣告為父類別
    game.dataPrint()          // 但實際執行哪個版本由傳入的物件決定（多型）
}
```

### 對照表
| 語法 | 方向 | 安全性 |
|---|---|---|
| 子類別物件 → 父類別變數 | Upcasting | 永遠安全，自動完成 |
| `父類別變數 as 子類別` | Downcasting | 型別不符會拋例外，需自行確保正確 |
| `obj is 型別` | 型別檢查 | 回傳 Boolean，安全 |

### 常見誤區
- `as` 轉型失敗會直接讓程式崩潰（`ClassCastException`），業界更常搭配 `as?`（安全轉型，失敗回傳 `null`）而不是硬 `as`。

### 實務上的替代方案
如果你發現程式碼裡到處都要用 `is` 判斷型別再分支處理，這通常是一個訊號：**改用多型（把邏輯寫進各子類別的 override 方法）或改用 `sealed class` + `when`** 會更安全、更好維護。`sealed class` 的好處是編譯器會強制你處理「所有可能的子類別」，不像一般繼承的 `is` 判斷可能漏掉某個分支也不會報錯。

---

## 7. 例題章節：多型集合處理（NewCar.kt）

### 題目背景
設計一個 `Car` 開放類別，並衍生出 `OilCar`（燃油車，可加油）與 `ElectricCar`（電動車，可充電），最後把三種物件放進同一個 `List<Car>`，統一呼叫 `displayInfo()`。這是「多型在集合中的實務用法」的典型範例。

### 完整程式碼
```kotlin
open class Car(val brand: String, val model: String, val year: Int) {
    open fun displayInfo() {
        println("Car brand : $brand, model: $model, year: $year")
    }
}

class OilCar(_brand: String, _model: String, _year: Int) : Car(_brand, _model, _year) {
    fun oil(oilCap: Int, oilConsume: Int = 12) {
        println("$brand $model can drive ${oilCap * oilConsume} km")
    }
}

class ElectricCar(_brand: String, _model: String, _year: Int, _battery: Int) : Car(_brand, _model, _year) {
    var batteryCapability = _battery
    fun charge(amount: Int) {
        batteryCapability = (batteryCapability + amount).coerceAtMost(100)
        println("$brand $model charged to ${batteryCapability}")
    }
}

fun main() {
    val myCar = Car("Toyota", "RAV4", 2022)
    val oilCar = OilCar("BMW", "X3", 2025)
    val electricCar = ElectricCar("Tesla", "Model 3", 2026, 50)

    val carList = mutableListOf<Car>(myCar, oilCar, electricCar)
    carList.forEach { it.displayInfo() }
}
```

### 執行流程說明
1. 建立三種不同類型的物件，但存放進 `List<Car>` 時，**集合的型別統一是父類別 `Car`**——這是多型的實務意義：不需要為每種車寫一個 List。
2. `forEach { it.displayInfo() }` 逐一呼叫時，雖然變數型別是 `Car`，但因為 `displayInfo()` 是 `open`，實際執行的是各物件**自己（子類別未覆寫則沿用父類別）**的版本。
3. 這裡 `OilCar` 和 `ElectricCar` 都沒有覆寫 `displayInfo()`，所以三者列印的都是父類別 `Car` 的格式，但 `oil()` 和 `charge()` 是各自子類別獨有的方法，只能透過原本的 `oilCar`/`electricCar` 變數呼叫，不能透過 `Car` 型別的變數呼叫（除非用 `as` 轉型）。

### 預期輸出（節錄）
```
Car brand : Toyota, model: RAV4, year: 2022
Car brand : BMW, model: X3, year: 2025
Car brand : Tesla, model: Model 3, year: 2026
```

### 核心語法對照表
| 語法 | 這裡的作用 |
|---|---|
| `mutableListOf<Car>(...)` | 建立以父類別為型別的集合，可放入任何子類別物件 |
| `it.displayInfo()` | 集合遍歷時透過父類別介面統一呼叫，體現多型 |
| `coerceAtMost(100)` | 數值上限限制，避免電量超過 100 |

### 實務應用
這正是策略模式（Strategy Pattern）與多型集合的雛形，對應到 `ex_9.txt` 的 `PaymentMethod` 介面（`CreditCard`/`Cash`）——**用同一種父型別（介面或抽象類別）放進集合或當參數傳遞，讓呼叫端不用知道實際是哪個子類別**，這在訂單系統、支付系統、UI 元件渲染中非常常見。

### 實務上的替代方案
若各種車輛的差異行為（`oil()`、`charge()`）多到需要頻繁向下轉型才能呼叫，通常代表該用**介面（interface）定義共同能力**（例如 `interface Refuelable { fun refuel() }`），或直接把共同行為往上提到父類別，而不是各子類別各自長出不相干的方法後還要 `is`/`as` 才能用。

---

## 快速總結

```
Kotlin 物件導向重點
├── 屬性初始化
│   └── 沒預設值必須賦值，杜絕半初始化物件
├── Getter / Setter 客製化
│   ├── field 代表底層儲存值
│   └── 用於驗證、正規化（實務上複雜邏輯改用 Validator）
├── 建構子
│   ├── 主建構子：最常用，具名參數 + 預設值可取代多個次建構子
│   └── 次建構子：constructor(...) : this(...)，鏈回主建構子
├── 繼承
│   ├── 預設 final，需 open 才能被繼承 / 覆寫
│   └── override + super.xxx() 疊加父類別邏輯
├── 多型
│   ├── 父類別型別變數 → 動態綁定到子類別實作
│   └── 多層繼承時 super 只會呼叫直接父類別
├── 轉型
│   ├── Upcasting：子→父，安全自動
│   ├── Downcasting：as（risky）優先用 as?
│   └── is + when：型別分支，過度使用建議改 sealed class 或多型
└── 實務範例
    └── List<父類別> 存放多種子類別物件 → 統一介面呼叫（策略模式雛形）
```