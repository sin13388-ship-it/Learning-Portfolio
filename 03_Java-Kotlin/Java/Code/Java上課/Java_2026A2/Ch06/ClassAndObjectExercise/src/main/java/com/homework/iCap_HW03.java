package com.homework;

public class iCap_HW03 {

    static void main(String[] args) {
        double radius =5.67;
        Circle circle =new Circle(radius);
        System.out.println("The circle area is = " + circle.getArea());
    }
}

class Circle{
    private  double radius;

    Circle(double radius){
        this.radius=radius;
    }

    double  getArea(){
        return radius * radius * Math.PI;
    }
}
