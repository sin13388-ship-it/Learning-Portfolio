/*Map exercise*/
fun main() {

    var map1 = mapOf<String, Int>()

    println("Set a map===")
    //using pair
    var map2= mapOf<String, Double>(Pair("Mary",62.4), Pair("John", 58.6), Pair("Nancy", 50.2))
    println(map2)
    //using to
    var map3=mapOf(1 to "Leo", 15 to "Joanna", 6 to "Brown")
    println(map3)
    //明確宣告
    var map4 : Map<String, Int> =mapOf("Apple" to 10  , "Banana" to 20, "Cherry" to 80)
    println(map4)

    //Get length
    println("Get length===")
    println(map4.size)
    println(map3.count())

    println("Get value===")
    //using key as an index
    println(map2["Mary2"] ?: "Not Found") //nullable
    println(map2.get("Mary") ?: "Not Found") //nullable
    println(map2.getValue("Nancy")) //not null, throws exception
    println(map3[10] ?: "Not Found") //nullable

    //get all keys, all values
    println("Get all keys, all values===")
    val keys =map4.keys
    println(keys)
    val values : Collection<Int> = map4.values
    println(values)
    val values2 :List<Int> = map4.values.toList()
    println(values2)

    println("Travel===")
    for(data in map4){
        println(data)
        println("key = ${data.key}, value= ${data.value}")
    }

    map4.forEach { key, v ->  println("key = ${key}, value= ${v}") }

    println("Contains===")
    println(map4.contains("Apple"))
    println(map4.containsKey("Pear"))
    println(map4.containsValue(80))





}