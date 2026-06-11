fun main() {

    println("===takeIf, takeUnless===")
    var lst = mutableListOf<Int>(90,91,92,93,94)
    println(lst)

    // 如果符合即return
    var result =lst.takeIf {
        println("min= ${it.min()}")
        it.min()>20
    }
    println(result)
    result =lst.takeIf {
        println("min= ${it.min()}")
        it.min() <20
    }
    println(result)

    // 如果不符合即return
    result =lst.takeUnless {
        it.min() <20
    }
    println(result)

    //test book exercise

    lst = mutableListOf<Int>(92,75,67,87,94)
    println(lst)

   /*
   * takeIf -> pick 符合條件的，如果不為null，執行also裡的，最後run
   * */
    lst.takeIf {
        println("min =${it.min()}")
        it.min()<20
    }?.also {
        it.remove(it.min())
    }.run (::println)

    //Apply
    val stName=arrayOf("Mary","John","Jack","AAA")
    val stId= arrayOf(100,101,102,103)
    val stAge= arrayOf(20,21,22,23)
    val stEmail=arrayOf("mary@iot.com","john@iot.com","jack@iot.com","aaa@iot.com")
    var stList= mutableListOf< MutableMap<String, Any>>()
    for(i in 0.. stName.size-1){
        //Initialize object
        val data =mutableMapOf<String, Any>()
        //使用apply簡寫內容
        data.apply {
            put("name",stName[i])
            put("ID",stId[i])
            put("Age",stAge[i])
            put("stEmail",stEmail[i])
        }
        stList.add(data)
    }
    println(stList)

}