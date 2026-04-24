package com.vera.genericexercise;

import java.util.ArrayList;
import java.util.Arrays;

public class P13_ArrayList_String {
    static void main() {
        /*ArrayList  與string 的連用*/
        ArrayList<String>aList =new ArrayList<>(Arrays.asList("Andy", "Bill", "Carol"));
        System.out.println(aList);
        aList.add("Eric");
        System.out.println(aList);
        aList.add(1, "Insert at 1");// Insert 是插入
        System.out.println(aList);
        aList.set(1, "Modified at 1"); //set 會修改原本的內容
        System.out.println(aList);
        aList.addAll(Arrays.asList("Grace", "Robert")); //從頭開始插入
        System.out.println(aList);
        aList.addAll(1,Arrays.asList("Ted", "Vicky")); //從1 開始插入
        System.out.println(aList);
        System.out.println(aList.size());

        /*移除字元長度>=5 的元素*/
        aList.removeIf((e)-> e.length()>=5);
        System.out.println(aList);

        /*移除特定字串*/
        aList.removeAll(Arrays.asList("Andy", "Ted"));
        System.out.println(aList);

        /*Index of*/
        /*找不到會回傳-1*/
        System.out.printf("Index of 'Andy': %d, Index of 'Bill' : %d \n",aList.indexOf("Andy"), aList.indexOf("Bill"));

        /*Get index*/
        System.out.printf("Get(index =1) : %s \n", aList.get(1));
    }
}
