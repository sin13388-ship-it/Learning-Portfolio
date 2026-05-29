/*declare function*/
fun main() {
    var sum=add(8,12)
    println("Sum= ${sum}")
    //anonymous func
    val sum1={ a: Int, b:Int -> a+b }
    println("Sum1= ${sum1(8,12)}")
    //add1()
    //C2F()
    sayHello("Kelly",36)
    sayHello("Mary") //use default
    sayHello(age=25, name = "Jhon") //Named arguments, the order of arguments can be swapped
}
/*Named arguments, parameters, default value*/
fun sayHello(name:String, age: Int=10){
    println("Hi ${name}, age = ${age}")
}
//fun 函數名稱(parameters) : return type
fun add(a: Int, b: Int) : Int{
    return  a+b
}
//function exercise: nullable & safe call, elvis
fun add1(): Unit{
    var a: Int=0
    var b: Int=0
    println("Input two numbers to sum: ")
    a=readln()?.toIntOrNull() ?: 0 //save calls ?., elvis handle null
    b=readln()?.toIntOrNull() ?:0
    println("The sum: ${a+b}")
}
fun C2F(): Unit{
    var c_value: Float
    var f_vlaue: Float
    println("Input temperature in c degrees :")
    c_value = readln().toFloatOrNull()?: 0F //float 後要加f
    f_vlaue=c_value*1.8f+32F
    println("The temperature in F degree: ${f_vlaue}")
}
