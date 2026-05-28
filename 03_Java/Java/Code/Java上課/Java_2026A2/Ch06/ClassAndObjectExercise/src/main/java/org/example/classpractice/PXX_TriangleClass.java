package org.example.classpractice;

public class PXX_TriangleClass {


    static void main(String[] args) {
        Triangle smallTriangle =new Triangle(3,5);
        System.out.printf("the Area is %f \n", smallTriangle.getArea());
    }

}
class Triangle
{
    double base=0;
    double heigh=0;
    Triangle(double base, double heigh ){
        this.base=base;
        this.heigh=heigh;
    }
    double getArea(){
        return base * heigh /2;
    }
}