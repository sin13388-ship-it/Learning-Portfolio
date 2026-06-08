/*Homework 0605*/

fun main() {

    /*Q1*/
    //Higher orderfunction exercise
    println("Input 1st number :")
    var a=readln()?.toIntOrNull() ?: 0
    println("Input 2nd number :")
    var b=readln()?.toIntOrNull() ?: 0
    var result : (Int, Int)-> Int = {a,b -> a+b}
    print(" a + b = ")
    process(a,b) {x,y -> x+y} //避免命名覆蓋
    println("Input 1st number :")
     a=readln()?.toIntOrNull() ?: 0
    println("Input 2nd number :")
      b=readln()?.toIntOrNull() ?: 0
    result = {a,b -> a*b}
    print("  a x b = ")
    process(a,b) {x,y -> x*y}

    /*Q2*/
    println("Input Jack's score to calculate the total :")
    student("Jack",10,{math,english,science -> math+english+science})
    println("Input Mary's score to calculate the average :")
    student("Mary",20,){math,english,science -> (math+english+science)/3}

}

fun process(a: Int, b: Int, op: (Int, Int) -> Int){

    println("${op(a,b)}")

}


fun student(name: String, id: Int, score:(Int, Int, Int)-> Int) : Unit {
    println("Please input the score of Math :")
    var math=readln().toIntOrNull()?:0 //readln() 永遠回傳string 不用?
    println("Please input the score of English :")
    var english=readln().toIntOrNull()?:0
    println("Please input the score of Science :")
    var science=readln().toIntOrNull()?:0
    println("$id - $name - score : ${score(math,english,science)}")
}