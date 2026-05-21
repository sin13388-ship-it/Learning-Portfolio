package com.vera.genericexercise;

import java.util.*;

public class P39_ArrayList_LinkedList_Vector {
    static void main(String[] args) {
        List<String> alist =new ArrayList<>();
        alist.addAll(Arrays.asList("Apple","Banana","Cheery","Apple"));
        System.out.println(alist);
        //無序不重複
        Set<String> aSet=new HashSet<>(Arrays.asList("Apple","Banana","Cheery","Apple"));
        System.out.println(aSet);
        //有序不重複
        Set<String> cSet=new TreeSet<>(Arrays.asList("Cheery","Apple","Banana","Apple"));
        System.out.println(cSet);

        List<String> lkList=new LinkedList<>(Arrays.asList("Apple","Banana","Cheery","Apple"));
        System.out.println(lkList);


    }
}
