# **Kotlin 集合型別（Collections）重點筆記**

## **1. 列表基礎：MutableList 的建立與初始化**

### 核心概念
1. **MutableList 是有序、可重複的集合** — 支持索引存取，可隨時修改內容
2. **類型推斷 vs 明確宣告** — 類型推斷讓程式碼簡潔，明確宣告增強可讀性
3. **混合型資料（Any）允許多種類型混存** — 用 `mutableListOf<Any>()` 實現
4. **空列表必須明確指定類型** — `mutableListOf<Int>()` 才能編譯通過

### 宣告方式對照表

| 方式 | 語法 | 何時使用 |
|------|------|--------|
| 空列表 | `mutableListOf<Int>()` | 動態新增元素 |
| 初值推斷 | `mutableListOf(11,12,13)` | 類型明顯時簡化 |
| 初值指定 | `mutableListOf<Double>(50.2)` | 需要特定類型 |
| 混合型 | `mutableListOf<Any>("Mary",50,162.3)` | 存不同類型元素 |
| 明確宣告 | `var mlst: MutableList<String> = mutableListOf(...)` | 重視類型安全 |

### 最小可執行範例

```kotlin
fun main() {
    // 1. 建立不同類型的列表
    var mlst1 = mutableListOf<Int>()              // 空整數列表
    var mlst2 = mutableListOf("Mary", "John")     // 字符列表（類型推斷）
    var mlst3: MutableList<Any> = mutableListOf("Mary", 50, 162.3)  // 混合型
    
    println(mlst1)  // 輸出: []
    println(mlst2)  // 輸出: [Mary, John]
    println(mlst3)  // 輸出: [Mary, 50, 162.3]
}
```

### 常見誤區 & 注意事項

| 誤區 | 正確做法 | 解釋 |
|------|--------|------|
| `mutableListOf()` 不指定類型 | `mutableListOf<Int>()` | 空列表必須明確類型 |
| 混合型用 `mutableListOf<String>` | 用 `mutableListOf<Any>` | `Any` 是所有類型的父類 |
| `val` 與 `var` 選擇 | 可修改內容用 `var`，引用不變用 `val` | Mutable 指內容可變，不指引用 |

---

## **2. 列表操作：增加、修改、刪除**

### 核心概念
1. **新增方式有兩種：尾端 vs 指定位置** — `add()` 尾端，`add(index, 值)` 指定位置
2. **修改用 set() 或索引語法** — 兩者等價，`set(0, 新值)` 等同 `[0]=新值`
3. **刪除有多種方式回傳不同結果** — `remove()` 回傳 Boolean，`removeAt()` 回傳元素
4. **批量操作用 addAll() 和 clear()** — 提高效率

### 操作方法對照表

| 操作 | 方法 | 回傳值 | 範例 |
|------|------|-------|------|
| 尾端新增 | `add(元素)` | Boolean | `mlst.add(10)` |
| 指定位置插入 | `add(索引, 元素)` | Boolean | `mlst.add(1, 10)` |
| 批量新增 | `addAll(索引, 集合)` | Boolean | `mlst.addAll(2, listOf(1,2,3))` |
| 修改元素 | `set(索引, 值)` 或 `[索引]=值` | 原元素 | `mlst.set(0, 20)` 或 `mlst[0]=20` |
| 移除元素 | `remove(值)` | Boolean | `mlst.remove(10)` |
| 按索引移除 | `removeAt(索引)` | 被移除元素 | `mlst.removeAt(0)` |
| 條件移除 | `removeIf { 條件 }` | Boolean | `mlst.removeIf { it > 10 }` |
| 清空列表 | `clear()` | Unit | `mlst.clear()` |

### 最小可執行範例

```kotlin
fun main() {
    var mlst = mutableListOf<Int>()
    
    // 新增
    mlst.add(10)              // [10]
    mlst.add(20)              // [10, 20]
    mlst.add(1, 15)           // [10, 15, 20]
    
    // 修改
    mlst.set(0, 5)            // [5, 15, 20]
    mlst[1] = 25              // [5, 25, 20]
    
    // 刪除
    mlst.remove(25)           // [5, 20] 回傳 true
    mlst.removeAt(0)          // [20] 回傳被移除的元素 5
    
    // 批量
    mlst.addAll(listOf(30, 40))  // [20, 30, 40]
    mlst.clear()              // []
}
```

### 常見誤區 & 注意事項

