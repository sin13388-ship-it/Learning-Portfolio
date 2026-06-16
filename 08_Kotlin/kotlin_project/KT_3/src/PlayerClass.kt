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

class Player{
    /*姓名轉大寫*/
    /*Mail 轉小寫*/
    private  var phone="123456"
    /*getter , setter 要緊接於下方*/
    var name="Mary"
        get()= field.uppercase()
        set(value){field=value.trim()}
    var id:Int =1
        get()=field+100
        set(value){
            if(value>10){
                println("id is error")
                field=0
            }else{
                field=value
            }
        }
    var email="AAA@gmail.com"
        get()=field.lowercase()
        /*可以新增一些資料驗證的方法*/
        set(value){
            if(value.length<5){
                println("Length is error")
                field="error"
            }else{
                field=value
            }
        }
    fun attrPrint(){
        println("name= $name, id= $id, email= $email, phone=$phone ")
    }
    fun changePhone(phone: String){
        this.phone=phone
    }
}

class NewPlayer1(_name:String, _age: Int, _isBlessed: Boolean){
    /*attribute 另外拉出來宣告
    * 如果要用getter, setter 的話，還是需要用此方法
    * */
    var name=_name
        /*初始化的數值不會進入到getter/ setter 的判斷*/
        get()= field.lowercase()
        set(value){
            if(value.length >10){
                println("name is too long")
                field="Error"
            }else{
                field=value
            }
        }
    var age=_age
    var isBlessed=_isBlessed
    init{
        println("do init")
    }
    fun attPrint(){
        println("name= $name, age= $age, isBlessed= $isBlessed")
    }
}

class NewPlayer2(var name: String, var age: Int, var healthPoint: Int=80)
{
    //Health point 有給預設值
    //主建構子已經宣告，此處就不用額外宣告
    fun attPrint(){
        println("name= $name, age= $age, healthPoint= $healthPoint")
    }
}

class NewPlayer3(_name: String, var age: Int=50, var healthPoint: Int=70)
{
    //某個參數想使用屬性的話，可以不用在主建構式用var/ val
    var name=_name
        get()=field.uppercase()
    fun attPrint(){
        println("name= $name, age= $age, healthPoint= $healthPoint")
    }

}