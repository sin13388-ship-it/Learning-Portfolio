package com.vera.genericexercise;

import java.util.ArrayList;

public class P17_Generic_Stack {
    /*stack 的基本方法
    * push
    * pop
    * peek
    * */

    static void main() {

        /* 使用Generic Class + Arraylist 實現堆疊
        */


        System.out.println("===String stack===");

        GenericStack<String> strStack =new  GenericStack<>();

        strStack.push("Andy");
        strStack.push("Bill");
        strStack.push("Carol");
        strStack.showInfo();

        var peekValue =strStack.peek();
        System.out.println("Peek : " + peekValue);
        strStack.showInfo();

        var popValue=strStack.pop();
        System.out.println("Pop : " + popValue);
        strStack.showInfo();

        System.out.println("===Double stack===");

        GenericStack<Double> intStack =new  GenericStack<>();

        intStack.push(1.23);
        intStack.push(4.56);
        intStack.push(7.89);
        intStack.showInfo();

        var peekValue2 = intStack.peek();
        System.out.println("Peek : " + peekValue2);
        intStack.showInfo();

        var popValue2= intStack.pop();
        System.out.println("Pop : " + popValue);
        intStack.showInfo();


    }
}
class GenericStack<T>{
    private ArrayList<T> list =new ArrayList<>();
    int getSize(){
        return  list.size();
    }
    T peek(){
        return list.getLast(); /*查看最上層*/
    }
    void push(T element){
        list.add(element);
    }
    void showInfo(){
        System.out.println(list);
    }
    T pop(){
        var e = list.getLast();
        list.remove(e);
        return e;
    }

}
