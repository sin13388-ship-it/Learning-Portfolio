import java.util.Locale

fun main() {
    var player =PlayerClass()
    player.name="Mary"
    player.score=100
    player.show()

    var player1=PlayerClass()
    player1.show()

    player1.apply {
        name="John"
        score=72
        setData("Jack",67)
        show()
        showNew()
    }

    /*可以利用setter, getter 對資料做處理*/
    var data1 =ToUpper()
    data1.str="hello, Mary" //如果有寫setter，會自動呼叫
    println(data1.str) //回傳結果由getter 回傳

    data1.str=""
    println(data1.str)

    /*getter, setter exercise*/
    var myPlayer=Player()

    myPlayer.apply {
        println("myplayer: name= $name, id= $id, email= $email ")
        email="8" //會出現error
    }
    myPlayer.apply {
        name="John"
        id=20 //會出現error
        email="ABC@gmail.com"
        changePhone("99008866")
        attrPrint()
    }

    println("initialize===")

    /*class initialize(constructure) */
    var newPayer2=NewPlayer1("Lily",20,false)
    newPayer2.attPrint()

    var newPayer3=NewPlayer1("Lilyyyyyyyyyyyyyy",20,false)
    newPayer3.attPrint() //初始化給的變數不會納入getter, setter 的判斷

    //此時的更改在getter, setter 裡
    newPayer3.apply {
        name="Lilyyyyyyyyyyyyyy"
    }

    println()
    var newPlayer4=NewPlayer2("John", 33, 90)
    newPlayer4.attPrint()
    newPlayer4=NewPlayer2("Mary",45) //會建立一個全新的物件
    newPlayer4.attPrint()

    println()
    var newPlayer5=NewPlayer3("John", 43, 88)
    newPlayer5.attPrint()

    newPlayer5=NewPlayer3("Jane")
    newPlayer5.attPrint()


}


