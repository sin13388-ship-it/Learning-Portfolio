import java.io.File
import java.io.FileReader
import java.io.FileWriter

fun main() {
    /*檔案操作
    * .mkdir() : Boolean 回傳是否建立成功
    * .apply 作用域函數，建立檔案時順便完成初始動作
    *
    *
    * */
    var dir= File("").absolutePath
    println("current path: $dir")

    val newDir= File("C:\\Users\\User\\Documents\\kotlin_file_exercise")
    val result= newDir.mkdir()
    println("$result")



    // File()：建立檔案物件，指定檔案路徑
    // 不會立刻建立實體檔案，需搭配 createNewFile() 才會真的建立
    var file = File("$newDir\\data1.txt").apply {
        createNewFile()
        writeText("Hello Mary \n")
        appendText("Good morning !\n")
        appendText("This is kotlin class. \n")
    }

    println()
    var data =file.readText()
    println(data)

    println()
    val lines=file.readLines().also {
        it.forEach {
            println("data= $it")
        }
    }

    println()

    /*FileWriter() 說明:
    * 1. 建立檔案物件，指定檔案路徑
    * 2. 第二個參數為是否要 append，true=append, false=overwrite
    * 3. use{} 作用域函數，使用完畢後自動關閉檔案
    * */
    var newFile = FileWriter("$newDir\\data2.txt", false)
    newFile.use {
        it.write(0x31)
        it.write(0x38)
        it.write(0x41)
        it.write("\n")
        val data=charArrayOf('H','e','l','l','o',' ','K','o','t','l','i','n','\n')
        it.write(data)
        it.write("It is sunny day\n")
    }

    /*FileReader() 說明:
    * 1. 建立檔案物件，指定檔案路路徑
    * 2. use{} 作用域函數，使用完畢後自動關閉檔案
    * 3. read() 讀取檔案內容，回傳讀取的字元數量
    * 4. readLines() 讀取檔案內容，回傳 List<String>
    * */

    var chBuff=CharArray(50)
    var len=0
    FileReader("$newDir\\data2.txt").use {
        len=it.read(chBuff)
        println("len= $len")
    }
    println(chBuff)
    println()
    for (i in 0 until len){
        print(chBuff[i])
    }

    println()
    FileReader("$newDir\\data2.txt").use {
        val dataList=it.readLines()
        for (data in dataList){
            println(data)
        }
    }


}