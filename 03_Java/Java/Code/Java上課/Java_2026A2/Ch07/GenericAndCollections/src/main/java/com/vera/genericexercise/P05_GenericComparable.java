package com.vera.genericexercise;

public class P05_GenericComparable {

    static void main(String[] args) {

        /*泛型也可以支援comparable*/

        Integer[] iArray={1,2,3,4,5};
        String[] sArray={"Andy", "Bob","Eric","David", "Lily"};
        Character[] cArray={'Y','B','a','i','D'};

        System.out.println("The max in iArray(Integer) : " + findMax(iArray));
        System.out.println("The max in sArray(String) : " + findMax(sArray));
        System.out.println("The max in cArray(Character) : " + findMax(cArray));
    }


    static <T extends  Comparable<T> > T findMax(T[] array){
        /*傳入的類別(介面)要實作Comparable 介面
        * 回傳泛型
        * */
        T max =null;
        max=array[0];
        for(var e : array) {
            if(e.compareTo(max)>0) max=e;
        }
        return max;
    }
}
