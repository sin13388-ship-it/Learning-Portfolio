package org.example;

public class Main {
    static void main() {
        /*
        * 位元移位運算
        * MSB =1 ; 為負號
        * Not 後 +1, 取負號
        * Auto Casting 的問題需要留意
        *  <<, >> 不像遞增/減運算子，會改變原變數的值
        * <<<, >>> 移位後埔0
        * */
        byte a, b;
        int c;

        a=0b100_0101; // 0x45 69(dec)
        b= (byte)0b1000_1010; // 0x8A 138(-118)
        c=0b11111111_11111111_11111111_10001010; //FF_FF_FF_8A -> -0x76 -> -118(dec)

        System.out.println(a); //Auto casting to string
        System.out.println("a << 1 = " + (a <<1)); //138
        System.out.println("(Auto cast to integer) a << 2 = " + (a <<2)); //276 (overflow), 但會被autocasting
        System.out.println("(Force cast to byte) a << 2 = " + (byte)(a <<2)); // (overflow), MOD 256

        System.out.println(a);
        System.out.println("a >> 1 = " + (a >>1)); //69 /2 =34
        System.out.println("a >> 2 = " + (a >>2)); // 17

        System.out.println(a);
        System.out.println("a >>> 1 = " + (a >>>1)); //0b0010_0010
        System.out.println("a >>> 2 = " + (a >>>2)); //0b0001_0001

        System.out.println("b >>> 2 = " + (b >>>1)); //0b0100_0101

        System.out.println(a);
        System.out.println(b);
        System.out.println(c);

    }
}
