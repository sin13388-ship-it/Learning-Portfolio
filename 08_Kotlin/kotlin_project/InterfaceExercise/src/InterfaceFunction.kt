fun interface Action{
    fun execute()
}

fun runAction(action: Action){
    println("Starting runAction")
    action.execute()
    println("end of runAction")
}

class DoAction:Action{
    override fun execute() {
        println("class implement")
    }
}

fun interface StudentWork{
    fun execute(name : String)
}

class TaskClass(val name: String){
    fun handleTask(task:StudentWork){
        println("Task start")
        task.execute(name)
        println("Task end")
    }
}



fun main() {

    val myTask = TaskClass("John")
    myTask.handleTask(object : StudentWork{
        override fun execute(name: String) {
            println("myTask implement 1 - ${name}")
        }
    })
    println()
    myTask.handleTask { name : String -> println("myTask implement 2 -$name") }
    println()
    myTask.handleTask { println("myTask implement 2 -$it") } //可以用it 替代
    println()

    /*在方法中傳入interface，用object實作*/
    runAction(object : Action {
        override fun execute() {
            println("object implement")
        }
    })
    println()

    /*like lambda, fun interface 可以被視為匿名函式
    * 可以寫在 () 外
     */
    runAction() {
        println("function implement 1")
    }
    println()

    /*只有一個的時候可以不用()*/
    runAction {
        println("function implement 2")
    }
    println()

    /*正規作法*/
    runAction { DoAction() }

}