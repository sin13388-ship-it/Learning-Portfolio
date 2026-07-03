# Kotlin 檔案操作（File I/O）重點筆記
> 對應範例：`FileControl_1.kt`

---

## 1. `File` 物件與 `mkdir()`：建立資料夾

```kotlin
val newDir = File("C:\\Users\\User\\Documents\\kotlin_file_exercise")
val result = newDir.mkdir()
```

**動機說明**
`File()` 建立的只是「路徑的描述物件」，不代表磁碟上真的有這個檔案或資料夾。這個設計讓程式可以先在記憶體中組合、判斷路徑，再決定要不要真的建立實體檔案／資料夾，避免不必要的 I/O 動作。`mkdir()` 回傳 `Boolean`，代表「這次呼叫有沒有成功建立」，方便你在建立失敗時（例如上層目錄不存在、權限不足）做錯誤處理，而不是讓程式直接丟例外中斷。

**實務應用**
- Android/後端專案常需要在 App 第一次啟動時建立快取目錄、下載目錄、log 目錄。
- 上傳檔案的後端服務會依使用者 ID 動態建立子資料夾（例如 `/uploads/user_123/`）。

**實務上的替代方案**
- 若要建立多層資料夾（父目錄也不存在），業界更常用 `mkdirs()` 而非 `mkdir()`（`mkdir()` 遇到父目錄不存在會直接失敗）。
- 現代 Kotlin 專案（尤其是新版 JVM）也常用 `java.nio.file.Files.createDirectories(path)`，因為 `java.nio.file` API 的例外訊息更清楚、且能搭配 `Path` 做更安全的路徑組合，是 Java 官方後來主推的方向，`java.io.File` 屬於較舊的 API。

---

## 2. `apply` 建立檔案並初始化內容

```kotlin
var file = File("$newDir\\data1.txt").apply {
    createNewFile()
    writeText("Hello Mary \n")
    appendText("Good morning !\n")
    appendText("This is kotlin class. \n")
}
```

**動機說明**
`apply` 是作用域函數，特色是「回傳呼叫者本身（this）」。它的價值在於：建立物件後，常常需要連續對同一個物件做好幾個初始化動作，用 `apply` 可以把這些動作包成一個區塊，不必重複打 `file.xxx()`、`file.yyy()`，同時最後仍然拿到 `file` 這個變數本身，方便後續繼續使用。

**實務應用**
- 建立 View、建立設定物件（例如 `OkHttpClient.Builder().apply {...}`）時非常常見。
- 這裡用在「建立檔案 + 寫入初始內容」一氣呵成，程式碼可讀性比拆成四行更好。

**實務上的替代方案**
- 如果初始化動作只有一行，直接鏈式呼叫即可，不需要特地用 `apply`（過度使用作用域函數反而降低可讀性）。
- 若要區分「回傳 this」還是「回傳 lambda 結果」，team 常見規範是：**回傳物件本身 → `apply`／`also`**；**回傳運算結果 → `let`／`run`**。這是 Kotlin 官方風格指南建議的選用原則，寫作業或 code review 時可以順便記住。

---

## 3. 讀取檔案：`readText()` vs `readLines()`

```kotlin
var data = file.readText()
val lines = file.readLines().also { it.forEach { println("data= $it") } }
```

**動機說明**
`readText()` 一次把整個檔案讀成一個 `String`，適合檔案不大、想整份處理（例如整份丟去做字串比對）的情況；`readLines()` 則直接回傳 `List<String>`，每個元素是一行，適合你需要「逐行」處理資料（像 CSV、log）。這兩個 API 都幫你把底層的 buffer、換行判斷都封裝掉了，是 Kotlin 對 `File` 的擴充函數（extension function），比原生 Java 寫法簡潔很多。

**實務應用**
- 讀設定檔（`.properties`、`.json`）常用 `readText()` 再丟給 parser。
- 讀 log 檔、CSV 逐行分析常用 `readLines()`。

**實務上的替代方案**
- 檔案很大（例如上百 MB 的 log）時，`readText()` / `readLines()` 都會把整個檔案一次載入記憶體，容易 OOM。這時業界會改用 `File.forEachLine { line -> ... }` 或 `bufferedReader().useLines { ... }`，用 lazy sequence 逐行處理，不會一次把全部資料塞進記憶體。

---

## 4. `FileWriter` 寫入檔案（byte / char array / String 三種寫法）

