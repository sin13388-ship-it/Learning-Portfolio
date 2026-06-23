package vera.generic.exercise;

/*Generic
* 規定要用Integer, Double ...etc 類別
*
* */
public class GenericExercise {
    static void main(String[] args) {
        //Integer
        MyDataGeneric<Integer> mydata=new MyDataGeneric<>();
        mydata.setObject(10);
        System.out.println("The value= " + mydata.getObject());

        //Double
        MyDataGeneric<Double> mydata2=new MyDataGeneric<>();
        mydata2.setObject(10.3);
        System.out.println("The value= " + mydata2.getObject());

        //String
        MyDataGeneric<String> mydata3=new MyDataGeneric<>();
        mydata3.setObject("\"Generic string\"");
        System.out.println("The value= " + mydata3.getObject());
    }
}
class MyData {
    private Integer obj1;// 整數資料
    private Double obj2;// 浮點數資料
    //overload，多形
    void setobj(Integer obj) {
        this.obj1 = obj;					// 設定整數
    }
    void setobj(Double obj) {
        this.obj2 = obj;					// 設定整數
    }
    //取得資料
    Integer getobj1() {
        return this.obj1;				// 回傳整數
    }
    Double getobj2() {
        return this.obj2;				// 回傳整數
    }
}

class MyDataGeneric<T>{

    private T object;
    public void setObject(T obj){
        this.object=obj;
    }
    T getObject(){
        return this.object;
    }
}

