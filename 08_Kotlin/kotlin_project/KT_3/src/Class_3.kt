fun main() {

    var myClass=CClass("Mary", 20)
    myClass.show1()

    var myClass1 =CClass1("John", 20)
    myClass1.show()


    /*多重繼承的實作
    * 最後會被孫類別取代掉*/
    println()
    var myClass2= CGame("Jack", 88)
    myClass2.dataPrint()
    println()
    myClass2=CCGame("Jane", 10)
    myClass2.dataPrint()

   /*Class casting child -> parent*/

    println()
    var cls=myClass as PClass //可以向上轉型成父類別
    cls.show()

    println("========Casting=======")
    var newClass =myClass2 as Game
    newClass.dataPrint() //Upper casting

    println("Upper casting=======")
    /*宣告成一個父類別的資料型態，再放入子類別或孫類別*/
    var game=Game("AAA", 8)
    game.dataPrint()
    println()
    game=CGame("BBB", 77)
    game.dataPrint()
    println()
    game=CCGame("CCC", 2)
    game.dataPrint()

    println()
    /*類別作為參數傳入func*/
    printInfo(Game("XXX", 4))
    println()
    printInfo(CGame("YYY", 99))
    println()
    printInfo(CCGame("ZZZ", 7))

    /*多型應用*/
    println()
    checkClass(PClass("HHH"))
    println()
    checkClass(CClass("KKK", 11))

}

fun printInfo(game: Game){
        game.dataPrint()
}
fun checkClass(className:PClass){
    /*參數傳遞父類別，根據類別選擇邏輯*/
    when(className){
        is CClass -> className.show1()
        is PClass1 -> className.show()
    }
}