| 誤區 | 正確做法 | 解釋 |
|------|--------|------|
| `remove()` 移除索引位置 | 用 `removeAt(索引)` | `remove()` 是移除值，不是索引 |
| `remove(0)` 移除第一個元素 | `removeAt(0)` 或 `remove(value)` | 0 是值，不會移除第一個位置 |
| `set()` 回傳新列表 | `set()` 回傳舊值，原列表被修改 | MutableList 是修改自身 |
| 不知道元素是否刪除 | 檢查 `remove()` 的 Boolean 回傳值 | 回傳 true 表示刪除成功 |

---

## **3. 列表查詢與遍歷**

### 核心概念
1. **兩種遍歷方式：值遍歷 vs 索引遍歷** — 根據需求選擇
2. **包含檢查有單個和批量版本** — `contains()` vs `containsAll()`
3. **字符串轉換用 joinToString()** — 方便輸出顯示
4. **索引查詢用 indexOf()** — 找到時回傳索引，找不到回傳 -1

### 查詢與遍歷方法表

| 方法 | 功能 | 回傳值 | 範例 |
|------|------|-------|------|
| `contains(值)` | 檢查是否包含元素 | Boolean | `mlst.contains(15)` |
| `containsAll(集合)` | 檢查是否包含所有元素 | Boolean | `mlst.containsAll(listOf(12,14))` |
| `indexOf(值)` | 找元素第一次出現的索引 | Int (-1 表示找不到) | `mlst.indexOf(15)` |
| `size` | 取得列表長度 | Int | `mlst.size` |
| `joinToString()` | 轉為字符串 | String | `mlst.joinToString()` |

### 遍歷方式對照表

| 遍歷方式 | 語法 | 用途 |
|---------|------|------|
| 值遍歷 | `for (data in list)` | 只需要值的場景 |
| 索引遍歷 | `for (i in 0 until list.size)` | 需要索引或位置的場景 |

### 最小可執行範例

```kotlin
fun main() {
    var mlst = mutableListOf(11, 12, 13, 14, 15)
    
    // 檢查
    println(mlst.contains(15))                    // true
    println(mlst.containsAll(listOf(12, 14)))     // true
    
    // 查詢
    println(mlst.indexOf(13))                     // 2
    println(mlst.size)                            // 5
    
    // 轉字符串
    println(mlst.joinToString())                  // 11,12,13,14,15
    println(mlst.joinToString(" - "))             // 11 - 12 - 13 - 14 - 15
    
    // 值遍歷
    for (data in mlst)
        print("$data, ")                          // 11, 12, 13, 14, 15,
    
    // 索引遍歷
    for (i in 0 until mlst.size)
        print("${mlst[i]}, ")                     // 11, 12, 13, 14, 15,
}
```

### 常見誤區 & 注意事項

| 誤區 | 正確做法 | 解釋 |
|------|--------|------|
| `indexOf()` 不存在時拋異常 | 檢查回傳值是否為 -1 | 不存在回傳 -1，不拋異常 |
| `joinToString()` 改變原列表 | `joinToString()` 只回傳字符串 | 原列表不變 |
| 同時需要值和索引用 `for (data in list)` | 用 `forEachIndexed` 或索引遍歷 | 值遍歷無法取得索引 |

---

## **4. 條件移除與高階操作：removeIf()**

### 核心概念
1. **removeIf() 用 Lambda 定義移除條件** — 符合條件的元素都被移除
2. **Lambda 中的 it 代表當前元素** — 簡潔語法
3. **條件可以是複雜的邏輯表達式** — 用 `||`（或）、`&&`（且）組合
4. **removeIf() 修改原列表，回傳 Boolean** — true 表示有元素被移除

### 最小可執行範例

```kotlin
fun main() {
    var mlst = mutableListOf(11, 12, 13, 14, 15)
    
    // 單一條件
    mlst.removeIf { it > 12 }                    // [11, 12]
    
    // 複雜條件：移除 it*2==28 或 it*3==36 的元素
    mlst = mutableListOf(11, 12, 13, 14, 15)
    mlst.removeIf { it * 2 == 28 || it * 3 == 36 }  // [11, 12, 15]
    
    // 驗證結果
    println(mlst)                                 // [11, 12, 15]
}
```

### 常見誤區 & 注意事項

| 誤區 | 正確做法 | 解釋 |
|------|--------|------|
| `removeIf()` 回傳被移除的元素 | `removeIf()` 回傳 Boolean | 若需要移除的元素，用 `filter()` |
| 不知道有沒有元素被移除 | 檢查回傳值的 Boolean | true 表示有元素被移除 |
| Lambda 中忘記回傳 Boolean | Lambda 最後一行自動成為回傳值 | `{ it > 12 }` 隱含 `return it > 12` |

---

