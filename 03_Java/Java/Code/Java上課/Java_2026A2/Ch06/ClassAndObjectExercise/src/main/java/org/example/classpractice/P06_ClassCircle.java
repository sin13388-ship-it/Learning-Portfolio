package org.example.classpractice;

public class P06_ClassCircle {

    static void main(String[] args) {

        Circle circle1=new Circle(); /*內定建構子*/
        Circle circle2=new Circle(2.3); /*標準建構子*/
        System.out.printf("The perimeter of circle1 is %f \n", circle1.getPerimeter());
        circle1.setRadius(2.3);
        System.out.printf("The perimeter of circle1 is %f \n", circle1.getPerimeter());
        System.out.printf("The perimeter of circle2 is %f \n", circle2.getPerimeter());

    }

}
class Circle{
    double radius= 0;


    Circle(){} /*內定建構子*/
    /*標準建構子*/
    Circle(double radius){
        this.radius=radius;
    }

    double getPerimeter(){
        return radius * 2 * Math.PI;
    }
    void setRadius(double r){
        this.radius=r;
    }

}