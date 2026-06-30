package homework

import java.sql.Date


abstract class Shape{
    abstract fun area() : Double
}

class Rectangle(val width: Double=0.0, val height : Double =0.0): Shape(){
    override fun area() : Double {
        return height * width
    }
}

class Circle(val radius: Double=0.0): Shape(){
    override fun area() : Double {
        return Math.PI * radius *radius
    }
}

abstract class Employee{
    abstract fun calculateSalary(): Double
}

class FullTimeEmployee(val name: String, val monthlySalary: Double=0.0): Employee(){
    override fun calculateSalary() : Double {
        return monthlySalary*12
    }
}

class PartTimeEmployee(val name: String, val hourlyRate: Double=0.0,val workingHour: Int =0): Employee(){
    override fun calculateSalary() : Double {
        return hourlyRate * workingHour
    }
}

interface PaymentMethod{
    fun pay(amount:Int): Boolean
}

class CreditCard: PaymentMethod{
    val pType="CreditCard"
    override fun pay(amount: Int): Boolean {
        println("使用信用卡付款：$amount 元 , 付款成功")
        return true
    }
}
class Cash: PaymentMethod{
    val pType="Cash"
    override fun pay(amount: Int): Boolean {
        println("使用現金付款：$amount 元 , 付款成功")
        return true
    }
}

class Checkout{
    fun processPayment(amount: Int, method: PaymentMethod){
       if  (method.pay(amount)) println("process : success") else println("process : fail")
    }
}

fun main() {
    /*Ex7 Q1 Shape calculator*/
    val circle: Shape= Circle(6.0)
    val rectangle: Shape = Rectangle(12.0,16.0)
    println("The area of circle = ${circle.area()}")
    println("The area of rectangle = ${rectangle.area()}")

    /*Ex7 Q2 Employee salary calculation system*/
    val emp1= FullTimeEmployee("Alice",50000.0)
    val emp2 = PartTimeEmployee("Bob", 300.0, 60)
    println("員工類型\t姓名\t薪資資料\t")
    println("正職員工\t${emp1.name}\t月薪 ${emp1.monthlySalary}\t 年薪 ${emp1.calculateSalary()}")
    println("兼職員工\t${emp2.name}\t時薪 ${emp2.hourlyRate}，工作時數  ${emp2.workingHour}\t 月薪${emp2.calculateSalary()}")

    /*Ex9 Q1 PaymentStrategy*/
    val cash = Cash()
    val creditCard = CreditCard()
    val checkout= Checkout()
    checkout.processPayment(10000, creditCard)
    checkout.processPayment(500, cash)

}