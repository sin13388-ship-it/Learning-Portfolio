package org.example;

public class Main {
    static void main() {
        /*
        * Java 會有自動型轉
        * type char 被放入 int 後，會自動型轉成 ASCII
        * 注意 大轉小的問題, char 是 2 bytes, byte 是 1 byte
        * */

        int i;
        byte bt=10;
        char ch ='A'; //0x41 65
        float f;

        i=bt;
        System.out.println("i= "+i + "bt= " +bt);

        i=ch;
        System.out.println("i= "+i + " ch= " +ch);

        f=bt;
        System.out.println("f= "+f + " bt= " +bt);

        ch=0x42;
        //bt =ch; // 違例，大轉小
        i=ch;
        System.out.println("i= "+i + " ch= " +ch);


    }
}
