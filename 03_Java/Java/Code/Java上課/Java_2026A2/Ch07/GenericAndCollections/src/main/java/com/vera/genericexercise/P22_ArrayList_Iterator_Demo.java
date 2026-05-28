package com.vera.genericexercise;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;

public class P22_ArrayList_Iterator_Demo {

    /*Iterator usage*/
    static void main() {
        ArrayList<String> fruits =new ArrayList<>(Arrays.asList("Apple", "Banana", "Cherry","Date"));
        Iterator<String> it =fruits.iterator();
        while(it.hasNext()){
            System.out.println(it.next() + "\t");
        }
        System.out.println("\nFinish");
    }
}
