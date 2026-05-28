package org.example;

import java.util.Scanner; //import scanner

public class Main {
    static void main() {
        /*
        * 讓使用者輸入溫度轉換的模式
        * 並轉換
        * C =(F-32)*5/9
        * F = C*9/5 +32
        * */

        Scanner _scanner =new Scanner(System.in);
        System.out.println("Please input your selection :");
        System.out.println("1 : F2C; 2: C2F");

        int selection =_scanner.nextInt();

        double F,C;

        if ((selection > 2) || (selection <= 0)) {
            System.out.println("Type Error!!");
            return;
        }

        if (selection==1){

            System.out.println("Please input your degree (F) :");
            F=_scanner.nextDouble();
            C= (F-32 ) * 5 / 9.0;
            System.out.println("Corresponding oC " + C);

        }else {
            System.out.println("Please input your degree (C) :");
            C=_scanner.nextDouble();
            F=C * 9 /5.0 +32;
            System.out.println("Corresponding oF " + F);

        }
        System.out.println("bye !");
    }
}
