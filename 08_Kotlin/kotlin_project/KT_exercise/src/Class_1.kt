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

}


