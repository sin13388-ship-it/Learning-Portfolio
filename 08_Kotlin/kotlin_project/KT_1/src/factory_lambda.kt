fun main() {

    /*建立一個法規工廠，根據傳入的條件，回傳對應的結果
    *
    * 外層 :匿名方法傳入一個　(Int)-> Boolean lambda, 並回傳字串
    * 內層 :根據方法回傳字串結果
    * 明確寫法
    * val buyWine: ((Int) -> Boolean) -> ((Int) -> String) = { condition ->
            { age ->
                if (condition(age)) "You can buy wine" else "You are under 18"
            }
        }
    *
    * */
    val buyWine = {  condition :(Int)-> Boolean ->
        {
            age: Int->if(condition(age)) "You can buy wine" else "You are under 18"
        }
    }

    val taiwainLaw=buyWine{age :Int -> age >=18}
    val americanLaw=buyWine{age :Int -> age >=20}

    println(taiwainLaw(19))
    println(americanLaw(19))

}