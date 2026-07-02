class Rect<T>(h:T, w:T)
{
    var width :T=w
    var height: T=h
}
class PlayerClass<T1,T2>(n:T1, s:T2)
{
    var name=n
    var score=s

}

interface Process<T>
{
    fun process(item:T)
}

class MyPrint:Process<String>
{
    override fun process(item: String) {
        println("Item: $item")
    }
}

data class Data(val name: String, val id: Int)

class MyData:Process<Data>{
    override fun process(item: Data) {
        println("name: ${item.name}, id: ${item.id}")
    }
}


fun main() {

    val myData=MyData()

    myData.process(Data("Mary", 100))
    myData.process(Data("Bob", 101))

    val rect=Rect(10,20)
    val rect1=Rect(100.2F, 100.5F)

    val player =PlayerClass("Mary", 100)
    val players =PlayerClass("Mary", "Bob")

    MyPrint().process("Mary")
    val myPrint=MyPrint()
    myPrint.process("Bob")



}