package org.example;

import java.util.Scanner;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    static void main() {
        /*
        * 三元運算子
        * 請使用者輸入兩數，再輸出較大、較小的數值
        */
        Scanner _scanner =new Scanner(System .in);
        int a, b;
        System.out.println("Please Input int a : ");
        a= _scanner.nextInt() ;
        System.out.println("Please Input int b : ");
        b= _scanner.nextInt();
        int larger, smaller;
        larger= (a >b)?a : b;
        smaller=(a < b)?a : b;
        System.out.println("The larger is : " + larger);
        System.out.println("The smaller is : " + smaller);
    }
}
