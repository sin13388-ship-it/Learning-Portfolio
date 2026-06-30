import java.sql.SQLOutput

interface Drawable{
    fun draw()
}
class SimpleCircle:Drawable{
    override fun draw() {
        println("Drawing a circle")
    }
}

interface Click{

    fun click()
}

open class Button : Drawable, Click{
    override fun draw() {
        println("Drawing a button")
    }
    override fun click() {
        println("Button Clicked!")
    }
}

/*Polymorphic應用*/
interface  Shape{
    fun area(): Double
    fun perimeter() : Double
}

class Rectangle(val width: Double, val length: Double):Shape{
    override fun area(): Double {
        return width * length
    }

    override fun perimeter(): Double {
        return (width+length) *2
    }
    fun showInfo(){
        println("Rectangle width = ${width}, length= ${length}, area = ${area()}, perimeter= ${perimeter()}")
    }
}

class Circle(val radius: Double) : Shape{
    override fun area(): Double {
        return Math.PI * radius * radius
    }
    override fun perimeter(): Double {
        return 2* Math.PI * radius
    }

    fun showInfo(){
        println("Circle radius = ${radius}, area = ${area()}, perimeter= ${perimeter()}")
    }

}




fun main() {

    val draw=SimpleCircle()
    draw.draw()

    val button =Button()
    button.draw()
    button.click()

    val rect:Rectangle=Rectangle(10.0,20.0)
    rect.showInfo()
    val circle:Circle=Circle(10.0)
    circle.showInfo()
    var shapes=mutableListOf<Shape>(rect,circle)
    for (item in shapes){
        println("Area = ${item.area()}")
        println("Perimeter= ${item.perimeter()}")
    }
    println()
    shapes.add(circle)
    shapes.add(rect)
    for(i in 0..  shapes.size-1){
        println("Area = ${shapes[i].area()}")
        println("Perimeter= ${shapes[i].perimeter()}")
        println()
    }
}