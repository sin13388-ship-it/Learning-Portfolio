class  Outer{
    val message ="Hello from Outer"

    /*Outer message 不能傳遞進去*/
    class Nested{
        fun greet(): String{
            return "Hellow from Nested"
        }
    }
}

class OuterIn{
    val message ="Hello from OuterIn"
    fun outerFun(){
        println("This is outerIn function")
    }
    /*變數可以傳遞進來*/
    inner class Inner{
        fun greet() ="Message is $message"

        fun innerFun() {
            outerFun()
        }
    }
}

class Calculator{
    class  Adder{
        fun add(a:Int, b:Int) =a+b
    }
}

class Phone(val number: String){
    inner class SimCard{
        fun showNumber(){
            println("Sim card number is :$number")
        }
    }
}

fun main() {

    val outer= Outer()
    println(outer.message)

    val nested=Outer.Nested()
    println(nested.greet())

    println()

    val outerIn = OuterIn()
    outerIn.outerFun()

    val inner = outerIn.Inner() //inner class 要先實作outer class 才能建立inner

    println(inner.greet())
    println(inner.innerFun())

    println()

    val myCal =Calculator.Adder()
    println("Result = ${myCal.add(10,20)}")

    println()

    val  myPhone =Phone("123456")
    val sim =myPhone.SimCard()
    sim.showNumber()

    println()

    /*inline 寫法*/
    Phone("9999").SimCard().showNumber()

    println()

}