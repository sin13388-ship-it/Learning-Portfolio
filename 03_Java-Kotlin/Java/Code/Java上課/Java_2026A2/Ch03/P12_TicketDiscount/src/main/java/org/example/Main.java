package org.example;



import java.util.Scanner;

public class Main {
    static void main() {
        /*
        * 根據使用者的年紀計算折扣後的票價
        * 大於 80歲 及 6 歲以下 2折
        * 60~79 歲 及 7~12歲 5 折
        * */


        double price;
        int age;
        int ticket =100;
        Scanner _scanner =new Scanner(System.in);
        System.out.println("Please input your age :");
        age =_scanner.nextInt() ;

        if (age >=80 || age <=6) price =ticket * 0.2;
        else if (age >=60 || age <=12) price =ticket * 0.5;
        else price =ticket;

        System.out.println("Price :" + price);

    }
}
