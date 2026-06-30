import kotlin.random.Random

/*使用object 生成一組亂數
* 使用者可以輸入長度(最小為1)
* 生成亂數
* */
object randNumber{
    var num:Int=1
        set (value){
            field= if(value<1) 1 else value
        }
    var id: Int
    init{
        id=100
    }
    /*回傳指定長度的int 陣列*/
    fun getNumber(): IntArray{
        /*使用apply 生成亂數*/
        var numbers= IntArray(num).apply {
            for (i in this.indices){
                this[i]= Random.nextInt(1,11)
            }
        }
        return  numbers
    }
}

object Logger{
    var count: Int

    /*類似於static, 只會init 一次，每次呼叫都會改變*/
    init{
        count=0
        println("count= $count, Welcome to Logger")
    }
    fun log(message: String){
        println("Log: $message")
        count++
    }
    fun logCount(): Int=count
}

interface LogMag{
    fun log(message: String){
        println("Log : $message")
    }
}
class  AppLogger:LogMag {
    fun myLog(myClick: Click){
        myClick.click()
    }
}

open class Car(val brand: String){
    open fun basicInfo(name:String):String{
        println("Car brand is $brand")
        return "sales name is $name"
    }
}




fun main() {

    var myCar=Car("BMW")
    println(myCar.basicInfo("John"))

    println()

    myCar=object : Car("Toyota") {
        /*直接複寫既有方法*/
        override fun basicInfo(name: String): String {
            println("This is object car $brand")
            return "My sales is $name"
        }
    }
    println(myCar.basicInfo("Mary"))

    println()



    var button1 =object : Button(){
        override fun draw() {
            println("Object button drawing")
        }

        override fun click() {
            println("Object button clicked")
        }
    }
    button1.click()
    button1.draw()


    randNumber.num=5
    var numbers =randNumber.getNumber()
    numbers.forEach { print("$it, ") }
    println()
    println("count= ${Logger.logCount()}") // 第一次會初始化，之後就不會
    println()
    Logger.log("Log test 1") //每次都會改變
    Logger.log("Log test 2")
    Logger.log("Log test 3")
    println("count= ${Logger.logCount()}")

    val appLogger=AppLogger()
    appLogger.log("Hello")
    appLogger.myLog(object :Click{
        override fun click() {
            println("myLog is clicked")
        }
    })

    println()

    /*使用 object 去implement 介面*/
    val log =object :LogMag{
        override fun log(message: String) {
            println("This is object : $message")
        }
    }
    log.log("My Log")

    println()

    /*使用之前新增的interface button*/
    var button =object :Click{
        override fun click() {
            println("This is object: \"button clicked !\"")
        }
    }
    button.click()

}