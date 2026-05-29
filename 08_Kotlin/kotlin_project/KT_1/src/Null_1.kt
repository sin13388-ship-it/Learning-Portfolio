
//Null Safety
fun main() {
    var str: String? =null
    var len: Int
    var str1: String? ="Mary"

   // println("Length of string : ${str1.length}") /*如果是nullable 要是 str1?.*/
    try {
        len=str!!.length //assertion
    }catch (e: Exception){
        println(e)
    }

    if (str !=null){
        len=str.length
        println("Length: ${str.length}")
    }
    //Elvis
    println("Length(Elvis): ${str?.length ?: 0}")
    println("Length(Elvis): ${str1?.length ?: 0}")

}
