
fun main() {
    performCombat()
    performCombat("Mary")
    performCombat("John", isBlessed = true)

    fireball_1(2)

    var result =mul(10,20)
    println("result=${result}")
    result=mul_1(10,20)
    println("result=${result}")

    println(getGreeting("Mary"))

}
/*Overload Exercise*/
fun performCombat()
{
    println("You see nothing to fight")
}
fun performCombat(enemyName: String)
{
    println("You begin fighting $enemyName")
}
fun performCombat(enemyName: String, isBlessed: Boolean)
{
    if(isBlessed)
        println("You begin fighting $enemyName. You are blessed")
    else
        println("You begin fighting $enemyName")
}


fun fireball(ball: Int=2) :Unit
{
    println("Fireball number = $ball")
}
/*Single-Expression Function
* 當函式主體只有一個表達式時，可以省略大括號 {} 和 return，直接用 = 連接
* 編譯器會自動推斷回傳型別（這裡 println 回傳 Unit），所以也不需要寫 : Unit
* */
fun fireball_1(ball: Int=2) =println("Fireball number = $ball")

fun mul(a:Int, b:Int) : Int{
    return a * b
}
fun mul_1(a: Int, b: Int)=a*b //Single-Expression Function
fun getGreeting(name: String) ="Hello $name"