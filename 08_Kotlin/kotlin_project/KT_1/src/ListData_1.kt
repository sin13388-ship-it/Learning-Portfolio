/*MutableList Exercise*/
fun main() {
    var mlst1=mutableListOf<Int>() //empty list
    var mlst2=mutableListOf<Double>(50.2)
    var mlst3=mutableListOf(11,12,13,14,15)
    var mlst4=mutableListOf("Mary","John","Nancy")
    var mlst5=mutableListOf<Any>("Mary",50,162.3) //混合型資料型態

    //明確宣告
    var mlst6: MutableList<String> = mutableListOf("Mary","John","Nancy")
    var mlst7 : MutableList<Any> =mutableListOf("Mary",50,162.3)

    println(mlst1)
    println(mlst2)
    println(mlst3)
    println(mlst4)
    println(mlst5)

    //Add, delete, set
    println()
    mlst1.add(10)
    println(mlst1)
    mlst1.set(0,20)
    println(mlst1)
    mlst1[0]=30 //也可以用index的方式
    println(mlst1)

    //insert element
    mlst1.add(1,10)
    println(mlst1)

    //Add range
    mlst1.addAll(2,listOf(1,2,3))
    println(mlst1)

    //convert it to string
    println(mlst1.joinToString())

    //remove element and return state
    println(mlst3)
    println(mlst3.remove(0)) //會回傳boolean表示是否有成功
    println(mlst3)
    println(mlst3.remove(15)) //會回傳boolean表示是否有成功
    println(mlst3)

    //remove at
    println(mlst3)
    println(mlst3.removeAt(0)) //會回傳被移除的element
    println(mlst3)

    //travel elements
    println()
    for (data in mlst3)  //value
        print("$data, ")
    for (i in 0 until mlst3.size)  //from index
        print("${mlst3[i]}, ")

    //contains
    println("Is element '15' in list? : ${mlst3.contains(15)}")
    println("Are elements '12 and 14' in list? : ${mlst3.containsAll(listOf(12,14))}")

    //removeIf
        // 可以自己設定判斷條件
    println(mlst3)
    mlst3.removeIf {
        println(it)
       it *2 ==28 || it *3 ==36 //只要符合這個條件的都會被移掉
    }
    println(mlst3)
    //removeAll
    mlst3.clear()
    println(mlst3)

}

