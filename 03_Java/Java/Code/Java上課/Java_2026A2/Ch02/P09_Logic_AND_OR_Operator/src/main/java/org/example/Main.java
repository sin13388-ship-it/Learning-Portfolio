package org.example;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    static void main() {
        /*
        * &, && 有相同的邏輯
        * & >> 左右兩邊會乖乖做完
        * && >> 有短路機制，只要左邊false則跳出
        * 同理 |, ||
        */
        boolean b0, b1;
        b0= false;
        b1=true;

        System.out.println("b0 = "+ b0 + " b1 " +  b1); // false true
        System.out.println("b0 & b1 =" + (b0 & b1)); //false
        System.out.println("b0 && b1 =" + (b0 && b1)); // false, 短路

        System.out.println("b0 | b1 =" + (b0 | b1)); //true
        System.out.println("b0 || b1 =" + (b0 || b1)); //true

        System.out.println("b0 ^ b1 =" + (b0 ^ b1)); //true

    }
}
