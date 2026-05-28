package com.questions;

public class A4_Prob13 {

    /*當static 發生名稱重疊的時候，參數優先*/
    static int extra =300;

    public static int changePoint(int point, Boolean bonus, int extra){
        if(bonus==true){
            point+=extra;
        }
        return point;
    }
    static void main(String[] args) {
        Boolean bonus =true;
        int point=10;
        int extra =100;
        int newPoint=changePoint(point, bonus,extra);
        System.out.println(point);
        System.out.println(newPoint);
        System.out.println(A4_Prob13.extra); /*static extra*/

        for(int i=5; i>=0; --i){
            System.out.println(i);
        }
    }
}
