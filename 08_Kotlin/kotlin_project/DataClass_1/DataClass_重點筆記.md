# Kotlin Data Class 重點筆記

---

## 1. 什麼是 Data Class？

- 使用 `data class` 關鍵字宣告，主要用來**儲存資料**。
- 編譯器會自動產生：`toString()`、`equals()`、`hashCode()`、`copy()`。
- 適合用來代替 Java 的 POJO (Plain Old Java Object)。

```kotlin
data class MyData(var name: String, var height: Float, var weight: Float) {
    var age: Int = 0  // ⚠️ 這行不在主建構子內
}
```

---

## 2. toString()

- 自動產生，輸出**主建構子內**所有屬性的值。
- `println(data1)` 等同 `println(data1.toString())`

```kotlin
val data1 = MyData("Mary", 173.2f, 54.5f)
data1.age = 20
println(data1)
// 輸出: MyData(name=Mary, height=173.2, weight=54.5)
// ⚠️ age=20 不會出現，因為 age 不在主建構子內
```

---

## 3. equals() 與比較運算子

| 運算子 / 方法 | 比較內容 | 說明 |
|---|---|---|
| `==` | 物件**內容** | 呼叫 `equals()`，只比對主建構子屬性 |
| `equals()` | 物件**內容** | 同上 |
| `===` | 物件**參考(記憶體位址)** | 是否為同一個實例 |

```kotlin
val data1 = MyData("Mary", 173.2f, 54.5f)
data1.age = 20

val data2 = MyData("Mary", 173.2f, 54.5f)
// data2.age = 0 (預設值)

println(data1 == data2)       // true  ← age 不參與比對
println(data1.equals(data2))  // true  ← 同上
println(data1 === data2)      // false ← 不同的物件實例
```

> ⚠️ **重點**：`equals()` 只比對**主建構子**的屬性，類別主體內的屬性（如 `age`）不參與比對。

---

## 4. 參考賦值 vs. Copy

### 4-1. 參考賦值（`val data3 = data1`）

- `data3` 和 `data1` **指向同一個物件**。
- 修改其中一個，另一個也會被影響。

```kotlin
val data3 = data1
println(data1 === data3)  // true ← 同一個物件

data1.name = "Bob"
println(data3)  // MyData(name=Bob, ...) ← 一起被修改
```

### 4-2. copy()（Shallow Copy 淺拷貝）

- `copy()` 建立一個**新的外層物件**，`===` 會是 `false`。
- 預設是 **Shallow Copy（淺拷貝）**，不等同 deep copy。

```kotlin
var data4 = data1.copy()
println(data4 == data1)   // true  ← 內容相同
println(data4 === data1)  // false ← 不同的物件實例

data4.name = "Lily"
println(data4 == data1)   // false ← data4 已修改
println(data4 === data1)  // false
```

---

## 5. copy() 是 Shallow Copy，不是 Deep Copy

| 欄位型別 | copy() 後修改 | 會影響原物件？ |
|---|---|---|
| `String`、`Float`、`Int` 等值型別 | 直接賦值 (`=`) | **不會** |
| `MutableList`、自訂可變物件 等參考型別 | 修改內部元素 (`add()` 等) | **會** |

```kotlin
data class User(val name: String, val tags: MutableList<String>)

val u1 = User("A", mutableListOf("x"))
val u2 = u1.copy()

u2.tags.add("y")
println(u1.tags)  // [x, y] ← 原物件被影響！(Shallow Copy)
```

### 解決方式：手動 Deep Copy

```kotlin
data class User(val name: String, val tags: MutableList<String>) {
    fun deepCopy() = User(name, tags.toMutableList())  // 對 list 另建新實例
}
```

---

## 6. 主建構子 vs. 類別主體屬性

```kotlin
data class MyData(
    var name: String,    // ✅ 主建構子內 → 參與 equals / toString / copy
    var height: Float,   // ✅ 主建構子內
    var weight: Float    // ✅ 主建構子內
) {
    var age: Int = 0     // ⚠️ 類別主體內 → 不參與 equals / toString / copy
}
```

| | 主建構子屬性 | 類別主體屬性 |
|---|---|---|
| `toString()` | ✅ 顯示 | ❌ 不顯示 |
| `equals()` / `==` | ✅ 比對 | ❌ 不比對 |
| `copy()` | ✅ 複製 | ❌ 不複製（使用預設值） |

> 💡 若希望 `age` 也參與上述行為，請移入主建構子：
> ```kotlin
> data class MyData(var name: String, var height: Float, var weight: Float, var age: Int = 0)
> ```

---

## 7. 例題：Student 管理系統

### 7-1. 資料模型 — `Student` data class

- 所有屬性全在**主建構子**內，均使用 `val`（不可變）。
- `id`、`name`、`age`、`grade` 皆參與 `equals()` 和 `toString()`。

```kotlin
data class Student(
    val id: Int,
    val name: String,
    val age: Int,
    val grade: String
)
```

---

### 7-2. 資料管理員 — `StudentManager` object

- 使用 `object` 宣告 **Singleton（單例）**，全程式只有一份實例。
- 以 `private val students = mutableListOf<Student>()` 儲存學生清單（外部無法直接存取）。
- 提供三個公開方法：`addStudent`、`showAllStudents`、`removeStudentById`。

