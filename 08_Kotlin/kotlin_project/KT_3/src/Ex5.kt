fun main() {

    //想印出 Map 同時保留 Map 變數，要用 .also 而不是 .run
    println("Q1====")
    studentMap("Mary", listOf(92, 83, 67))
    studentMap("John", listOf(81, 68, 70))
    studentMap("Nancy", listOf(93, 89, 73))

    println("Q2====")
    val lst = listOf(1, 2, 3, 4, 5, 6)
    val f:(List<Int>)->List<Int> ={
        l -> l.filter { it %2 ==0 }
    }
    val s : (List<Int>)->List<Int> ={
        l ->l.map {(it *it)}
    }
    math(lst, f, s).also(::println)
}
fun studentMap(name: String, scores: List<Int>): MutableMap<String, Any>{
    val stdMap =mutableMapOf<String, Any>("name" to name,
        "sum" to scores.sum(),
        "average" to scores.average()).also {
            println("name=${name}, sum =${it["sum"]}, average= ${it["average"]}") }
    return stdMap
}
fun math(data: List<Int>, filter:(List<Int>) -> List<Int>, square:(List<Int>) -> List<Int>): List<Int>{
    val lst =filter(data)
    return square(lst)
}