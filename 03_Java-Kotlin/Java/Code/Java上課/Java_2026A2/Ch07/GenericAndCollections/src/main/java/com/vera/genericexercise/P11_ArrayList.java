package com.vera.genericexercise;

import java.util.ArrayList;
import java.util.Arrays; /*陣列相關*/

public class P11_ArrayList {
    /*你應該要知道的ArrayList用法*/
    static void main(String[] args) {
        var iList =new ArrayList<Integer>(Arrays.asList(1,2,3,4,5));
        ArrayList<Double> dList =new ArrayList<>(Arrays.asList(1.23,3.45,5.67,7.89));
        System.out.println("iList = " + iList);
        System.out.println("dList = " + dList);
        /*Add*/
        iList.add(6);
        System.out.println("iList add = " + iList);
        iList.add(3,7);
        System.out.println("iList add with index = " + iList);
        /*Replace*/
        iList.set(3,8);
        System.out.println("iList replace  = " + iList);
        /*AddRange*/
        dList.addAll(Arrays.asList(5.67,7.89,10.11));
        System.out.println("dList addAll = " + dList);
        dList.addAll(1, Arrays.asList(9.99,9.89,9.79));
        System.out.println("dList addAll = " + dList);
        dList.remove(2);
        System.out.println("dList addAll = " + dList);
    }
}
