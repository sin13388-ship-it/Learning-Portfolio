fun main() {
    /*Map Practice*/


    var listData= mutableListOf< MutableMap<String, String>>()

    var stud1 = mutableMapOf<String, String> ("name" to "Mary", "email" to "mary@iot.com", "phone" to "1111")
    listData.add(stud1)
    println(listData)

    println()
    listData.clear()

    val nameArray =arrayOf("Mary","John","Jack","AAA")
    val emailArray =arrayOf("mary@iot.com","john@iot.com","jack@iot.com","aaa@iot.com")
    val phoneArray =arrayOf("1111","2222","3333","4444")


    //put data

    val stName=arrayOf("Mary","John","Jack","AAA")
    val stId= arrayOf(100,101,102,103)
    val stAge= arrayOf(20,21,22,23)
    val stEmail=arrayOf("mary@iot.com","john@iot.com","jack@iot.com","aaa@iot.com")
    var stList= mutableListOf< MutableMap<String, Any>>()

    for(i in 0.. stName.size-1){
        //Initialize object
        val data =mutableMapOf<String, Any>()
        data.put("name",stName[i])
        data.put("ID",stId[i])
        data.put("Age",stAge[i])
        data.put("stEmail",stEmail[i])
        stList.add(data)
    }
    println(stList)
}