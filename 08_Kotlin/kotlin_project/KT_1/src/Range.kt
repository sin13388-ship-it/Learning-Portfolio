const val GREEN_COLOR="GREEN" //一定是val
const val COLORLESS="NONE"


fun main() {
    /*range variables*/
    var r =2..8

    for(i in r)
        print("i= $i\t ") //2 3 4 5 6 7 8
    println()

    for (j in 2..8 step 2)
        print("j= $j\t") //2 4 6 8
    println()

    /*字元也可以是範圍變數*/
    var c ='E'..'H'
    for(i in c)
        print("i= $i\t ")

    for (j in 'E'..'H' step 2)
        print("j= $j\t")
    println()

    /*Until 也有相同的功能，但是最後一個元素不算*/
    r= 2 until 8
    for(i in r)
        print("i= $i\t ") //2 3 4 5 6 7
    println()

    for (j in 2 until 8 step 2)
        print("j= $j\t") //2 4 6
    println()

    /*downTo 是遞減關鍵字，最後一個元素不算*/
    var n =8 downTo 2
    for(i in n)
        print("i= $i\t ") //2 3 4 5 6 7
    println()

    for (j in 8 downTo 2 step 2)
        print("j= $j\t") //2 4 6
    println()

    /*in 其實是一個判斷，會return 一個boolean*/
    var result = 1 in 2..8
    println("Result=1 and in 2~8 ? = $result")

    result=3 in 2..8
    println("Result=3 and in 2~8 ? = $result")

    result=1 !in 2..8 //not in
    println("Result=1 and not in 2~8 ? = $result")

    /* in Exercise*/
    print("Input age: ")
    var age =readln().toInt() //read line 進來的都是string

    println("is under 18? ${age in 0..18 }")

    /*用變數承接判斷式的結果
    * Kotlin 中 if 可以回傳值，這是它與 Java 的重要差異之一
    * */
    var ageResult = if(age in 1 ..5)
        "It is preschool"
    else if (age in 6.. 11)
        "It is school children"
    else if (age in 12 .. 18)
        "It is teenager"
    else if (age in 19..24)
        "It is youth"
    else
        "It is adult"

    println("ageStatus : $ageResult")
    //if 也可回傳數字
    println("Input fruit :")
    var fruit =readln()
    var price= if(fruit.lowercase() == "apple") //kotlin 可以用== (不用equals)
            100
        else
            50
    println("Price: $price")

    /*String compare exercise*/
    val data1="abc"
    var data2="ABC"
    if(data1==data2) //第一種方法
        println("data1 is equal to data2")
    else
        println("It is not the same")

    if (data1.equals(data2.lowercase())) //第二種方法
        println("data1 is equal to data2")
    else
        println("It is not the same")

    /*Const variable Exercise*/
    val points =100
    println()
    println("The color : ${if (points>80) GREEN_COLOR else COLORLESS}") //Kotlin 特色

}