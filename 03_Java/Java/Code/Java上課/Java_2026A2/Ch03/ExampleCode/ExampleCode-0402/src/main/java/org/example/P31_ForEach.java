package org.example;

import java.util.Arrays;

public class P31_ForEach {
    static void main(String[] args) {
        /*
        * For each
        * for(int name : collections name)
        * {
        *   //statement
        * }
        * */

        int[] collections ={0,1,2,3,4,5,6,7,8,9};

        for(int _element : collections) {
            System.out.print(_element);
        }

        System.out.println();

        for(int _element : collections) {
            if(_element ==8) break; //跳開最靠近的loop
            if(_element==4) continue; //直接跳過，next _element
            System.out.print(_element);
        }
        System.out.println();
    }
}
