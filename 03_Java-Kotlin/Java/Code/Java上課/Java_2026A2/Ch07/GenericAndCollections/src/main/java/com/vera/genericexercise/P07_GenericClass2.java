package com.vera.genericexercise;

public class P07_GenericClass2 {
    static void main(String[] args) {
        Point<String> position=new Point<>("Taipei", "Tau-yuan");
        Point<Float> planPoint=new Point<>(3.5f,4.7f);
        position.showInfo();
        planPoint.showInfo();

        compoundGenericClass<String, Integer> positionAndPostCode = new compoundGenericClass<>("Taipei", 235);
        positionAndPostCode.showInfo();
    }
}

class Point <T>{
    T x,y ;

    Point(T x, T y){
        this.x=x;
        this.y=y;
    }

    void showInfo(){
        System.out.println("x= " + x +" y= " + y);
    }
}
class compoundGenericClass<T,Q>{

    T x;
    Q y;

    compoundGenericClass(T x, Q y) {
        this.x=x;
        this.y=y;
    }

    void showInfo(){
        System.out.println("x= " + x +" y= " + y);
    }
}