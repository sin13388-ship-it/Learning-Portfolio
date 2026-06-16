/*類別繼承練習
*
* 父類別當中需要被覆寫的類別，要增加open修飾字, 子類別要寫override
*
* */

open class PClass(pname:String) {
    var name=""

    init{
        name=pname
    }
    fun show(){
        println("name= $name")
    }
}

class CClass(pname :String, page: Int):PClass(pname)
{
    /*
    * PClass(pname) 裡的 pname 是在呼叫父類別 PClass 的建構子,
    * 這裡的 pname 指的就是前面 CClass 剛剛宣告的那個參數,把它的值傳給 PClass。
    * */

    var age=0
    init{
        age=page
    }
    fun show1(){
        super.show()
        println("name= $name, age= $age")
    }
}

open class PClass1(pName: String){
    /*override
    * 要得都要+ open 修飾字
    * */

    open var name=""
    init{
        name=pName
    }
    open fun show(){
        println("PClass name= $name")
    }
}

class CClass1(pName: String, age:Int):PClass1(pName){

    override var name: String="" //子類別的名稱會覆蓋到父類別

    var age =0
    init{
        name=pName.uppercase()
        this.age=age
    }
    override fun show(){
        super.show()
        println("CClass name= $name, age= $age")
    }

}

/*多重繼承*/
open class Game(val player: String, _level: Int){
    open var level = _level
    open val score = 60
    open fun dataPrint(){
        println("Game player = $player, level :$level, score: $score")
    }
}

open class CGame(player: String, score:Int):Game(player, 10){

    override var level=5
    override var score =score

    override fun dataPrint() {
        super.dataPrint()
        println("CGame player= $player, level= $level, score= $score")
    }
}

class CCGame(player:String, _level: Int) : CGame(player, 100){

    override var level=_level //孫類別去覆寫原始類別

    override fun dataPrint() {
        super.dataPrint()
        println("CCGame player = $player, level =$level, score= $score")
    }
}
