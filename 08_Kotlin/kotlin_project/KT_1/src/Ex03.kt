fun main() {

    /*Q1: Calculate square*/
   val caluateSquare:(Int)->Int ={number-> number*number }
    println("Q1 Output:")
    println("Square of 7 = ${ caluateSquare(7)}")
    println("Square of 15 = ${ caluateSquare(15)}")

    println()
    /*Q2: Odd Even*/
    try {
        println("Input your number :")
        var number=readln().toInt()

        var OddEven:(Int)->String={if(it %2 ==0) "Even" else "Odd"}
        println("Q2 output : ${OddEven(number)}")

    }catch (e : Exception){
        println("Invalid input")
    }

    println()
    /*Q3: Deposit Interest Rate*/

    var depositInterestRate :(Int, Float, Int) -> Unit = { principal, interest, year->

            var totalAmount: Int
            var afterInterest : Int
            totalAmount = ((Math.pow((1+interest/100f).toDouble(),year.toDouble()))*principal).toInt()
            afterInterest =totalAmount-principal
            println("本金 ${principal} 存放${year}年的利息${afterInterest} 和本利和${totalAmount}")
        }

    println("Q3 Output : ")
    println(depositInterestRate(50000, 1.75f, 10 ))
    println(depositInterestRate(90000, 3.5f, 15 ))












}