## **5. 集合型別：Set 的無重複特性**

### 核心概念
1. **Set 自動去重，同時存不了重複元素** — `setOf(1,1,2,2)` 結果是 `{1, 2}`
2. **Set 是無序的，不支持索引存取** — 需轉換為 List 才能用 `[索引]`
3. **setOf() 是不可變，mutableSetOf() 可變** — 對應 List 的用法
4. **Set 支持集合運算：並集、交集、差集** — union、intersect、subtract

### Set 的特性對照表

| 特性 | List | Set |
|------|------|-----|
| 是否有序 | ✅ 有序 | ❌ 無序 |
| 是否可重複 | ✅ 可重複 | ❌ 不重複 |
| 是否支持索引 | ✅ 支持 | ❌ 不支持 |
| 查詢速度 | 較慢（O(n)） | 較快（O(1)） |
| 用途 | 有序資料、需要索引 | 去重、集合運算 |

### 建立 Set 的方式

```kotlin
fun main() {
    // 不可變 Set
    var st1 = setOf<Int>(11, 22, 33, 44, 44)          // {11, 22, 33, 44} 自動去重
    var st2 = setOf<String>("AA", "AA", "BB", "BB")   // {AA, BB} 自動去重
    var st3: Set<Double> = setOf<Double>()            // {} 明確宣告空 Set
    var st4: Set<Any> = setOf("Mary", 20, 52.3)       // {Mary, 20, 52.3} 混合型
    
    // 可變 Set
    var mst1 = mutableSetOf<Int>(1, 1, 2, 2, 3, 4, 5) // {1, 2, 3, 4, 5}
}
```

### 最小可執行範例

```kotlin
fun main() {
    var st1 = setOf<Int>(11, 22, 33, 44, 44)  // {11, 22, 33, 44}
    println(st1)                              // [11, 22, 33, 44]
    
    // 長度
    println(st1.size)                         // 4
    println(st1.count())                      // 4
}
```

### 常見誤區 & 注意事項

| 誤區 | 正確做法 | 解釋 |
|------|--------|------|
| Set 用 `[索引]` 取值 | 轉為 List：`st.toList()[0]` | Set 無序，不支持索引 |
| 不知道重複元素被去掉 | 檢查 `size` 和原數據大小比較 | Set 自動去重，無警告 |
| 建立空 Set 不指定類型 | `setOf<Int>()` | 否則編譯器無法推斷類型 |

---

## **6. Set 查詢：按位置、按條件**

### 核心概念
1. **elementAt() 按位置查詢** — Set 無序，此操作結果不可靠
2. **elementAtOrNull() 安全版本** — 越界回傳 null
3. **elementAtOrElse() 提供預設值** — 越界回傳自定義預設值
4. **find() 和 findLast() 按條件查詢** — 回傳第一個/最後一個符合的元素
5. **filter() 按條件批量查詢** — 回傳所有符合條件的元素列表

### Set 查詢方法表

| 方法 | 功能 | 越界行為 | 回傳值 |
|------|------|--------|-------|
| `elementAt(索引)` | 按位置取元素 | 拋異常 | 元素 |
| `elementAtOrNull(索引)` | 安全版 `elementAt()` | 回傳 null | 元素或 null |
| `elementAtOrElse(索引) {預設值}` | 指定預設值 | 回傳預設值 | 元素或預設值 |
| `find { 條件 }` | 找第一個符合 | 不存在回傳 null | 元素或 null |
| `findLast { 條件 }` | 找最後一個符合 | 不存在回傳 null | 元素或 null |
| `filter { 條件 }` | 找所有符合 | 回傳空列表 | 列表 |

### 最小可執行範例

```kotlin
fun main() {
    var st1 = setOf<Int>(11, 22, 33, 44)
    
    // elementAt 系列
    println(st1.elementAt(2))                      // 某個元素（Set無序）
    println(st1.elementAtOrNull(10))               // null
    println(st1.elementAtOrNull(10) ?: "Not found") // Not found
    println(st1.elementAtOrElse(10) { -1 })        // -1
    println(st1.elementAtOrElse(10) { "Not found" }) // Not found
    
    // find 系列
    println(st1.find { it >= 30 })                 // 33 或 44（第一個 ≥30）
    println(st1.findLast { it >= 30 })             // 44 或 33（最後一個 ≥30）
    
    // filter 系列
    println(st1.filter { it > 20 && it < 40 })     // [22, 33]
}
```

### 常見誤區 & 注意事項

