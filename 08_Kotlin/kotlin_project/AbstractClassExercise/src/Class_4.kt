import java.sql.SQLOutput
import kotlin.math.pow

abstract class Base{
    /*抽象類別*/
    abstract var a: Int
    var b=0
    abstract fun fun1()
    fun fun2(){
        println("From base class")
    }
}
class Derived : Base(){
    override var a: Int=0
    override fun fun1() {
        println("From Derived class")
    }
}

abstract class Shape(p1 : Float=0.0f, p2: Float=0.0f){

     var length: Float=p1
     var width : Float=p2
     var radius : Float=p1

    abstract fun calArea(): Float
}

class Rect(p1 : Float=0.0f, p2: Float=0.0f):Shape(p1, p2){
    override fun calArea(): Float {
        return length * width
    }
}

class Circle(p1 : Float=0.0f, p2: Float=0.0f):Shape(p1, p2){
    override fun calArea(): Float {
       return  radius.pow(2.0f)*3.14159f
    }
}

fun main(){

    println("====== Exercise 1 ======")
    var myClass=Derived()
    println("a= ${myClass.a}")
    println("b= ${myClass.b}")
    println(myClass.fun1())
    println(myClass.fun2())

    println("====== Exercise 2 ======")
    var rect=Rect(10.0f,15.0f)
    var circle=Circle(12.3f)
    println("The area of rectangle : ${rect.calArea()}")
    println("The area of circle : ${circle.calArea()}")

}