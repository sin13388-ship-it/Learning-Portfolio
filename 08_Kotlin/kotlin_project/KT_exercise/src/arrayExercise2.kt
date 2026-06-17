/*Array 練習*/

fun main() {
        /*存取陣列元素*/
        var arr: IntArray=intArrayOf(34,12,5,67)
        val v=arr[2]
        arr[3]=v
        /*get, set*/
        val y= arr.get(2)
        arr.set(3,y)

        /*Travel*/
        //.indices 會回傳 0 到 lastIndex（元素數量減 1）的區間
        var sum=0
        for(i in arr.indices){
                sum+=arr[i]
        }
        println(sum)

        //foreach
        sum=0
        arr.forEach { sum+=it }
        println(sum)

        //withIndex
        sum=0
        for((index, value) in arr.withIndex()){
                sum+=value
        }
        println(sum)

        /*Array with forEach, onEach, forEaxhIndexed, onEachIndexed*/
        //onEach 敘述會回傳處理後的資料，可以用於串接函式或是方法

        //比較 onEach, forEach 的差異
        var arr2: IntArray=intArrayOf(34,12,5,67, 9, 10, 7)

        var a=arr.forEach { println(it * 2 ) }
        var b=arr.onEach { println(it * 2) }
        println(a::class.simpleName) // return Unit
        println(b::class.simpleName) // return IntArray

        println()

        /*Application
        * 輸入一個陣列，找出偶數後顯示，再將每個數都x2，最後再顯示一次*/
        /*
        * filter 會回傳一個List 出來，再藉由OnEach 接收
        * OnEach 會回傳一個泛形再藉由map 接收
        * map 會回傳一個List，最後傳遞給forEach        *
        * */
        arr2.filter{it %2 ==0}.onEach(::println).map{ it *2 }.forEach(::println)














}