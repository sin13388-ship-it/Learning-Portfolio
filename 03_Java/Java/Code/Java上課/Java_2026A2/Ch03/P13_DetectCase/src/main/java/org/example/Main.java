package org.example;

import java.util.Scanner;
//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    static void main() {

        /*
        * 讓使用者輸入字元, 並判斷大小寫
        * Java 取字元的方式
        * _scanner.nextLine().charAt(0);
        * */

        char ch;
        Scanner _scanner =new Scanner(System.in);
        System.out.println("Please input a character :");
        ch =_scanner.nextLine().charAt(0);
        if(ch >='A' && ch <='Z') System.out.println("=Upper case");
        else if(ch >='a' && ch <='z') System.out.println("=Lower case");
        else if(ch >='0' && ch <='9') System.out.println("=Digit");
        else  System.out.println("Especial character");







    }
}
