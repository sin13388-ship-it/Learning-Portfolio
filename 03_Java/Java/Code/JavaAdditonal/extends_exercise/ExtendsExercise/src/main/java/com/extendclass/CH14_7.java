package com.extendclass;

public class CH14_7 {
    static void main(String[] args) {
        Dog d =new Dog("Haly");
        d.eat();
        d.sleep();
    }
}
class Animal {
    private String name ; // 定義動物名字
    Animal(String name){
        this.name = name;
        System.out.println("Animal....");
    }
    public void eat() { // Animal方法eat
        System.out.println(name + "正在吃食物");
    }
    public void sleep() { // Animal方法sleep
        System.out.println(name + "正在睡覺");
    }
}

class Dog extends Animal {
    Dog(String name) { // Dog建構方法
        super(name);
        System.out.println("Dog....");
    }
}
