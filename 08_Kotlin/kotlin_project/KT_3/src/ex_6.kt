/*Class Exercise*/
fun main() {

    /*Question1*/
    val std1=Student("Tom", 18, 85)
    val std2=Student("Amy", 17, 92)
    val std3=Student("Bob", 19, 55)
    std1.printInfo()
    std2.printInfo()
    std3.printInfo()

    println()

    val rect1= Rectangle(120,30)
    val rect2= Rectangle(250,60)

    println("Rect1: ${rect1.printInfo()}")
    println("Rect2: ${rect2.printInfo()}")
}

class Student(val name:String, val age: Int, val score: Int){

    fun isPass(): Boolean{ return score >=60}
    fun printInfo(){
        println("name= $name, age= $age, score= $score, isPass= ${isPass()}")}
}

class Rectangle(val width:Int, val height:Int){
    fun area(): Int {return width* height}
    fun perimeter(): Int {return (width+ height)*2}
    fun printInfo(): String{
        return "width= $width, height= $height, area= ${area()}, perimeter= ${perimeter()}"
    }
}