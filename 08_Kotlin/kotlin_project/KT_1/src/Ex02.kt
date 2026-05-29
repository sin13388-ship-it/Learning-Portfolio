/*Kotlin Homework Ex_2*/
fun main() {

    student("Mary",80,90,72) //80.67
    student("Jhon",83,67,73) //74.33
    student("Kelly", 100,90,80) //90

    println("10 : ${drunkStatus(10)}")
    println("48 : ${drunkStatus(48)}")
    println("23 : ${drunkStatus(23)}")


}
fun drunkStatus(v: Int)=when(v){

    in 1..10 ->"tipsy"
    in 11..20 ->"sloshed"
    in 21..30->"soused"
    in 31..40->"stewed"
    in 41..50->"..t0aSt3d"
    else -> "invalid"

}


fun student(name: String,math:Int,english:Int,science:Int){

    var avg =(math+english+science)/3.0f
    println("Student: ${name}, Average score: ${avg}")

}