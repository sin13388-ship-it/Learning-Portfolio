fun main() {
    println("Hello")
    run{println("Good morning")}

    println()

    //匿名函式
    val greeting={
        val year=2025
        "Welcome to SimVillage in $year"
    }

    //無參數，回傳字串
    val greeting2 : () -> String ={
        val year=2025
        "Welcome 2 SimVillage in $year"
    }

    println(greeting())
    println(greeting2())

    //有 Int 參數，明確宣告
    val greetingYear: (Int) -> Int ={
        year:Int ->
        year +1911
    }
    println(greetingYear(115))

    val data1: Int =greetingYear(100)
    println("year =$data1")

    //有 String 參數，沒有明確宣告
    val greetingName : (String) -> String={name ->
        "Hi $name, welcome to SimVillage"
    }
    println(greetingName("Mary"))

    //2個以上參數
    val greetingTwo={name: String, numBuilding: Int ->
        println("Adding $numBuilding house")
        "Hi $name, welcome to new House" //回傳
    }

    println(greetingTwo("Jhon",3))

    val greetingSimple: ()-> Unit={
        println("Simple greeting")
        println("Hello world")
    }

    greetingSimple()

    val mathResult :(Int, Int, String) -> Int={x,y,process ->
        val result =when(process){
            "+" -> x+y
            "-" -> x-y
            "*" -> x*y
            "/" -> x/y
            else -> 0
        }
        result //要再寫一次回傳
    }

    //直接return 的版本
    val mathResult1 :(Int, Int, String) -> Int={x,y,process ->
        when(process){
            "+" -> x+y
            "-" -> x-y
            "*" -> x*y
            "/" -> x/y
            else -> 0
        }
    }

    println()

    //使用變數去承接lambda函式的時候，要符合函式的規則，也要有大括號{}
    println("100+20 = ${mathResult1(100,20,"+")}")
    println("100-20 = ${mathResult1(100,20,"-")}")
    println("100*20 = ${mathResult1(100,20,"*")}")
    println("100/20 = ${mathResult1(100,20,"/")}")
    println("100%20 = ${mathResult1(100,20,"%")}")


    /*課本習題*/
    //事前宣告
    var mathOpt: ()-> Unit
    var sel:Int?=0
    println("Select your mode, 0 : Add, 1 : Sub")
    sel=readln().toIntOrNull() ?: 0 //   safe call

    /*動態的方式去處理邏輯
    * if else 處理mathOpt 的邏輯
    * mathOpt() 才是真正執行
    * */
    if (sel==0) {
        mathOpt={println(1+2)}
    }
    else{
        mathOpt={println(1-2)}
    }
    mathOpt() //執行前面的設定

    /*參數 it*/
    val inch2cm:(Double) -> Double ={inch ->
        inch * 2.54
    }
    println(inch2cm(2.0)) //記得小數點

    /*參數 it*/
    val inch2cm2:(Double) -> Double ={
        it * 2.54
    }
    println(inch2cm2(2.5)) //記得小數點

    /*Example*/
    val greetingYearIt: (Int) -> Int={
        println("it function")
        it +1911
    }
    println(greetingYearIt(100))

    val data2: Int=greetingYear(110)
    println(data2)

}