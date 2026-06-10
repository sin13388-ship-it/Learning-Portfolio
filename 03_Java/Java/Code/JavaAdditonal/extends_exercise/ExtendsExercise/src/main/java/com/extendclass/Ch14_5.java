package com.extendclass;

public class Ch14_5 {
    public static void main(String[] args) {
        Father father = new Father();	// 建立父類別物件
        Child child = new Child();		// 建立子類別物件
        System.out.println("列印Father類別 x : " + father.x);
        System.out.println("列印Child 類別 x : " + child.x);
        child.printInfo();
    }
}
class Father {
    protected int x = 50;
    public void printInfo() {
        System.out.println(".....1.....");
    }
}

class Child extends Father {
    protected int x = 100;
    public void printInfo() {
        System.out.println("父x="+super.x);
        System.out.println("子x="+x);
        super.printInfo();
    }
}