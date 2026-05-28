package com.vera.genericexercise;

public class P06_GenericClass {

    static void main(String[] args) {
        GenericClass<Integer> iClass = new GenericClass<>(123);
        GenericClass<String> sClass =new GenericClass<>("Andy");
        System.out.println("iClass value : " + iClass.getValue());
        System.out.println("sClass value : " + sClass.getValue());

        GenericClass<Integer> iClass2 = new GenericClass<>();
        GenericClass<String> sClass2 =new GenericClass<>();
        System.out.println("iClass2 value : " + iClass2.getValue());
        System.out.println("sClass2 value : " + sClass2.getValue());
    }
}

class GenericClass <T>{
    /*泛型類別
    * 基本setter & getter*/

    private T value;
    GenericClass(){}
    GenericClass(T value){
        this.value=value;
    }
    T getValue(){
        return  value;
    }
    void setValue(T value){
        this.value=value;
    }

}