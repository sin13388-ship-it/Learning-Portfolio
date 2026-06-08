/*Homework 0605*/

fun main() {

    /*Q1*/
//    println("Input 1st number :")
//    var a=readln()?.toIntOrNull() ?: 0
//    println("Input 2nd number :")
//    var b=readln()?.toIntOrNull() ?: 0
//    var result : (Int, Int)-> Int = {a,b -> a+b}
//    println("a + b = ${result(a,b)}")
//    println("Input 1st number :")
//     a=readln()?.toIntOrNull() ?: 0
//    println("Input 2nd number :")
//      b=readln()?.toIntOrNull() ?: 0
//    result = {a,b -> a*b}
//    println("a x b = ${result(a,b)}")

    /*Q2*/
    println("Input Jack's score to calculate the total :")
    student("Jack",10,{math,english,Science -> math+english+Science})
    println("Input Mary's score to calculate the average :")
    student("Mary",20,{math,english,Science -> (math+english+Science)/3})

}


fun student(name: String, id: Int, score:(Int, Int, Int)-> Int) : Unit {
    println("Please input the score of Math :")
    var math=readln()?.toIntOrNull()?:0
    println("Please input the score of English :")
    var english=readln()?.toIntOrNull()?:0
    println("Please input the score of Science :")
    var Science=readln()?.toIntOrNull()?:0
    println("$id - $name - score : ${score(math,english,Science)}")
}