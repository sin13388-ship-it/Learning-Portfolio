package Chapter09Exercise;

public class ch09_01 {
    static void main(String[] args) {
        //Overload 實作
        MyClass test =new MyClass(5);
        test.printInfo();
        MyClass test2 =new MyClass(5,6);
        test2.printInfo();
        MyClass test3 =new MyClass("Overload test");
        test3.printInfo();
    }
}
class MyClass{
    //Overload
    //Overload + 建構子
    int x,y;
    String name;
    MyClass(){}
    MyClass(int x){
        this.x=x;
    }
    MyClass(int x, int y){
        this.x=x;
        this.y=y;
    }
    MyClass(String name){
        this.name=name;
    }

    public void printInfo(){
        System.out.println("x: " +x);
        System.out.println("y: " +y);
        System.out.println("name: " +name);
    }
}