```kotlin
var newFile = FileWriter("$newDir\\data2.txt", false)
newFile.use {
    it.write(0x31)          // 寫入單一字元的 unicode code point
    it.write(charArrayOf('H','e','l','l','o',...))  // 寫入 char array
    it.write("It is sunny day\n")                   // 寫入 String
}
```

**動機說明**
`FileWriter` 建構子的第二個參數（`append: Boolean`）是為了讓同一支程式碼可以重複使用同一個 API，卻能決定「每次都是全新寫入」還是「接續之前的內容」，這在 log 系統或需要保留歷史紀錄的場景非常重要。`write()` 之所以有多載（overload）可以吃 `Int`／`CharArray`／`String`，是因為底層資料來源本來就可能是位元組碼、字元陣列或字串，多載讓你不需要自己手動轉型。

**實務應用**
- Log 系統寫入時常用 `append = true`，確保重啟程式也不會蓋掉舊 log。
- 產生報表、匯出資料時常用 `append = false`（每次重新產生完整檔案）。

**實務上的替代方案**
- `FileWriter` 是字元導向（character stream），內部使用系統預設編碼，跨平台（尤其中英文混合）容易出現編碼不一致的問題。業界更常用 `File("path").bufferedWriter(Charsets.UTF_8)` 或 `OutputStreamWriter(FileOutputStream(...), Charsets.UTF_8)`，明確指定編碼，避免中文亂碼問題（這點對你的範例特別重要，因為程式裡有中文字串）。

---

## 5. `use{}`：自動關閉資源（相當於 try-with-resources）

**動機說明**
檔案、資料庫連線這類資源如果沒有正確關閉，會造成檔案鎖定或資源洩漏。`use{}` 是 Kotlin 對 `Closeable` 介面提供的擴充函數，會在 lambda 執行完（不論是否丟出例外）自動呼叫 `close()`，讓你不用手動寫 `try / finally`，也不會忘記關閉。

**實務應用**
- 幾乎所有牽涉到 `InputStream`、`OutputStream`、`Reader`、`Writer`、資料庫 `Connection` 的操作都應該包在 `use{}` 裡，這是 Kotlin 專案的標準寫法。

**實務上的替代方案**
- 沒有真正的「替代方案」，`use{}` 本身就是業界公認優於手寫 `try/finally` 的作法；唯一要注意的是巢狀多個資源時，可以用多層 `use{}` 或 Kotlin 的 `use` 搭配 `Pair`／多個 `use` 串接，保持每層都正確關閉。

---

## 6. `FileReader` 讀取檔案：`read()` vs `readLines()`

```kotlin
var chBuff = CharArray(50)
var len = 0
FileReader("$newDir\\data2.txt").use {
    len = it.read(chBuff)
}
```

**動機說明**
`read(CharArray)` 是比較底層的 API：它會嘗試把資料讀進你準備好的固定大小陣列，並回傳「實際讀到幾個字元」。這種寫法給你對 buffer 大小、讀取次數更精細的控制，但也代表你要自己處理「讀不完要不要迴圈再讀一次」的邏輯。相對地，前面看到的 `readLines()` 已經把這些細節都封裝好了。

**實務應用**
- 底層 API（`read(CharArray)`）常見於需要客製化緩衝策略的場景，例如串流處理、網路傳輸讀寫。
- 一般應用層讀取設定檔、文字檔，直接用 `readLines()` 或 `readText()` 即可，不需要自己管理 buffer。

**實務上的替代方案**
- 在教學情境下手動管理 `CharArray` buffer 很適合用來理解「串流讀取」的底層原理；但正式專案中，除非有效能或記憶體控制的明確需求，否則直接用 Kotlin 提供的 `readLines()` / `useLines()` 會更安全（不用擔心 buffer 太小截斷資料、也不用自己處理迴圈補讀）。

---

## 小結：這份範例涵蓋的核心觀念

| 觀念 | 對應 API |
|---|---|
| 建立資料夾 | `File.mkdir()` |
| 物件建立後鏈式初始化 | `apply` |
| 整份 / 逐行讀取（高階 API） | `readText()` / `readLines()` |
| 可控制 append 的寫入 | `FileWriter(path, append)` |
| 資源自動關閉 | `use {}` |
| 底層 buffer 讀取 | `FileReader.read(CharArray)` |

這份範例本身不是作業提交（沒有題目要求對照），所以我用整理筆記的方式呈現；如果之後有對應的作業題目要我核對是否符合要求，我會先逐項比對題目規格再給建議。