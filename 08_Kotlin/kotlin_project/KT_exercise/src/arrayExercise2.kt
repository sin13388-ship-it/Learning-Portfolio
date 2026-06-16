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







}