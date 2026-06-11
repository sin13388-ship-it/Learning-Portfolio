fun main() {

    var q1 = studentMap("Mary", listOf(92, 83, 67)).run(::println)
    q1 = studentMap("John", listOf(81, 68, 70)).run(::println)
    q1 = studentMap("Nancy", listOf(93, 89, 73)).run(::println)


    val lst = listOf(1, 2, 3, 4, 5, 6)

    val f:(List<Int>)->List<Int> ={
        l ->
        l.filter { it %2 ==0 }

    }
    val s : (List<Int>)->List<Int> ={
        l ->
           var result: MutableList<Int> = mutableListOf()
            l.forEach {
                result.add(it *it)
            }
        result
    }

    val q2=Math(lst, f(lst), s(lst)).run(::println)

}
fun studentMap(name: String, scores: List<Int>): MutableMap<String, Any>{

    var stdMap =mutableMapOf<String, Any>(Pair("name",name),
        Pair("sum",scores.sum()),
        Pair("average",scores.average()))
    return stdMap
}
fun Math(data: List<Int>, filter:(List<Int>) -> List<Int>, square:(List<Int>) -> List<Int>): List<Int>{

    var lst =filter(data)

    return square(lst)

}