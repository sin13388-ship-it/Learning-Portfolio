package com.vera.genericexercise;

import java.util.Arrays;
import java.util.Vector;

public class P33_Vector_Collection {
    static void main(String[] args) {
        Vector<String> vector=new Vector<>();
        vector.add("Eric");
        vector.add("Daniel");
        System.out.println(vector);

        Vector<Integer> vector2 =new Vector(Arrays.asList(3,4,5,6));
        System.out.println(vector2);
    }
}
