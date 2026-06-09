
/*Set exercise*/
fun main() {

    //Integer Type
    var st1=setOf<Int>(11,22,33,44,44)
    println(st1)

    //String Type
    var st2=setOf<String>("AA","AA","BB","BB")
    println(st2)

    //Double, 明確宣告
    var st3 : Set<Double> =setOf<Double>()
    println(st3)
    //Any type
    var st4: Set<Any> =setOf("Mary",20,52.3)
    println(st4)

    //get length
    println()
    println(st2.size)
    println(st2.count())

    //search element and do something
    println("search element and do something")
    println(st1.elementAt(2))
    println(st1.elementAtOrNull(10))
    println(st1.elementAtOrNull(10)?: "Not found")
    println(st1.elementAtOrElse(10){-1}) //return generic結果
    println(st1.elementAtOrElse(10){"Not found"}) //return generic結果

    //travel
    println("travel")
    st2.forEach(){println(it)}
    println()
    st2.forEachIndexed { index, data ->  println("index= $index, value= $data") }

    // Find an element matching the specified condition
    println("Find an element matching the specified condition")
    println(st1)
    println(st1.find { it-> it >=30 })
    println(st1.findLast { it-> it >=30 })

    // Filter elements matching the specified condition
    println("Filter elements matching the specified condition")
    println(st1)
    println(st1.filter{ println(it); it >=30 }) //符合條件的全印出
    println(st1.filter{  it > 20 && it < 40 }) //符合條件的全印出

    //Nested list
    var st6 =setOf( st1.filter { it >= 30 }, listOf(1,2,3,4))
    println(st6)

    //plus(), minus()
    println("plus(), minus()")
    var mst1=mutableSetOf<Int>(1,1,2,2,3,4,5)

    var mst3 =mst1.plus(5)
    println(mst3)
    mst3=mst1.minus(2)
    println(mst3)

    println()
    var mst4 =mst1+6         //可以用 +/- 代替
    println(mst4)
    mst4 -=2
    println(mst4)

    //as a list or an array
    println("as a list or an array")
    var arr =st1.toIntArray()
    arr.forEach { print("$it, ") }
    println()
    var list=st1.filter{  it > 20 && it < 40 }.toMutableList()
    println(list)
    //can use index to get element from the list
    println(list[0])

    //list->set or set->list
    println("list->set or set->list")
    var mlist =mutableListOf<Int>(1,1,2,2,3,3,4,5)
    println(mlist)
    var mSet8=mlist.toMutableSet()
    println(mSet8)
    mlist=mSet8.toMutableList()
    println(mlist)

    println()
    var nameList=mutableListOf("AA","BB","CC","DD")
    println(nameList)
    var newName=nameList.toMutableSet()
    newName.add("AA") //語法糖，不會報錯，會自動去重
    println(newName)
    newName.add("DD")
    println(newName)
    nameList=newName.toMutableList()
    nameList.add("AA-1")
    println(nameList)

    //union, intersect, subtract
    println("union, intersect, subtract")
    var mst5= setOf("Mary", "John", "Lily", "Bob", "Nancy")
    var mst6 =setOf("Mary", "Leo",  "Bob", "Jack")
    println(mst5)
    println(mst6)
    var mst7=mst5.union(mst6).toMutableSet()
    println("mst7 (union) = ${mst7.joinToString()}")
    var mst8=mst5.intersect(mst6).toMutableSet()
    println("mst8 (intersect) = ${mst8.joinToString()}")
    var mst9=mst5.subtract(mst6).toMutableSet()
    println("mst9 (subtract), main : mst5 = ${mst9.joinToString()}")
    var mst10=mst6.subtract(mst5).toMutableSet()
    println("mst10 (subtract),  main : mst6 = ${mst10.joinToString()}")

}
