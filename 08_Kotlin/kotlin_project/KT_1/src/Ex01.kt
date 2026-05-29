/*Kotlin Homework Ex_1*/
fun main() {

   // printMultipleTable()

    calculateKarmaAndPrintColor()

}
fun calculateKarmaAndPrintColor(): Unit{

    var r =0 until 110
    var points=r.random()

    for(i in  0 until 3){
        val karma = ( Math.pow(Math.random(), (110-points)/100.0) *20 ).toInt()
        var color= when(karma){

            in 0..5->"red"
            in 6..10->"orange"
            in 11..15 ->"purple"
            in 16..20->"green"
            else ->"invalid"
        }

        println("${i+1} karma value: $karma -> $color")
    }

}
fun printMultipleTable(): Unit{

    for(i in 1..9){
        for (j in 1..9){
            println("$i x $j = ${i*j}")
        }
    }

}

