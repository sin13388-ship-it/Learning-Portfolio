fun main() {
    //不管最終是走主建構子還是次建構子——都會建立一個全新的物件實體（配置新記憶體），而不是修改原本那個物件。
    //Primary constructor
    var info=Info("Mary", 22)
    info.dataPrint()
    //2nd constru
    info=Info("John", 30, "john22@iot.com")
    info.dataPrint()
    info=Info("Jack", "jack22@iot.com", 33, "123456")
    info.dataPrint()
    info=Info("Tina", 44, 10)
    info.dataPrint()

    println()
    var carInfo=CarInfo("Toyota", "Corolla", 2022)
    carInfo.carPrint()
    carInfo.accelerate(20)
    carInfo.carPrint()

    carInfo=CarInfo("Tesla", "Model Y")
    carInfo.carPrint()

    carInfo=CarInfo("BMW", "X3", 2025)
    carInfo.carPrint()
    carInfo.speed=50
    carInfo.accelerate(20)
    carInfo.carPrint()

}