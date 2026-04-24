package org.example;

public class Main {
    static void main() {

        /*
        * 自動轉換練習
        * 如果expression 裡有不同type 的 運算.
        * 會以大的為主
        * 例題 整數型態的看不出變化
        * */

        int i;
        double db;
        float f;
        long ll;
        short st=-10;
        byte bt=-5;

        db =(i=-101) + 3.3; // 轉型成 double
        System.out.println("i= "+ i + " db= " + db);

        f =i +5.5f; // 轉型成 float , float size > int
        System.out.println("i= "+ i + " f= " + f);

        ll =i +100L; // 轉型成 long , long  size > int

        System.out.printf("i= %d ll= %d i= %X %n", i, ll, i);

        i =st +bt; // 不轉型, int size > short, byte
        System.out.println("i= "+ i + " st= " + st + " bt= " +bt);
        System.out.printf("i= %X %n", i);

    }
}
