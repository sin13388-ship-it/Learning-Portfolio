import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.Job
import kotlinx.coroutines.SupervisorJob
import kotlinx.coroutines.async
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking
import kotlinx.coroutines.withContext
import java.sql.SQLOutput

fun main() {

    var scope= CoroutineScope(Dispatchers.Default+ Job())
    /*只要有一個error 另一個就無法執行*/
    scope.launch {
        delay(100)
        println("Job 1")
        error("job 1 fail")
    }
    scope.launch {
        delay(200)
        println("job2 is ok")
    }
    Thread.sleep(1000)
    println("waiting 1")
    println()


    /*supervisorJob 協同程式獨立，一個發生error 另一個還是可以執行*/
    var scope1= CoroutineScope(SupervisorJob())
    scope1.launch {
        delay(100)
        println("Job 3")
        error("job 1 fail")
    }
    scope1.launch {
        delay(200)
        println("job4 is ok")
    }
    Thread.sleep(1000)
    println("waiting 2")
    println()

    /*runBlock 可以讓main thread 等block 做完在結束*/
    runBlocking {
        val value1 =scope1.async {
            delay(100)
            println("async job 1")
            100
        }.await()
        val value2 =scope1.async {
            delay(200)
            println("async job 2")
            100
        }

        //await 會去取得數值
        println("value1= ${value1}, value2 =${value2.await()}")
        println()
    }

    // 在 Default dispatcher 上啟動協程，執行 DoEvent() 函數
    CoroutineScope(Dispatchers.Default).launch {
        DoEvent()
    }
    Thread.sleep(1000)
    println("waiting 3")
}

suspend fun DoEvent(){
    withContext(Dispatchers.Default){
        println("Do Event")
        DoJob()
        delay(200)
        println("event finished")
    }
}

suspend fun DoJob(){
    withContext(Dispatchers.IO){
        println("Do job")
        delay(100)
        println("job finished")
    }
}