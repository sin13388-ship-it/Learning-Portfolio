package org.example;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    static void main() {

        /*
        * 短路機制
        * i++ ==8 >>先判斷再運算
        * */

        System.out.println("&&, &");
        boolean b0=false;
        int i = 8;
        System.out.println("b0 = " + b0 + " i = " + i);
        System.out.println("b0 && (i++ ==8) = " + (b0 && (i++ ==8))); // i ==8 i+=1
        System.out.println("ｉ = " + i ); // 8
        System.out.println("b0 & (i++ ==8) = " + (b0 & (i++ ==8)));
        System.out.println("ｉ = " + i ); // 9
        System.out.println("||, |");
        i=8;
        b0=true;
        System.out.println("b0 = " + b0 + " i = " + i);
        System.out.println("b0 || (i++ ==8) = " + (b0 || (i++ ==8)));
        System.out.println("ｉ = " + i ); // 8
        System.out.println("b0 | (i++ ==8) = " + (b0 | (i++ ==8)));
        System.out.println("ｉ = " + i ); // 9
    }
}
