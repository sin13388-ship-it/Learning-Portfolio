

fun main() {
    /*when exercise
    * 可以回傳值
    * 不一定要引入參數，可以從外部呼叫
    *
    * */

    val v: Int
    val five =5
    val str="11"

    println("please input a number to select a character: ")
    v=readln().toInt() //Initialize once

    when(v){
        1-> println("a") //const
        2-> println("b") //const
        3,4 -> println("c or d") // multiselect
        five -> println("e") //variable
        in 6..10 ->println("f-j") // in Range
        str.toInt()->println("k") //method
        else -> println("invalid")
    }

    print("Please input health points:")
    var point=readln().toInt()

    //可以不傳入參數
    var isBlessed =true
    val status = when{
       point == 100 -> "It is good"
        point >=90 -> "There are a few scratches"
        /*
        * 這裡的 { } 只是一個 程式碼區塊（code block），目的是
        *「當 point >= 75 時，執行這段邏輯，把最後的字串結果作為 when 的回傳值」
        * 它不會被儲存，也不能被傳遞，執行完就結束了
        * */
        point >=75 ->{
            if (isBlessed){
                "It is blessed"
            }else{
                "There are minor wounds"
            }
        }
        else-> "It is awful"
    }

    println("Health status : ${status}")

    /*Exception exercise*/
    /*How to throw an exception*/

    var name: String
    name=readln()
    try {
        if(name.isNullOrEmpty())
            throw Exception("Please input name")

        /*
        * 在 Kotlin 中，當 lambda 只有一個參數時，可以省略參數宣告，直接用 it 代替
        * name.forEach {
                if (!it.isLetter())
                throw Exception("Input right name")
            }
        * */
        name.forEach {
            if(!it.isLetter())
                throw Exception("Input right name")
        }

        println("$name is correct")
    } catch (e: Exception){
        println(e.message)
    }

}