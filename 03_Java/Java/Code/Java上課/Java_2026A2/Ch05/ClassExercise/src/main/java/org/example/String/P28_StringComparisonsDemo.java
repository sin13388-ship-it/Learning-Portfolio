package org.example.String;

public class P28_StringComparisonsDemo {
    static void main(String[] args) {
        /*
        * String.compareTo
        * String.startWith; endWith
        * String.regionMatches
        *
        * */

        String S1="Welcome to Java";
        String S2="Welcome to C++";
        /*
        * 如果兩個字串的內容不同，則回傳不同字元的差值(this-target)
        * 如果兩個字串的長度不同，而且this比較短，則回傳長度的差值(this-target)
        * 0 : 完全相同
        * 其他看語法
        * */
        System.out.println(S1.compareTo(S2));
        /*
        * 句首 句尾
        * */
        System.out.println(S1.startsWith("Welcome"));
        System.out.println(S1.endsWith("C++"));
        /*
        * 區域比對
        * */
        System.out.println(S1.regionMatches(0,S2,0,S1.length())); /*全段, false*/
        System.out.println(S1.regionMatches(0,S2,0,10)); /*指定位置, true*/
    }
}
