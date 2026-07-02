import kotlin.concurrent.thread

fun taskFun()
{
    for(i in 1..5){
        println("${Char(i+64)}")
        Thread.sleep(500)
    }
}

/*繼承Thread 的類別
* 有固定結構，要去override run()
* */
class MyThread: Thread()
{
    override fun run() {
        super.run()
        println("Thread start.")
        for(i in 10..15){
            println("Running $i")
            sleep(100)
        }
        println("Thread end")
    }
}

fun main() {
    MyThread().start()
    /*寫法1*/
    val thd1= Thread{taskFun()}
    thd1.start()
    /*寫法2*/
    var thd2= Thread({
        for(i in 1..5){
            println("${Char(i+0x30)}")
            Thread.sleep(300)
        }
    })
    thd2.priority= Thread.MAX_PRIORITY
    thd2.start()

    /*寫法3*/
    var thd3= Thread({
        for(i in 1..5){
            println("${Char(i+0x61)}")
            Thread.sleep(200)
        }
    }).start()

}