| 誤區 | 正確做法 | 解釋 |
|------|--------|------|
| Set 用 `elementAt()` 有序取值 | Set 無序，索引位置無意義 | 應先轉 List 再索引取值 |
| `find()` 不存在時拋異常 | `find()` 回傳 null，不拋異常 | 用 Elvis 運算子 `?: ` 處理 |
| `filter()` 回傳 Set | `filter()` 回傳 List | 若需 Set 用 `.toSet()` |
| `elementAtOrElse()` 的回傳值類型 | Lambda 回傳值決定回傳類型 | `{-1}` 回傳 Int，`{"Not found"}` 回傳 String |

---

## **7. Set 遍歷與集合運算**

### 核心概念
1. **forEach() 遍歷所有元素** — 無索引版本
2. **forEachIndexed() 帶索引的遍歷** — 注意 Set 無序
3. **union() 並集** — 合併兩個集合，去重
4. **intersect() 交集** — 找兩個集合的共有元素
5. **subtract() 差集** — A 有但 B 沒有的元素

### 遍歷方法表

| 方法 | 功能 | 備註 |
|------|------|------|
| `forEach() { println(it) }` | 遍歷元素 | Set 無序，順序不固定 |
| `forEachIndexed { index, data -> ... }` | 帶索引遍歷 | 索引是遍歷順序，非元素位置 |

### 集合運算表

| 運算 | 方法 | 回傳值 | 範例 |
|------|------|-------|------|
| 並集 | `union(集合)` | Set | `{1,2} ∪ {2,3}` = `{1,2,3}` |
| 交集 | `intersect(集合)` | Set | `{1,2} ∩ {2,3}` = `{2}` |
| 差集 | `subtract(集合)` | Set | `{1,2} - {2,3}` = `{1}` |

### 最小可執行範例

```kotlin
fun main() {
    var st2 = setOf<String>("AA", "BB", "CC")
    
    // 遍歷
    st2.forEach() { println(it) }
    st2.forEachIndexed { index, data -> 
        println("index= $index, value= $data") 
    }
    
    // 集合運算
    var mst5 = setOf("Mary", "John", "Lily", "Bob", "Nancy")
    var mst6 = setOf("Mary", "Leo", "Bob", "Jack")
    
    var mst7 = mst5.union(mst6)               // {Mary, John, Lily, Bob, Nancy, Leo, Jack}
    var mst8 = mst5.intersect(mst6)           // {Mary, Bob}
    var mst9 = mst5.subtract(mst6)            // {John, Lily, Nancy}
    var mst10 = mst6.subtract(mst5)           // {Leo, Jack}
    
    println("union = ${mst7.joinToString()}")
    println("intersect = ${mst8.joinToString()}")
    println("subtract(mst5) = ${mst9.joinToString()}")
    println("subtract(mst6) = ${mst10.joinToString()}")
}
```

### 常見誤區 & 注意事項

| 誤區 | 正確做法 | 解釋 |
|------|--------|------|
| `union()` 回傳 MutableSet | `union()` 回傳 Set，需 `.toMutableSet()` | 不可變集合返回 Set |
| 差集的順序弄反 | A.subtract(B) 是 A 有但 B 沒有 | B.subtract(A) 結果不同 |
| 集合運算結果是列表 | `toMutableSet()` 或 `toSet()` 轉型 | 若需 Set 型別要明確轉換 |

---

## **8. Set 與 List 互轉：去重的實務應用**

### 核心概念
1. **List → Set：自動去重** — `list.toSet()` 或 `list.toMutableSet()`
2. **Set → List：轉為可索引** — `set.toList()` 或 `set.toMutableList()`
3. **Set.add() 重複元素自動忽略** — 不拋異常，無警告
4. **類型轉換的效率權衡** — 去重的代價是遍歷整個集合

### 最小可執行範例

```kotlin
fun main() {
    // List → Set（去重）
    var mlist = mutableListOf<Int>(1, 1, 2, 2, 3, 3, 4, 5)
    println(mlist)                                  // [1, 1, 2, 2, 3, 3, 4, 5]
    
    var mSet = mlist.toMutableSet()
    println(mSet)                                   // [1, 2, 3, 4, 5]
    
    // Set → List（可索引）
    mlist = mSet.toMutableList()
    println(mlist)                                  // [1, 2, 3, 4, 5]
    println(mlist[0])                               // 1
    
    // Set 去重特性
    var nameList = mutableListOf("AA", "BB", "CC", "DD")
    var newName = nameList.toMutableSet()
    newName.add("AA")                               // 不會報錯，自動去重
    println(newName)                                // {AA, BB, CC, DD}
    
    newName.add("EE")                               // 新元素
    println(newName)                                // {AA, BB, CC, DD, EE}
    
    nameList = newName.toMutableList()
    println(nameList)                               // [AA, BB, CC, DD, EE]
}
```

