import kotlin.random.Random

class RandomNumber {
    /*相當於static 的方法*/
    companion object {
        fun getNumbers(_num: Int = 1): IntArray {
            var num = if (_num < 1) 1 else _num
            var numbers = IntArray(num).apply {
                for (i in this.indices) {
                    this[i] = Random.nextInt(1, 11)
                }
            }
            return numbers
        }
    }
}

class NewDice{
    /*擲骰子*/

    //要實作物件才能取得rolledValue
    val rolledValue
        get() =(1..6).shuffled().first()

    companion object{
        fun randomValue() =println("Random value = ${(0 ..50).random()}")

    }
}

class User(val name: String){
    /*透過static 可以建立一個user 的物件*/
    companion object{
        const val TAG="myTag"
        fun create(name: String): User{
            return User(name) //建構一個user 後回傳
        }
    }
    fun userInfo()=println("Tag = $TAG, name= $name")
}

open class  Fragment{

}

class DetailFragment :Fragment(){
    var param1: String? =null
    var param2: String? =null
    companion object{
        fun newInstance(_param1: String, _param2: String) : DetailFragment{
            /*回傳一個物件，並同時設定屬性*/
            return DetailFragment().apply {
                param1=_param1
                param2=_param2
            }

        }
    }

}




fun main() {

    val myFrag=DetailFragment.newInstance("color", "black")
    println(myFrag.param1)
    println(myFrag.param2)




    /*類似於class static 方法，可以不用建構物件直接使用該方法*/
    var numbers = RandomNumber.getNumbers(5)
    for (i in 0 until numbers.size)
        print("${numbers[i]} ,")

    println()

    val randVlaue =NewDice.randomValue()
    val dice=NewDice().rolledValue
    println("Dice value= $dice")

    println()

    val user1=User.create("John")
    user1.userInfo()
    val user2=User.create("Mary")
    user2.userInfo()

    val user3=User("Lily")
    user3.userInfo()

}