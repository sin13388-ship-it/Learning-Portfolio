
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch


fun main() {

    /*Lambda 方法*/

    var scope = CoroutineScope(Dispatchers.Default)
    scope.launch {
        repeat(300){
            println("Coroutine : $it")
            delay(300)
        }
    }

    for (count in 1..10){
        println("count1 = $count")
        Thread.sleep(1000)
    }

    /*指定方法*/
    val job= CoroutineScope(Dispatchers.Default).launch { sFun() }

    for(i in 1..10){
        println("count2= $i")
        Thread.sleep(100)

    }

}

suspend fun sFun()
{
    for (i in 100..120){
        println("${i}")
        Thread.sleep(500)
    }
}

fun Fun2()
{
    for (i in 100..120){
        println("${i}")
        Thread.sleep(500)
    }
}