### 常見誤區 & 注意事項

| 誤區 | 正確做法 | 解釋 |
|------|--------|------|
| Set.add() 重複時拋異常 | Set.add() 自動忽略重複，回傳 false | 不會報錯，無異常 |
| List.toSet() 改變原列表 | `toSet()` 回傳新 Set，原 List 不變 | 原列表保持不變 |
| 轉換後無法索引 | `set.toList()[0]` 或 `set.toMutableList()` | Set 無法直接索引 |

---

## **9. 對應表型別：Map 的建立與初始化**

### 核心概念
1. **Map 是鍵值對結構，key 無序不重複** — 類似字典
2. **兩種建立方式：Pair vs to 語法糖** — `to` 更簡潔
3. **mapOf() 不可變，mutableMapOf() 可變** — 對應 List 和 Set
4. **Key 的類型可混合** — `Map<Any, String>` 但通常同型

### Map 建立方式對照表

| 方式 | 語法 | 用途 |
|------|------|------|
| 空 Map | `mapOf<String, Int>()` | 無初值 |
| 用 Pair | `mapOf(Pair("Mary", 62.4), Pair("John", 58.6))` | 明確表示鍵值對 |
| 用 to（推薦） | `mapOf("Mary" to 62.4, "John" to 58.6)` | 語法糖，更簡潔 |
| 明確宣告 | `var map: Map<String, Int> = mapOf(...)` | 重視類型安全 |
| 混合 Key | `mapOf(1 to "Leo", 15 to "Joanna")` | Key 可不同型別 |

### 最小可執行範例

```kotlin
fun main() {
    // 不可變 Map
    var map2 = mapOf<String, Double>(
        Pair("Mary", 62.4), 
        Pair("John", 58.6)
    )
    var map3 = mapOf(1 to "Leo", 15 to "Joanna", 6 to "Brown")
    var map4: Map<String, Int> = mapOf(
        "Apple" to 10, 
        "Banana" to 20, 
        "Cherry" to 80
    )
    
    // 可變 Map
    var stud1 = mutableMapOf<String, String>(
        "name" to "Mary", 
        "email" to "mary@iot.com", 
        "phone" to "1111"
    )
    
    println(map4)      // {Apple=10, Banana=20, Cherry=80}
    println(stud1)     // {name=Mary, email=mary@iot.com, phone=1111}
}
```

### 常見誤區 & 注意事項

| 誤區 | 正確做法 | 解釋 |
|------|--------|------|
| `Pair()` 和 `to` 混用 | 兩種都可用，`to` 更簡潔 | 語意上等價，選擇偏好 |
| 空 Map 不指定類型 | `mapOf<String, Int>()` | 否則編譯器無法推斷類型 |
| Key 重複時不會報錯 | 後面的值會覆蓋前面的值 | `mapOf("a" to 1, "a" to 2)` 結果是 `{a=2}` |

---

## **10. Map 取值：安全 vs 非安全**

### 核心概念
1. **三種取值方式有不同安全性** — `[]` 和 `get()` 回傳 null，`getValue()` 拋異常
2. **`[key]` 和 `get(key)` 等價** — 都是安全取值
3. **getValue() 用於確定 key 存在的場景** — 否則拋 NoSuchElementException
4. **Elvis 運算子 `?: ` 提供預設值** — 安全且簡潔

### Map 取值方法表

| 方法 | 語法 | Key 不存在 | 用途 |
|------|------|-----------|------|
| 索引取法 | `map[key]` | 回傳 null | 最常用，簡潔 |
| get 方法 | `map.get(key)` | 回傳 null | 與 `[key]` 等價 |
| getValue 方法 | `map.getValue(key)` | 拋異常 | 確定 key 一定存在 |
| Elvis 運算子 | `map[key] ?: 預設值` | 回傳預設值 | 安全且提供默認 |

### 最小可執行範例

```kotlin
fun main() {
    var map2 = mapOf<String, Double>(
        "Mary" to 62.4, 
        "John" to 58.6, 
        "Nancy" to 50.2
    )
    
    // 安全取值
    println(map2["Mary"])                          // 62.4
    println(map2["Mary2"])                         // null
    println(map2["Mary2"] ?: "Not Found")          // Not Found
    
    // get() 與 [] 等價
    println(map2.get("Mary"))                      // 62.4
    println(map2.get("Mary2") ?: "Not Found")      // Not Found
    
    // getValue() - key 必須存在
    println(map2.getValue("Nancy"))                // 50.2
    // println(map2.getValue("Unknown"))           // 拋異常！不執行
}
```

