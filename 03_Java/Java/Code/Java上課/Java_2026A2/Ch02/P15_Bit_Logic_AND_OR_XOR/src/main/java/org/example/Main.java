package org.example;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    static void main() {
        /*
        * 練習位元邏輯運算
        * AND, OR, XOR
        * 注意byte 型別在 有號/無號的轉換
        * 預設是int 型別，在 int -> byte 的時候 MSB=1 會出現違規
        * 此時要進行Casting (型轉)
        * */

        byte a=       0b0101_1011;
        byte b= (byte)0b1011_0110; //Casting

        int res;
        int len;

        res =a&b; //0b0001_0010 -> 0x12 -> 18 dec
        System.out.println(res);

        res =a|b; //0b1111_1111 -> 0xFF -> 255 (-1) 原因待釐清
        System.out.println(res);

        res =a^b; //0b1110_1101 -> 0xED -> 237 (-19) 原因待釐清
        System.out.println(res);


    }
}
