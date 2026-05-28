package InterfaceExercise;

public class P61_ComparableInterface {
    static void main(String[] args) {
        /*Java 提供可以比較的介面
        * 大寫的Integer, Double, ...etc. 是類別
        * 為自己的類別implements compare 介面
        * implements Comparable<自己的類別>
        * class 自己類別名稱 implements Comparable<自己類別名稱>
        * */

        String s1="Andy";
        String s2="Bill";
        int result;
        result=s1.compareTo(s2);
        System.out.println("s1 compare to s2 =" + result);

        Integer num1 =123;
        Integer num2 =456;
        result=num1.compareTo(num2);
        System.out.println("num1 compare to num2 =" + result);

        Rect r1 =new Rect(12, 54);
        Rect r2 =new Rect(22, 54);
        result=r1.compareTo(r2);
        System.out.println("r1 compare to r2 =" + result);


    }
}

class Rect implements Comparable<Rect>{
    int length;
    int width;
    Rect(int length, int width){
        this.length=length;
        this.width=width;
    }
    int getArea(){
        return length * width;
    }
    @Override
    public int compareTo(Rect o) {
        int res =0;
        if(getArea() > o.getArea()) {
            res =1;
        } else if (getArea() == o.getArea()) {
            res =0;
        }else {
            res=-1;
        }
        return res;
    }
}