### 常見誤區 & 注意事項

| 誤區 | 正確做法 | 解釋 |
|------|--------|------|
| 用 `getValue()` 處理未知 key | 用 `[key] ?: 預設值` | `getValue()` 會拋異常 |
| 不知道取值是否成功 | 檢查結果是否為 null | `[key]` 和 `get()` 回傳 null |
| Elvis 運算子使用錯誤 | `map[key] ?: 預設值` | `?:` 前面是 nullable，後面是預設 |

---

## **11. Map 的鍵與值：keys、values、entries**

### 核心概念
1. **keys 是 Set 型別** — 無序、不重複
2. **values 是 Collection 型別** — 可重複
3. **遍歷 Map 時用 data.key 和 data.value** — data 是 Map.Entry 物件
4. **forEach() 可用 Lambda 接收 key 和 value** — 最簡潔的遍歷方式

### Map 的鍵值提取表

| 屬性/方法 | 回傳型別 | 內容 | 用途 |
|----------|--------|------|------|
| `keys` | Set | 所有鍵 | 檢查 key 是否存在 |
| `values` | Collection | 所有值 | 檢查 value 是否存在 |
| `values.toList()` | List | 所有值轉為列表 | 需要索引存取 |

### 最小可執行範例

```kotlin
fun main() {
    var map4: Map<String, Int> = mapOf(
        "Apple" to 10, 
        "Banana" to 20, 
        "Cherry" to 80
    )
    
    // 取鍵和值
    val keys = map4.keys
    println(keys)                                  // [Apple, Banana, Cherry]
    
    val values: Collection<Int> = map4.values
    println(values)                                // [10, 20, 80]
    
    val values2: List<Int> = map4.values.toList()
    println(values2)                               // [10, 20, 80]
    
    // 遍歷方式 1：用 for 和 data.key、data.value
    for (data in map4) {
        println("key = ${data.key}, value= ${data.value}")
    }
    
    // 遍歷方式 2：forEach Lambda
    map4.forEach { key, v -> 
        println("key = ${key}, value= ${v}") 
    }
}
```

### 常見誤區 & 注意事項

| 誤區 | 正確做法 | 解釋 |
|------|--------|------|
| `values` 可用索引直接取值 | `values.toList()[0]` | `values` 是 Collection，需轉 List |
| 遍歷時 `data.value` 不存在 | `data.key` 和 `data.value` | data 是 Map.Entry，有 key 和 value 屬性 |
| `keys` 回傳型別是 List | `keys` 回傳 Set（無序不重複） | 需要有序要轉 List |

---

## **12. Map 包含檢查**

### 核心概念
1. **contains() 檢查 key 或 value**（較少用） — 結果可能不直觀
2. **containsKey() 檢查是否有該鍵** — 最常用
3. **containsValue() 檢查是否有該值** — 用於反查
4. **建議用 containsKey() 代替 contains()** — 意圖明確

### Map 包含檢查表

| 方法 | 檢查對象 | 回傳值 | 備註 |
|------|--------|-------|------|
| `contains(key)` | Key | Boolean | 容易混淆，不推薦 |
| `containsKey(key)` | Key | Boolean | 推薦使用，意圖明確 |
| `containsValue(value)` | Value | Boolean | 反查數值 |

### 最小可執行範例

```kotlin
fun main() {
    var map4: Map<String, Int> = mapOf(
        "Apple" to 10, 
        "Banana" to 20, 
        "Cherry" to 80
    )
    
    // 檢查 key
    println(map4.contains("Apple"))                // true
    println(map4.containsKey("Pear"))              // false
    
    // 檢查 value
    println(map4.containsValue(80))                // true
    println(map4.containsValue(100))               // false
}
```

### 常見誤區 & 注意事項

| 誤區 | 正確做法 | 解釋 |
|------|--------|------|
| 用 `contains()` 檢查 key | 用 `containsKey()` | `contains()` 也能檢查但容易混淆 |
| 忘記檢查 key 是否存在直接取值 | 先用 `containsKey()` 或用 Elvis 運算子 | 無必要多一步檢查，用 `?: ` 更簡潔 |

---

## **例題章節：學生資料管理系統**

### 題目背景
你需要建立一個學生資料管理系統，輸入多個學生的姓名、ID、年齡和電子郵件，存儲在 `List<Map<String, Any>>` 結構中。這練習結合了 List、Map、for 迴圈和型別轉換。

### 完整程式碼

