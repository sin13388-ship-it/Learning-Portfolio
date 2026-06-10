package com.extendclass;

import java.util.Scanner;

public class Ch14_3 {
    /*Inheritance  class*/
    static void main(String[] args) {
        Manager m =new Manager();
        m.salary=30000;
        m.bonus=1000;
        m.showSal();

    }

}

class  Emp{
    public int salary;
    public void showSal(){
        System.out.println(salary);
    }
}
class Manager extends Emp{
    public int bonus;
    public void showBonus(){
        System.out.println("bonus:"+bonus);
    }
    @Override
    public void showSal(){
       // System.out.println(salary);
        super.showSal();
        System.out.println("bonus:"+bonus);
    }

}
