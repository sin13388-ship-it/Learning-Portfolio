interface IntfA{
    var name: String
    var id : Int
    fun show(){
        println("id= $id, name= $name")
    }
}
interface IntfB{
    var math: Int
    var eng : Int
    fun show(){
        println("math= $math, eng= $eng")
    }
}

class Report(_name:String, _id:Int, _math:Int, _eng:Int) : IntfA, IntfB{
    override var name: String =_name

    override var id: Int =_id

    override fun show() {
        // 使用super 呼叫介面裡的方法
       super<IntfA>.show()
        println("Score: ")
        super<IntfB>.show()
    }
    override var math: Int= _math
    override var eng: Int =_eng
}

fun main() {

    var mary=Report("Mary", 1001, 90, 85)
    mary.show()

}