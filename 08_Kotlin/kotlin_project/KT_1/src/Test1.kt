fun main() {
    /*一樣main 是主要執行點*/
    println("Hello world")
    println("This is kotlin class.")

    var price : Int=10 // 資料型態都是大寫
    var name : String ="Mary"
    var age : Int
    var weight =50.69 //Type Inference
    val address ="Taoyuan"
    println("name")
    age=18
    //println(age) // no initialize , error !
    println(age)
    println(weight)
    println(address)


    /*String Exercise*/
    var str1 :String ="123456789"
    println("str1 length : ${str1.length}") //取得長度
    println("str1 length : ${str1.count()}") //取得個數


    println("str1 first char:  ${str1.first()}") //get first char
    println("str1 last char ${str1.last()}") // get last char

    var ch: Char=str1[4]
    println("str1[4] $ch") //get specific char

    //trimIndent()

    //多行字串宣告 """ """
    var str4="""
        "  Test line1 \n",
         "Test line2"
         """
    println(str4)

    var str5="""
        "  Test line1 \n",
         "Test line2"
         """.trimIndent()
    println(str5)

    var str6="""
           |"Test line1 \n",
         |"Test line2"
         """.trimMargin() //沒有加的話會把|之前的空格也如實印出
    println(str6)












}