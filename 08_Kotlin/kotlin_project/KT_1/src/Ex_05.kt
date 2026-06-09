fun main() {
    /*Month Revenue Analysis*/

    val revenue = arrayOf(
        intArrayOf(120, 135, 150, 140, 160, 180, 190, 210, 200, 195, 220, 250), // A店
        intArrayOf(100, 110, 130, 145, 155, 170, 185, 195, 205, 215, 225, 240), // B店
        intArrayOf(90, 105, 120, 130, 145, 160, 175, 185, 190, 200, 210, 230),  // C店
        intArrayOf(110, 125, 140, 150, 165, 175, 180, 205, 210, 220, 235, 260)  // D店
    )

    /*Q1 計算每間分店 12 個月的總營收及計算每間分店平均月營收*/
    println("A店全年營收： ${revenue[0].sum()}萬元, 平均月營收：  ${revenue[0].average()}")
    println("B店全年營收： ${revenue[1].sum()}萬元, 平均月營收：  ${revenue[1].average()}")
    println("C店全年營收： ${revenue[2].sum()}萬元, 平均月營收：  ${revenue[2].average()}")
    println("D店全年營收： ${revenue[3].sum()}萬元, 平均月營收：  ${revenue[3].average()}")
    println()

    /*Q2 比較四間分店的全年總營收,找出全年營收最高的分店*/
    val totalList= listOf<Int>(revenue[0].sum(),revenue[1].sum(),revenue[2].sum(),revenue[3].sum())
    println("全年營收最高分店： ${
        when(totalList.indexOf(totalList.max())){
            
            0-> "A"
            1-> "B"
            2-> "C"
            else -> "D"            
        }
    }")
    println("全年營收： ${totalList.max()}萬元")
    println()

    /*Q3 統計所有分店在每個月份的總營收*/
    var c:Int =0

    var totalList2=mutableListOf<Int>()
    for (i in 0.. 11){
        var t : Int =0
       revenue.forEach { row-> t+=row[i]}
        println("${i+1} 總營收:  $t 萬元" )
        totalList2.add(t)
    }
    println()

    /*Q4 比較 12 個月份的總營收 , 找出全公司營收最高的月份*/
    println("全公司營收最高月份： ${totalList2.indexOf(totalList2.max())+1}月")
    println("總營收：${totalList2.max()} 萬元")

}