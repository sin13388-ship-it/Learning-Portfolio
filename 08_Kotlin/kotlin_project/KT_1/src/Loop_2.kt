fun main() {
    /*While loop exercise*/
    //Guess number, 可以猜5次

    var targetNumber = 1..10
    var v : Int
    var times=1
    var guessNumber=-1 //Initialize

    v=targetNumber.random() //會從 1~10 隨機一個

    while (guessNumber !=v && times< 6){

        println("Guess times: ${times++}, input guess no(1..10) ")
        guessNumber = readln().toIntOrNull() ?: -1
        if(guessNumber>v) println("Too big")
        else if (guessNumber < v) println("Too small")
        else println("Bingo!")
    }

    /*do while*/
    //Sum
    var sum:Int=0
    v=1
    do {
        sum+=v
    }while (v++ <10)
    println("The sum: ${sum}")
}