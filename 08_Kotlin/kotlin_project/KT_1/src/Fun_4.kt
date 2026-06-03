import com.sun.jdi.Value
import kotlin.math.round

fun main() {

    val result=bill(10, {it*25})
    println(result)
    val result1=bill(10, {value : Int -> value *23})
    println(result1)
    val total =bill(10){it *23} //lambda 是最後一個的時候可以寫在函式之外
    println(total)
    val total1 =bill(10){price-> price *23}
    println(total1)

    /*lambda 先是變數再傳入
    * 只要符合型別簽章，可以動態的改變
    * */
    var cal1:(Int)->Int = {it *23} //只有lambda 是最後一個才能這樣寫
    val total2=bill(10, cal1)
    println(total2)
    cal1 ={price:Int -> price*2} //可以動態的改變程式內容
    println(cal1)

    /*課本習題 - temperature converter*/
    val F=temperatureConvert(37.0){1.8 * it +32}
    println("C->F : ${F}")
    val C=temperatureConvert(98.6){value -> (value-32)/1.8}
    println("F->C : ${C}")


    /* More lambda exercise
    *  提供一個2個arguments的lambda方法
    *  回傳字串
    * */
    //lambda在()裡寫
    runSimulate("Mary", funTwoParam = {name:String, age:Int ->
        "Hi ${name}, your age is $age"
    })
    //lambda拉出來寫
    runSimulate("Jhon"){name: String, building: Int ->
        val test= "$name , Welcome to building number $building"
        test
    }
    runSimulate1({it *25}, "Jhon", 10000)
   var funOne={year: Int -> year+1}
    runSimulate1(funOne, "Jhon", 20000)


    /*使用lambda的方式動態改變要印出的內容
    * 使用lambda的方式計算年紀
    * 主函式運作(print)
    * name, age 自動型別推斷
    * */
    runSimulate2("Mary", dataPrint = {name, age-> println("$name 's age is $age")}){it +20}

    var data: String="Mississippi"
    var count =data.count() //計算字串
    println("all count= $count")
    count=data.count({letter -> letter =='s'}) //計算s的出現次數
    count=data.count{letter -> letter =='s'}
}

fun temperatureConvert(value: Double, convert : (Double)-> Double): Double{
    val temp=convert(value)
    return temp
}

fun bill(number:Int, calculate: (Int)-> Int): Int{
    var total : Int=0
    total=calculate(number)
    return total
}

fun bill2(number:Int, calculate: (Int)-> Int, number2:Int): Unit
{
    //這種方法就不能把大括號寫在外面
}

fun runSimulate(playerName:String, funTwoParam:(String, Int)->String){
    val numBuilding =(1..10).shuffled().last() //隨機取最後
    println(funTwoParam(playerName,numBuilding))
}

fun runSimulate1(funOneParam: (Int)->Int, name:String, num:Int){
    val value =funOneParam(100)
    println("${value}")
    println("$name has $num")
}

fun runSimulate2(name:String, dataPrint:(String, Int)->Unit, funOne:(Int)->Int){
    val number=(20..30).shuffled().first()
    val value=funOne(number)
    dataPrint(name, value)
}

