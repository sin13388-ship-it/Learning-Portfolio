
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch


fun main() {

    var scope = CoroutineScope(Dispatchers.Default)
    scope.launch {
        repeat(3){
            println("Coroutine : $it")
            delay(300)
        }
    }

    for (count in 1..10){
        println("count = $count")
        Thread.sleep(200)
    }
}