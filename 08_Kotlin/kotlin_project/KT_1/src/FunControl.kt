import java.io.File

fun main() {

    /*Scope function*/
    //基本檔案讀寫
    println("Apply1====")
    var myFile = File(" my_file.txt") //default path : project
    myFile.setReadable(false)
    myFile.setReadable(false)
    myFile.setExecutable(true)
    //作用於當前物件
    myFile.apply {
        myFile.setReadable(true)
        myFile.setReadable(true)
        myFile.setExecutable(false)
    }
    val path =myFile.absolutePath
    println("path = $path")

    myFile.writeText("Hello world !!!\n")
    myFile.apply {
        appendText("This is Kotlin class.")
        appendText("It is rainy")
    }

    //Exercise 2
    println("Apply2====")
    /*傳統方法每次都要明確寫出lst*/
    var lst = mutableListOf<Int>(90,91,92,93,94)
    println()
    lst.set(2,100) //改變已存在的值
    println(lst)
    lst.remove(92)
    println(lst)

    /*使用apply 的寫法*/
    println()
    lst = mutableListOf<Int>(90,91,92,93,94)
    println(lst)
    //不用再每次lst
    lst.apply {
        set(2,100)
        remove(92)
        this.add(0, 50) //insert 用 add
    }
    println(lst)
    //-----let-----
    /*除了要做物件的控制之外，還想要回傳最終結果*/

    //改寫前
    println("Let====")
    lst = mutableListOf<Int>(90,91,92,93,94)
    lst.add(5,99)
    var avg =lst.average()
    println(lst)
    println("avg= $avg")
    //改寫後
    lst = mutableListOf<Int>(90,91,92,93,94)
    avg=lst.let{
        it.add(5,99)
        it.average()
    }
    println(lst)
    println("avg= $avg")

    //如果不想用it的話，想要自己的名稱
    lst = mutableListOf<Int>(90,91,92,93,94)
    avg=lst.let{ numbers: MutableList<Int>->
        numbers.add(5,99)
        numbers.average()
    }
    println(lst)
    println("avg= $avg")

    //自定義一個方法，可以return需求的值
    var lstSqure =lst.let{
        val i=(0..5).shuffled().first()
        println("i= $i, value=${it[i]}") //隨機取得list中的某個元素
        it.get(i)*it.get(i)
    }
    println(lstSqure)

    //----also----
    println("Also====")
    lst = mutableListOf<Int>(90,91,92,93,94)
    println(lst)

    lst.also {
        it.add(5,100)
        println("avg= ${it.average()}")

    }
    println(lst)

    val file = File("newFile.txt")
    file.also {
        it.setWritable(true)
        it.writeText("It is also function. \n")
        it.appendText("It is a file.")
    }

    //-----run-----
    println("Run====")
    lst = mutableListOf<Int>(90,91,92,93,94)
    var num1=run{
        println(lst)
        lst.min()
    }
    println("min = $num1")

    var check =lst.run{
        this.contains(100) // this 可以省略
    }
    println("check= $check")

    println()
    var data=file.run{
        readText()
    }
    println(data)


}