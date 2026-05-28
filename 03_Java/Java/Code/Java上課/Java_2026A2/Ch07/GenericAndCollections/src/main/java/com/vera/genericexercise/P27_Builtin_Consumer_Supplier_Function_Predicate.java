package com.vera.genericexercise;


import java.util.function.Consumer;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.function.Supplier;

public class P27_Builtin_Consumer_Supplier_Function_Predicate {
    static void main(String[] args) {
        /*Consumer 裡有一個抽象方法 accept
        * 以及一個預設方法 addThen
        * Lambda 只能實現抽象方法，所以只會實現accept
        * */
        Consumer<String> cs=(String str)-> System.out.println(str); //Print string
        Consumer<String> cs2=(String str)-> System.out.println(str.length()); //get length
        Consumer<String> cs3=(String str)-> {
            String result="";
            for(int i = str.length()-1; i>=0;i--){
                result +=  str.charAt(i);
            }
            System.out.println(result);
        }; //reverse
        cs.accept("Andy");
        Consumer<String> combine= cs.andThen(cs2).andThen(cs3); //String +length
        combine.accept("Andy");

        /*Supplier*/
        Supplier<String> sp =()-> "Hi, From supplier";
        System.out.println(sp.get());

        /*Function
        * The Function interface in Java uses Generics and is defined as Function<T, R>.
        * T represents the input type (Argument).
        * R represents the result type (Return value).
        * By writing <Integer, String>, you explicitly told the Java compiler:
        * "I am creating a function that takes an Integer as an input and must return a String."
        */
        Function<Integer, String> int2String =(Integer i) -> "Number From Function: "+i;
        System.out.println(int2String.apply(1234));

        /*Predicate*/
        Predicate<Integer> isEven=number->number %2 ==0;
        System.out.println(isEven.test(123));

        Delegate<String> delegate = PrintMSG ::printGreeting;
        delegate.invoke("Vera");

    }
}

interface Delegate <T>{
    void invoke(T str);
}

class PrintMSG{
    /*
    * Make printGreeting a standalone generic method in a non-generic class.
    * The compiler can then infer T from the target Delegate<String> type.
    * */
    static<T> void printGreeting(T name){
        System.out.println("Hello, " + name + "!");
    }
}
