fun main() {

    val myCar= Car("Toyota", "RAV4", 2022)
    myCar.displayInfo()

    println()

    val oilCar=OilCar("BMW", "X3", 2025 )
    oilCar.displayInfo()
    oilCar.oil(500, 15)

    println()
    val electricCar =ElectricCar("Tesla", "Model 3", 2026, 50)
    electricCar.displayInfo()
    electricCar.charge(30)
    println()

    /*只要是Car 的類別或衍生類別，都可以填入*/
    val carList =mutableListOf<Car>(myCar, oilCar, electricCar)
    carList.forEach {
        println()
        it.displayInfo() }

}
open class Car(val brand: String, val model: String, val year: Int){
    open fun displayInfo(){
        println("Car brand : $brand, model: $model, year: $year")
    }
}
/*不同的型態去繼承Car*/
class OilCar(_brand:String, _model: String, _year: Int) : Car(_brand, _model, _year)
{
    fun oil(oilCap:Int, oilConsume: Int=12){
        println("$brand $model can drive ${oilCap*oilConsume} km")
    }
}

class ElectricCar(_brand:String, _model: String, _year: Int, _battery: Int) : Car(_brand, _model, _year)
{
    var batteryCapability=_battery
    fun charge(amount: Int){
        batteryCapability=(batteryCapability+amount).coerceAtMost(100) //上限值
        println("$brand $model charged to ${batteryCapability}")
    }
}