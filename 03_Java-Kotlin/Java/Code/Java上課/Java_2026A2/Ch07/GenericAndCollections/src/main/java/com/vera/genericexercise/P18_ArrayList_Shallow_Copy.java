package com.vera.genericexercise;

import java.util.ArrayList;
import java.util.Arrays;

public class P18_ArrayList_Shallow_Copy {

    static void main() {
        /* 淺層copy
        * 會指向同一個物件
        * 當被複製者發生改變，複製的類別也會改變 ?
        * 在執行shallow copy 的時候如果是primitive type 會是值複製
        * However, if a field is an object (like ArrayList, String, or a custom class),
        * Java only copies the reference (the memory address).
        * 因為String 具有不變性，所以當改變字串的時候，記憶體會另外在某個記憶體生成，並指向他
        * ArrayList　是可變的，所以會直接指向那個位址
        **/

        ArrayList<String> hobbies =new ArrayList<>(Arrays.asList("Reading", "Playing video game"));
        Person2 employee1 =new Person2("Andy", hobbies);
        System.out.println("employee1.hobbies = " + employee1.hobbies);

        Person2 employee2 =employee1.clone();
        System.out.println("employee2.hobbies = " + employee2.hobbies);

        employee1.name="Lily";
        employee1.hobbies.add("Writing");
        System.out.println("employee1.hobbies = " + employee1.hobbies);
        System.out.println("employee2.hobbies = " + employee2.hobbies);

        System.out.println("employee1.name = " + employee1.name);
        System.out.println("employee2.name = " + employee2.name);
    }
}

class Person2 implements Cloneable{

    String name;
    ArrayList<String> hobbies; // Arraylist 可以做為屬性

    Person2(String name, ArrayList<String> hobbies){
        this.name=name;
        this.hobbies=hobbies;
    }

    @Override
    public Person2 clone() {
        try {
            return (Person2) super.clone();
        } catch (CloneNotSupportedException e) {
            throw new AssertionError();
        }
    }
}