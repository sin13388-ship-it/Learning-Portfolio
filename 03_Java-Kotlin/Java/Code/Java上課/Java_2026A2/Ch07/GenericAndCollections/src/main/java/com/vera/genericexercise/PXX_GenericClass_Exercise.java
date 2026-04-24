package com.vera.genericexercise;

public class PXX_GenericClass_Exercise {
    static void main(String[] args) {
        Person<String, Integer> staff1 =new Person<>("Andy",123);
        Person<String, Integer> staff2 =new Person<>("Bill",456);
        staff1.showInfo();;
        staff2.showInfo();;

    }
}
class Person<N, I>{

    private N name;
    private I id;

    Person(N name, I id){
        this.name=name;
        this.id=id;
    }
    void showInfo(){
        System.out.println("Person : " + name);
        System.out.println("ID : " + id);
    }
}
