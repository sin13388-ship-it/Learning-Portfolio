package org.example;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    static void main() {
        Person<String, Integer> staff1 =new Person<>("Andy",123);
        Person<String, Integer> staff2 =new Person<>("Bill",456);
        staff1.showInfo();
        staff2.showInfo();
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