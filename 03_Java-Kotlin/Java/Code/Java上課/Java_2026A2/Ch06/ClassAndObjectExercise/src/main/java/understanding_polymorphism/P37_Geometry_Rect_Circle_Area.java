package understanding_polymorphism;

public class P37_Geometry_Rect_Circle_Area {

    static void main(String[] args) {
        Geometry g=new Geometry();
        Rectangle r =new Rectangle(1.23, 4.56);
        Circle c =new Circle(7.89);
        System.out.println("g area: " + g.computeArea());
        System.out.println("r area: " + r.computeArea());
        System.out.println("c area: " + c.computeArea());
        System.out.println("-----------------------------------");
        System.out.println("g area: " + Geometry.getArea(g));
        System.out.println("r area: " + Geometry.getArea(r));
        System.out.println("c area: " + Geometry.getArea(c));
    }
}
class Geometry{
    double computeArea(){
        return 0;
    }
    static double getArea(Geometry g){ /*Parent type*/
         /*注意先後順序*/
        if (g instanceof  Rectangle){
            System.out.println("Rectangle : width :  " + ((Rectangle) g).width + " length : " + ((Rectangle) g).length );
        } else if (g instanceof  Circle) {
            System.out.println("Radius : " + ((Circle) g).radius);
        } else {
            System.out.println("Geometry : " + "No Attribute at all");
        }
        /*Java last binding method, 會自己binding對應，只有方法會*/
        /*如果子類別沒有override 則會往上找到最後一個*/
        return g.computeArea();
    }
}
class Rectangle extends Geometry{
    double width;
    double length;
    Rectangle(double width, double length){
        this.width=width;
        this.length=length;
    }
    double computeArea(){
        return  width * length;
    }
}

class Circle extends Geometry{
    double radius;

    Circle (double radius){
        this.radius=radius;
    }
    double computeArea(){
        return radius * radius * Math.PI;
    }
}