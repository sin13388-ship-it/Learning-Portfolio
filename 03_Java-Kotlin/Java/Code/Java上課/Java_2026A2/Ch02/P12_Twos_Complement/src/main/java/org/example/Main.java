package org.example;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    static void main() {
        /*
        * 2's 補數
        *
        * */
        byte b;
        b=0b0111_1111;
        System.out.println("b= " +b);
        b=0b0000_0001;
        System.out.println("b= " +b);
        b=0b0000_0000;
        System.out.println("b= " +b);
        b=(byte)0b1111_1111;
        System.out.println("b= " +b);
        b=(byte)0b1111_1110;
        System.out.println("b= " +b);
        b=(byte)0b1000_0000;
        System.out.println("b= " +b);
    }
}