```kotlin
object StudentManager {
    private val students = mutableListOf<Student>()

    // 新增學生
    fun addStudent(student: Student) {
        students.add(student)
    }

    // 顯示所有學生
    fun showAllStudents() {
        println("List all students")
        students.forEach {
            println("id: ${it.id}, name: ${it.name}, age: ${it.age}, grade: ${it.grade}")
        }
    }

    // 依 id 刪除學生
    fun removeStudentById(id: Int) {
        val removed = students.removeIf { it.id == id }
        if (removed)
            println("remove student id = $id")
        else
            println("id is wrong")
    }
}
```

> 💡 `object` 關鍵重點：
> - 不需要 `new` 或建構子，直接用 `StudentManager.方法名()` 呼叫。
> - 與 Java 的 `static` 工具類別類似，但更安全（天生執行緒安全）。

---

### 7-3. 使用範例與預期輸出

```kotlin
StudentManager.addStudent(Student(1001, "Mary", 15, "8"))
StudentManager.addStudent(Student(1002, "John", 16, "9"))
StudentManager.addStudent(Student(1003, "Bob",  17, "10"))
StudentManager.addStudent(Student(1004, "Lily", 18, "11"))

StudentManager.showAllStudents()
// List all students
// id: 1001, name: Mary, age: 15, grade: 8
// id: 1002, name: John, age: 16, grade: 9
// id: 1003, name: Bob,  age: 17, grade: 10
// id: 1004, name: Lily, age: 18, grade: 11

StudentManager.removeStudentById(1003)
// remove student id = 1003

StudentManager.showAllStudents()
// List all students
// id: 1001, name: Mary, age: 15, grade: 8
// id: 1002, name: John, age: 16, grade: 9
// id: 1004, name: Lily, age: 18, grade: 11  ← Bob 已被移除

StudentManager.removeStudentById(100)
// id is wrong
```

---

### 7-4. 核心概念對照

| 概念 | 本例用法 | 說明 |
|---|---|---|
| `data class` | `Student` | 純資料容器，自動產生 toString/equals |
| `object` | `StudentManager` | Singleton，管理 List 資料 |
| `mutableListOf` | `students` | 可新增/刪除的學生清單 |
| `removeIf { }` | 依 id 刪除 | Lambda 條件刪除，回傳 Boolean 是否有刪到 |
| `forEach { }` | 遍歷輸出 | 以 `it` 代表每個 Student |

---

## 8. 例題：Enum Class 與 when

### 8-1. 基本列舉 — `Direction`

- `enum class` 用來定義固定常數集合，適合方向、狀態、等級等有限選項。
- 你的程式定義了四個方向：`EAST`、`WEST`、`SOUTH`、`NORTH`。

```kotlin
enum class Direction {
    EAST, WEST, SOUTH, NORTH
}
```

---

### 8-2. 搭配 `when` 做分支處理

- `when(dir)` 可以直接比對 enum 成員，語意清楚。
- 目前四個分支都列出來，因此不需要 `else`。

```kotlin
fun move(dir: Direction) {
    when (dir) {
        Direction.NORTH -> println("Go to Top")
        Direction.SOUTH -> println("Go to Bottom")
        Direction.EAST -> println("Go to Right")
        Direction.WEST -> println("Go to Left")
    }
}
```

---

### 8-3. 帶參數的列舉 — `Day`

- enum 成員可以帶建構參數，你的範例用 `chinese` 保存中文名稱。

```kotlin
enum class Day(val chinese: String) {
    MONDAY("星期一"),
    TUESDAY("星期二"),
    WEDNESDAY("星期三")
}
```

---

### 8-4. 常用屬性：`name`、`ordinal`

- `name`：列舉常數名稱（字串）。
- `ordinal`：列舉索引（從 0 開始）。
- 自訂欄位：像 `today.chinese` 可直接讀取。

```kotlin
val today = Day.MONDAY
println(today)                 // MONDAY
println(today.name)            // MONDAY
println("index= ${today.ordinal}")
println("input= ${today.chinese}")
```

---

### 8-5. 核心概念對照

| 概念 | 用法 | 說明 |
|---|---|---|
| `enum class` | `Direction`, `Day` | 定義固定值集合 |
| `when` + enum | `when(dir)` | 依列舉值分支處理 |
| `name` | `dir.name` | 取得成員名稱字串 |
| `ordinal` | `dir.ordinal` | 取得成員索引（0-based） |
| 自訂參數 | `Day(... chinese ...)` | 每個列舉可攜帶額外資料 |

---

## 9. 快速總結

```
data class
 ├── 自動產生：toString / equals / hashCode / copy
 ├── == 比對內容（主建構子屬性）
 ├── === 比對物件記憶體位址
 ├── val x = obj        → 參考賦值，同一物件，互相影響
 └── val x = obj.copy() → 淺拷貝，新物件，值型別不連動，參考型別連動

object (Singleton)
 ├── 全程式只有一份實例
 ├── 直接用 類別名.方法() 呼叫
 └── 適合用來管理共用資料（如 List 管理員）

enum class
 ├── 定義固定常數集合（如 Direction / Day）
 ├── 可搭配 when 做清楚分支
 ├── name 取得名稱、ordinal 取得索引
 └── 可在 enum 建構子加入自訂欄位（如 chinese）
```