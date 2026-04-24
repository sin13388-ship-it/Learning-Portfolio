package com.vera.genericexercise;

import java.util.ArrayList;
import java.util.Arrays;

public class P12_Generic_ArrayList {
    static void main(String[] args) {

        var aList =new ArrayList<Integer>( Arrays.asList(11,2,23,4,15,6,17,13,14,18,19));

        System.out.println(aList);
        aList.remove(1);
        System.out.println(aList);
        aList.subList(4,7+1).clear(); //左閉右開 (4~7 會被清除)
        System.out.println(aList);
        aList.removeIf(e->e>10); //(e) -> e>10
        System.out.println(aList);
        aList.removeAll(Arrays.asList(4,2)); //沒有也不會報錯
        System.out.println(aList);
        aList.addAll(Arrays.asList(11,2,23,4,15,6,17,13,14,18,19));
        System.out.println(aList);
        System.out.printf("Index of 11: %d , Index of 17 %d", aList.indexOf(11),aList.indexOf(17));
        aList.clear();
        System.out.println(aList);


    }
}
