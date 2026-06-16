class Info (var name:String, var age:Int){

    var email="ab@gmail.com"
    var phone="123456789"
    var id =0

    /*次建構式, this(xxxxxxxx) 相當於java 的this 建構子
     * 次建構子不能做參數的宣告(var/val)
     * : this 後的會呼叫主建構式，也可以加入logic
     */
    constructor(_name1: String, _age1: Int, _email1: String)
    : this(name=_name1, age=_age1){
        this.email=_email1
    }
    //: this() 呼叫的是其他的次建構子，但最後都會呼叫主建構子
    constructor(_name2: String, _email2: String, _age2: Int, _phone2: String)
            : this(_name2,_age2, _email2){
        this.phone=_phone2
    }

    constructor(_name3: String, _age3: Int, _id:Int)
            : this(_name3, _age3){
                this.id=_id
            }

    fun dataPrint(){
        println("name= $name, id=$id, age= $age, email= $email, phone= $phone")
    }
}

class CarInfo(val brand: String, val model: String, var year: Int, var speed:Int=0){

    constructor(_brand: String, _model: String) :this(_brand, _model, 2026, 30)

    constructor(_brand: String, _model: String, _year:Int) :this(_brand, _model, _year, 90)

    fun carPrint(){
        println("Car info: $brand $model in ($year), current speed: $speed km/h")
    }

    fun accelerate(increase: Int){
        val currentSpeed = speed
        speed+= increase
        println("current speed $currentSpeed accelerated to $speed km/h")
    }
}