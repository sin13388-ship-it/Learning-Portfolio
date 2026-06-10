package com.extendclass;

public class Ch14_12 {
    static void main(String[] args) {

        Bird2 bird =new Bird2("cici");
        bird.eat();
        bird.sleep();
        bird.flying(); //bird method

        Dog2 dog =new Dog2("Haly");
        dog.eat();
        dog.barking();
        dog.sleep();

    }
}
class Animal2 {
    protected String name; // 宣告protected存取修飾符定義動物名字

    public void eat() { // Animal方法eat
        System.out.println(name + "正在吃食物");
    }

    public void sleep() { // Animal方法sleep
        System.out.println(name + "正在睡覺");
    }
}

class Dog2 extends Animal2 {
    Dog2(String name) { // Dog建構方法
        this.name = name; // 呼叫父類別屬性
    }
    public void barking() { // Dog類別自有的方法barking
        System.out.println(name + "正在叫"); // 可以繼承name了
    }
}

class Bird2 extends Animal2 {
    Bird2(String name) { // Bird建構方法
        this.name = name; // 呼叫父類別屬性
    }
    public void flying() { // Bird類別自有的方法flying
        System.out.println(name + "正在飛"); // 可以繼承name了
    }
}