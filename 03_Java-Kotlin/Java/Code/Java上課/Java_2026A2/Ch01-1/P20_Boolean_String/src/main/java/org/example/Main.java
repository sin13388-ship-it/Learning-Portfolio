package org.example;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    static void main() {
        /*
        * Substring (bIndex, eIndex) >> eIndex 不包含
        *
        * */

        boolean b1=true;
        System.out.println("b1: "+b1);
        b1=false;
        System.out.println("b1: "+b1);
        String Str ="歡迎光臨楊梅職訓中心, Java程式語言設計";
        System.out.println(Str);
        System.out.println(Str.substring(0,4) + "!!!");


    }
}
