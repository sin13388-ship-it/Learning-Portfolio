fun main() {
    //list operation exercise
    var index:Int =1
    var mlst1=mutableListOf<Int>()
    while(true){
        println("Enter $index number :")
        var v =readln().toIntOrNull() ?: 0
        if(v==-1) break
        mlst1.add(v)
        index ++
    }
    println(mlst1)

    println("Input insert data")
    var v =readln().toIntOrNull() ?: 0

    println("Input target index")
    index=readln().toIntOrNull() ?:0

    var lastindex =mlst1.indexOf(mlst1.last())

    if (index>=0 && index <= lastindex){
        mlst1.add(index,v)
        println(mlst1)
    }else{
        println("Invalid position")
    }
}

