package AbstrctClassAndMethod;

public class P52_Abstract_Class_Demo {
    static void main(String[] args) {
        Rectangle R =new Rectangle(10,20,30,40);
        System.out.println("x = "+ R.x + " Y =" + R.y + " width = "+ R.width+ " length = " + R.length + " computeArea = " + R.computeArea());
        Geometry G =new Rectangle(30,40,50,60);
        System.out.println("x = "+ G.x + " Y =" + G.y + " width = "+ ((Rectangle)G).width + " length = " +((Rectangle)G).length + " computeArea = " + G.computeArea());
    }
}

abstract class Geometry{
    int x, y;
    Geometry(int x, int y) {
        this.x=x;
        this.y=y;
    }
    abstract int computeArea();
}
class Rectangle extends Geometry{
    int width, length;
    Rectangle(int x, int y, int width, int length){
        super(x,y);
        this.width=width;
        this.length=length;
    }
    int computeArea(){
        return  width * length;
    }
}