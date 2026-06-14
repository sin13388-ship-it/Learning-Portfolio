/*Array exercise*/
fun main() {
    //Array 宣告型式

    /*宣告無初始值的陣列*/
    var arr1: IntArray //此時還未初始化，因此需要初始化
    var arr2= IntArray(5)
    var arr3= emptyArray<Int>()
    println(arr3.size)
    arr3+=5 //可以用'+'新增元素
    println("${arr3.size}")
    arr3.forEach { println(it) }
    arr1= IntArray(5) //初始化

    /*宣告有初始值的陣列*/
    var arr4=intArrayOf(34,12,5,67)
    var arr5: IntArray=intArrayOf(34,12,5,67)
    var arr6 =IntArray(5){it} //initialized (ranging from 0 to 4)
    var arr7 = IntArray(5){10} //以數值10初始化，5個元素的每個素質

    var arr9=arr5+arr4 //重新指派

    var arr8=arr4 //將arr4 指向arr8
    arr4[0]=2 //改變裡面的值，arr8會跟著改變
    arr4.forEach { print("$it \t") }
    println()
    arr8.forEach { print("$it \t") }
    println()

    arr4+=2 //創造新物件並重新指派（變數指針換人）
    arr4.forEach { print("$it \t") }
    println()
    arr8.forEach { print("$it \t") }
    println()

    //使用自動推論來初始化陣列(泛型)
    var arr10:Array<String> = arrayOf("Mary","John","Lily")
    var arr11=arrayOf<String>("Mary","John","Lily") //型別推論
    var arr12=arrayOf("Mary","John","Lily") //型別推論

    //使用Array 類別來宣告陣列
    /* syntax: var/val name= Array<T>(elements size, {logic for initializing}) */
    var arr13= Array<Double>(5,{ v-> v*1.2}) //索引位置v * 1.2
    var arr14= Array(5){it}
    var arr15=arrayOf<Int>()

    //Null 陣列
    var arr16= arrayOfNulls<Int>(5)










}