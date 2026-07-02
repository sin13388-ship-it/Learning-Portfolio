import java.sql.SQLOutput

/*資料類別*/
data class MyData(var name:String, var height:Float, var weight:Float){
    //只有屬性沒有方法
    var age: Int=0
}

data class  Student(
    val id: Int,
    val name: String,
    val age:Int,
    val grade: String
)

object StudentManager{
    private val students=mutableListOf<Student>()
    fun addStudent(student:Student){
        students.add(student)
    }
    fun showAllStudents(){
        println("List all students")
        students.forEach {
            println("id: ${it.id}, name: ${it.name}, age: ${it.age}, grade: ${it.grade}")
        }
    }
    fun removeStudentById(id: Int){
        val removed=students.removeIf { it.id==id }
        if(removed)
            println("remove student id =$id")
        else
            println("id is wrong")
    }
}
enum class Direction{
    EAST, WEST, SOUTH, NORTH;
}

fun move(dir:Direction){
    when(dir){
        Direction.NORTH-> println("Go to Top")
        Direction.SOUTH-> println("Go to Bottom")
        Direction.EAST-> println("Go to Right")
        Direction.WEST-> println("Go to left")
    }
}

enum class Day(val chinese: String){
    MONDAY("星期一"),
    TUESDAY("星期二"),
    WEDNESDAY("星期三");
}


fun main() {

    /*列舉*/

    var today=Day.MONDAY
    println(today)
    println(today.name)
    println("index= ${today.ordinal}")
    println("indput= ${today.chinese}") //取得參數名稱
    println()

    move(Direction.NORTH)
    move(Direction.SOUTH)
    move(Direction.WEST)
    move(Direction.EAST)
    println()

    var dir=Direction.EAST
    println(dir)
    println(dir.name)
    println("index= ${dir.ordinal}")
    println()
    dir=Direction.NORTH
    println(dir)
    println(dir.name)
    println("index= ${dir.ordinal}")


    val data1 =MyData("Mary", 173.2f, 54.5f)
    data1.age=20
    println(data1)
    println(data1.toString())

    /*比較*/
    val data2 =MyData("Mary", 173.2f, 54.5f)
    println(data1==data2) //比對主建構子的內容,age不在建構子哩，不會參與比對，true
    println(data1.equals(data2)) //比對內容, true
    println(data1===data2) //比對物件本身, false
    val data3=data1
    println(data1===data3) //比對物件本身, true

    data1.name="Bob"
    println(data3) //也會被修改，因為會被指向data1
    println()

    /*Copy*/
    var data4=data1.copy()
    println(data4)
    println(data4==data1)
    println(data4===data1)
    println()

    data4.name="Lily"
    println(data4)
    println(data4==data1)
    println(data4===data1)
    println()


    /*Exercise 2*/
    StudentManager.addStudent(Student (1001, "Mary", 15, "8"))
    StudentManager.addStudent(Student (1002, "John", 16, "9"))
    StudentManager.addStudent(Student (1003, "Bob", 17, "10"))
    StudentManager.addStudent(Student (1004, "Lily", 18, "11"))
    StudentManager.showAllStudents()
    StudentManager.removeStudentById(1003)
    StudentManager.showAllStudents()
    StudentManager.removeStudentById(100)

}