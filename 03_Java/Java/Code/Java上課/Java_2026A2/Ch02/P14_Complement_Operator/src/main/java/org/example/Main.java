package org.example;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    static void main() {
        byte a= 0b0111_1111;
        byte ab= (byte) ~a;
        System.out.println("a = " + a + " " + "ab = " +ab);
        a=0b0000_0001;
        ab= (byte) ~a;
        System.out.println("a = " + a + " " + "ab = " +ab);
        a=0b0000_0000;
        ab= (byte) ~a;
        System.out.println("a = " + a + " " + "ab = " +ab);
        a= (byte)0b1111_1111;
        ab= (byte) ~a;
        System.out.println("a = " + a + " " + "ab = " +ab);
        a= (byte)0b1000_0000;
        ab= (byte) ~a;
        System.out.println("a = " + a + " " + "ab = " +ab);
    }
}
