package org.example.classpractice;

public class P18_Inheritance_this_super_CTOR {
    static void main(String[] args) {

        Geometry geometry=new Geometry(100,200);
        geometry.printInfo();

        Rectangle rectangle =new Rectangle(23, 56, 10, 20);
        rectangle.printInfo();
    }
}
class Geometry{
    int x;
    int y;
    Geometry(){}
    Geometry(int x, int y) {
        this.x=x;
        this.y=y;
    }
    void printInfo(){
        System.out.printf("x = %d | y = %d \n", x ,y);
    }
}
class Rectangle extends Geometry{

    int length;
    int width;
    /*
    * 建構前會先呼叫super()
    * */
    Rectangle(int length, int width, int x, int y){
        super(x,y);
        this.length=length;
        this.width=width;
    }
    void printInfo(){
        super.printInfo(); /*取得父類別的方法*/
        System.out.printf("length = %d | width = %d " , length ,width);
    }
}
