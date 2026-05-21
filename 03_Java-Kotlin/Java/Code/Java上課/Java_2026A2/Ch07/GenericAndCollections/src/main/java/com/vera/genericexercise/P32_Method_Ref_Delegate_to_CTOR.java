package com.vera.genericexercise;

public class P32_Method_Ref_Delegate_to_CTOR {
    static void main(String[] args) {
        /*Java 看的是：People 的建構子簽名，是否符合介面方法的簽名？*/
        DelegateCTOR delegateCTOR=People::new; //指向建構子
        delegateCTOR.create("Andy");

    }
}

class People{
    private String name;
    People(String name){
        this.name=name;
        //System.out.println(name);
    }
}
interface DelegateCTOR{
    //Return a class
    People create(String str);
}