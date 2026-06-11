import java.util.Locale

class PlayerClass {
    /*必須初始化*/
    var name: String =""
    var score: Int =0

    private var newName: String =""
    private var newScore: Int=0
    fun setData(newName: String, newScore: Int =0) {
        this.newName = newName
        this.newScore = newScore
    }

    fun showNew(){
        println("$newName, score: $newScore")
    }

    fun show(){
        println("name= ${name}, score= ${score}")
    }
}

class ToUpper{
    //getter, setter 要直接寫在atttribute 的下面
    //不能有兩個getter
    var str: String=""
        set(value){
            if (value.isEmpty())
                field ="No data" //回傳的變數名稱只能用'field'
            else
                field= value.uppercase(Locale.getDefault())
        }
        //get() = "Hi " + field
        get(){
            return "transfer data : $field"
        }
}
