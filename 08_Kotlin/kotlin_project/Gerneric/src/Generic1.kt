fun <T> printItem(item:T){
    println("Item : $item")
}
fun <T1, T2>myFun(p1:T1, p2:T2)
{
    println("p1= $p1")
    println("p2= $p2")
    println()
}
fun <T: Comparable<T>>compare(t1:T, t2:T)
{
    when{
        t1 > t2 -> println("$t1 > $t2")
        t1 < t2 -> println("$t1 < $t2")
        else -> println("$t1 = $t2")
    }
}
fun <T1: Number, T2: Number> add(p1:T1, p2:T2) : Double
{
    var sum: Double
    sum=p1.toDouble().plus(p2.toDouble())
    return sum
}
fun <T>compare1(t1:T, t2:T) where T:Number, T: Comparable<T>
{
    /*where 關鍵字可以連接多個泛型約束*/
    when{
        t1 > t2 -> println("$t1 > $t2")
        t1 < t2 -> println("$t1 < $t2")
        else -> println("$t1 = $t2")
    }
}


fun main() {

    println("sum= ${add(100, 32.4)}")
    //println("sum= ${add("Mary", 32.4)}") //失敗，不是Number

    println(compare1(12,56))


    compare(50, 30)
    compare("Mary", "John")
    compare(12.45, 12.45)
    println()

    printItem("Mary")
    printItem(100)
    println(true)
    println()

    myFun(100, 200)
    myFun(100, "Mary")
    myFun("Mary", "Bob")
    myFun(false, 100)



}