package org.example;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    static void main() {
        /*
        * 邏輯運算part2
        * 有號的運算
        * Bitwise AND, OR, NOT, XOR
        * */

        byte bt= (byte) 0b1010_0010;
        byte bt2=(byte) 0b1111_0010;

        int res; //如何處理溢位的問題?

        res =bt & bt2; //1010 0010 A2 162 (-94)
        System.out.println(res);

        res =bt | bt2; //1111 0010 F2 242 (-14)
        System.out.println(res);

        res =~bt; //0101_1101 5D 93
        System.out.println(res);

        res =bt ^ bt2; //0101_0000 50 80
        System.out.println(res);
    }
}