```kotlin
fun main() {
    // 宣告四個平行陣列存儲學生數據
    val stName = arrayOf("Mary", "John", "Jack", "AAA")
    val stId = arrayOf(100, 101, 102, 103)
    val stAge = arrayOf(20, 21, 22, 23)
    val stEmail = arrayOf(
        "mary@iot.com", 
        "john@iot.com", 
        "jack@iot.com", 
        "aaa@iot.com"
    )
    
    // 建立存儲結構：List<MutableMap<String, Any>>
    var stList = mutableListOf<MutableMap<String, Any>>()
    
    // 迴圈遍歷數組，建立每個學生的 Map 物件
    for (i in 0 until stName.size) {
        // 為每個學生初始化 Map 物件
        val data = mutableMapOf<String, Any>()
        
        // 放入學生資訊
        data.put("name", stName[i])
        data.put("ID", stId[i])
        data.put("Age", stAge[i])
        data.put("stEmail", stEmail[i])
        
        // 將該學生 Map 加入列表
        stList.add(data)
    }
    
    // 打印整個學生列表
    println(stList)
}
```

### 執行流程說明

```
步驟 1: 宣告四個平行陣列
  stName = ["Mary", "John", "Jack", "AAA"]
  stId = [100, 101, 102, 103]
  stAge = [20, 21, 22, 23]
  stEmail = ["mary@iot.com", "john@iot.com", "jack@iot.com", "aaa@iot.com"]

步驟 2: 建立空 List<MutableMap<String, Any>>
  stList = []

步驟 3: 迴圈 i=0
  data = {name=Mary, ID=100, Age=20, stEmail=mary@iot.com}
  stList.add(data)
  stList = [{name=Mary, ID=100, Age=20, stEmail=mary@iot.com}]

步驟 4: 迴圈 i=1
  data = {name=John, ID=101, Age=21, stEmail=john@iot.com}
  stList.add(data)
  stList = [{...Mary...}, {name=John, ID=101, Age=21, stEmail=john@iot.com}]

步驟 5: 迴圈 i=2, i=3 重複上述過程

步驟 6: 打印整個列表
  輸出完整的學生資訊集合
```

### 預期輸出

```
[{name=Mary, ID=100, Age=20, stEmail=mary@iot.com}, 
 {name=John, ID=101, Age=21, stEmail=john@iot.com}, 
 {name=Jack, ID=102, Age=22, stEmail=jack@iot.com}, 
 {name=AAA, ID=103, Age=23, stEmail=aaa@iot.com}]
```

### 核心語法對照表

| 語法 | 說明 |
|------|------|
| `arrayOf(...)` | 建立不可變陣列 |
| `stName.size` | 取陣列大小 |
| `0 until stName.size` | 迴圈範圍：0 到 size-1 |
| `mutableListOf<MutableMap<String, Any>>()` | 建立可變列表，元素是可變 Map |
| `mutableMapOf<String, Any>()` | 建立可變 Map，值為混合型 |
| `data.put("key", 值)` | 向 Map 加入鍵值對 |
| `stList.add(data)` | 向列表加入元素 |

### 進階應用：查詢和遍歷

```kotlin
fun main() {
    // ... 前面的建立程式碼省略 ...
    
    // 遍歷打印每個學生
    for (student in stList) {
        println("姓名: ${student["name"]}")
        println("ID: ${student["ID"]}")
        println("年齡: ${student["Age"]}")
        println("郵箱: ${student["stEmail"]}")
        println("---")
    }
    
    // 查詢特定學生（第一個）
    val firstStudent = stList[0]
    println("第一個學生: ${firstStudent["name"]}")
    
    // 過濾年齡 > 21 的學生
    val filteredStudents = stList.filter { 
        (it["Age"] as Int) > 21 
    }
    println("年齡 > 21 的學生數: ${filteredStudents.size}")
}
```

---

## **13. 集合輸入與邊界檢查：實務練習**

### 題目背景
編寫一個互動式程式，讓使用者輸入若干整數到列表中（輸入 -1 時停止），再輸入一個新數字和目標插入位置，程式驗證位置有效性後插入。

### 完整程式碼

```kotlin
fun main() {
    // 步驟 1：動態輸入數字
    var index: Int = 1
    var mlst1 = mutableListOf<Int>()
    
    while (true) {
        println("Enter $index number :")
        var v = readln().toIntOrNull() ?: 0
        if (v == -1) break  // -1 結束輸入
        mlst1.add(v)
        index++
    }
    println(mlst1)
    
    // 步驟 2：輸入要插入的數字
    println("Input insert data")
    var v = readln().toIntOrNull() ?: 0
    
    // 步驟 3：輸入目標索引位置
    println("Input target index")
    index = readln().toIntOrNull() ?: 0
    
    // 步驟 4：驗證位置有效性並插入
    var lastindex = mlst1.indexOf(mlst1.last())  // 取得最後索引
    
    if (index >= 0 && index <= lastindex) {
        mlst1.add(index, v)
        println(mlst1)
    } else {
        println("Invalid position")
    }
}
```

