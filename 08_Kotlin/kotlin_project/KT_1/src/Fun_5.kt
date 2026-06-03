/*Exercise
* 要使用lambda 來判斷年齡
*
* */

fun main() {

    var result: String
    println("Input your age: ")
    var age=readln()?.toIntOrNull() ?:0
    println(buyWine(age){it >=18})

    var str =buyWine(age, {it >20} )

    var F= returnTmpConvert("C2F")(37.0) //嵌套
    println(F)

    /*function 回傳一個lambda*/
    result=ConfigGreeting()("Mary")
    println(result)

    /*使用when選擇並回傳方法*/
    var cal : (Int, Int)->Int =numProcess('+')
    var sum =cal(10,20)
    println("sum = $sum")

    //簡化成 ()()
    sum=numProcess('-')(10,20)
    println("sum = $sum")

}

fun buyWine(age:Int, condition: (Int)-> Boolean) : String{

    val result: String

    if(condition(age))
        result="You can buy wine"
    else
        result="You are under 18"

    return result
}


fun numProcess(dir:Char):(Int, Int)->Int{
    when(dir){
        '+'-> return {x:Int, y: Int -> x+y}
        '-'-> return {x:Int, y: Int -> x-y}
        '*'-> return {x:Int, y: Int -> x*y}
        '/'-> return {x:Int, y: Int -> x/y}
        else -> return {x:Int, y: Int -> -1}
    }
}


fun returnTmpConvert(caption: String): (Double)-> Double{
    /*該方法會傳入一個參數caption, 並回傳一個double 的結果，該結果是根據傳入的參數做計算*/

    when(caption){
        "C2F"->return {it *1.8 +32}
        "F2C"-> return {(it-32)/1.8}
        else -> return {-1.0}
    }
}

fun ConfigGreeting():(String)->String{

    /*回傳一個(String)->String 的方法*/

    val name ="hospital"
    var numBuilding=5
    return {
        playerName :String->
        numBuilding +=1
        println("Adding $numBuilding $name")
        "Welcome to new village, $playerName"
    }
}