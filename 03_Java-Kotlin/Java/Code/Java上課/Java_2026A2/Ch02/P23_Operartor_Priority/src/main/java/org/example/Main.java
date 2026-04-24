package org.example;

public class Main {
    static void main() {
        /*
        * 位元移位子的優先順序
        * 遞增運算子的優先順序
        * 遞增運算子會改變數值
        * 四則運算與移位的優先權練習，是遞迴運算，不是一次完成
        * */

        int a;
        a=9*4<<3+2; //  --> (9*4) << (3+2) --> 36 << 5 --> 36 * 32 =1152
        System.out.println(a);

        int b=5, c=5;
        a=++b+c++*3; //6 + 5*3 ; c++
        System.out.println(a);

        a=b++ + ++c*3; //6 + 7*3 ; c++
        System.out.println(a);

        a=5*4+8%3<<3; //20 + 2 << 3 -> 22 << 3 -> 22 *8 = 176
        System.out.println(a);

    }
}