### 執行流程示例

```
輸入階段：
  Enter 1 number : 10
  Enter 2 number : 20
  Enter 3 number : 30
  Enter 4 number : -1
  [10, 20, 30]

插入階段：
  Input insert data
  25
  Input target index
  1
  
  驗證：lastindex = mlst1.indexOf(mlst1.last()) = indexOf(30) = 2
       1 >= 0 && 1 <= 2 ? true → 有效
  結果：mlst1.add(1, 25) → [10, 25, 20, 30]
  
  或輸入無效位置：
  Input target index
  5
  
  驗證：5 >= 0 && 5 <= 2 ? false → 無效
  輸出：Invalid position
```

### 核心語法對照表

| 語法 | 說明 |
|------|------|
| `readln()` | 讀取使用者輸入的字符串 |
| `toIntOrNull()` | 將字符串轉為 Int，失敗回傳 null |
| `?: 0` | Elvis 運算子，null 時預設值 0 |
| `mlst1.last()` | 取得最後一個元素 |
| `indexOf(元素)` | 取得元素的索引位置 |
| `mlst1.add(index, 值)` | 在指定位置插入 |

### 常見誤區 & 注意事項

| 誤區 | 正確做法 | 解釋 |
|------|--------|------|
| `toInt()` 無效輸入時拋異常 | 用 `toIntOrNull() ?: 預設值` | 安全轉換，失敗不拋異常 |
| 不驗證位置直接插入 | 用 `if (index >= 0 && index <= lastindex)` | 防止越界 |
| `indexOf()` 找不到時回傳 -1 | 檢查回傳值，不用於索引直接操作 | -1 可能造成負索引問題 |
| 輸入 -1 後還要插入嗎 | 先停止輸入，再輸入插入數據 | 邏輯上分兩個階段 |

---

## **快速總結**

```
Kotlin 集合型別

├─ List（有序、可重複、支持索引）
│  ├─ 宣告：mutableListOf<T>()
│  ├─ 操作：add() / remove() / set() / clear()
│  ├─ 查詢：contains() / indexOf() / joinToString()
│  ├─ 遍歷：for (data in list) / forEachIndexed
│  └─ 高階：filter {} / removeIf {} / find {}
│
├─ Set（無序、不重複、無索引）
│  ├─ 宣告：setOf<T>() / mutableSetOf<T>()
│  ├─ 特性：自動去重，Set.add() 重複不報錯
│  ├─ 查詢：elementAt() / find {} / filter {}
│  ├─ 遍歷：forEach() / forEachIndexed
│  ├─ 運算：union() / intersect() / subtract()
│  └─ 轉換：toList() / toMutableList()
│
└─ Map（鍵值對、Key 無序不重複、Value 可重複）
   ├─ 宣告：mapOf() / mutableMapOf()
   ├─ 語法：Pair("key", value) / "key" to value
   ├─ 取值：map[key] / get(key) / getValue(key)
   ├─ 安全：map[key] ?: 預設值
   ├─ 檢查：containsKey() / containsValue()
   ├─ 屬性：keys / values
   └─ 遍歷：forEach { key, value } / for (data in map)

├─ 型別轉換
│  ├─ List ↔ Set：toMutableSet() / toMutableList()
│  ├─ List → Array：toIntArray()
│  └─ 集合 → String：joinToString()

└─ 常用組合
   ├─ List<Map<String, Any>>：複雜資料結構
   ├─ 輸入驗證：toIntOrNull() ?: 預設值
   └─ 邊界檢查：if (index >= 0 && index <= size-1)
```

---

## **學習路線建議**

1. **第 1~3 章（基礎）** → 掌握 List 的建立、新增、刪除、查詢
2. **第 4 章（高階）** → 理解 Lambda 和條件操作 `removeIf()`
3. **第 5~7 章（Set）** → 理解無序、不重複、集合運算
4. **第 8 章（互轉）** → 實務應用：何時用 List，何時用 Set
5. **第 9~12 章（Map）** → 掌握鍵值對、取值安全性、遍歷
6. **例題 1（學生系統）** → 綜合 List + Map 的複雜結構
7. **例題 2（輸入插入）** → 邊界檢查、使用者輸入驗證

---

