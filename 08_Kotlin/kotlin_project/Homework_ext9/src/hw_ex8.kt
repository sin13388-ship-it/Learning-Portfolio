data class Student(val name: String, val age: Int, val score: Int)

class ScoreManager
{
    private var students=mutableListOf<Student>()
    fun addStudent(student:Student){
        students.add(student)
    }
    fun listPass(){
        students.forEach {
            if(it.score >= 60) println("name= ${it.name}, age= ${it.age}, score= ${it.score}")
        }
    }
    fun printInfo(){
        students.forEach{println("name= ${it.name}, age= ${it.age}, score= ${it.score}")}
    }
}

data class Book(val title: String, val author: String, val year: Int)

class Library(){
    private var books=mutableListOf<Book>()
    fun  addBook(book: Book){
        books.add(book)
    }
    fun findByAuthor(author: String): List<Book>{
        return books.filter { it.author.equals(author) }
    }

    fun printInfo(){
        books.forEach { println("title= ${it.title}, author= ${it.author}, year = ${it.year}") }
    }

}



fun main() {

    println("Q1=======")

    val scoreManager=ScoreManager()
    scoreManager.addStudent(Student("Tom", 18, 85))
    scoreManager.addStudent(Student("Amy", 17, 92))
    scoreManager.addStudent(Student("Bob", 19, 55))
    scoreManager.addStudent(Student("Jane", 18, 60))
    println("List pass")
    scoreManager.listPass()
    println("List all")
    scoreManager.printInfo()

    println("Q2=======")
    val library=Library()
    library.addBook(Book("Kotlin入門","Tom",2020))
    library.addBook(Book("Android開發實戰","Amy",2021))
    library.addBook(Book("Kotlin進階技巧","Tom",2022))
    library.addBook(Book("資料結構基礎","Bob",2019))
    println("List all")
    library.printInfo()
    println("List author: Tom")
    library.findByAuthor("Tom").also { it.forEach {
        println("title= ${it.title}, " +
                "author= ${it.author}," +
                " year = ${it.year}") }
    }

}