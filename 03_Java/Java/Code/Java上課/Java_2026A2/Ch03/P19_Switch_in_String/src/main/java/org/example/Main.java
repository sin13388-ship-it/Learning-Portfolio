package org.example;

import java.util.Scanner;
//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    static void main() {
        /*
        * Scanner 的一行寫法
        * 若用字串做判斷要留意大小寫的問題
        * 簡易行事曆
        * */
        System.out.println("Please input weekday, Sun, Mon, Tue, Wed, Thu, Fri, Sat");
        String weekday =new Scanner(System.in).next();
        weekday=weekday.toUpperCase();

        switch (weekday){
            case "SUN" :
                System.out.println("Take A Rest");
                break;
            case "MON" :
                System.out.println("Reverse Room For Friday Meeting");
                break;
            case "TUE" :
                System.out.println("Prepare Powerpoint slides");
                break;
            case "WED" :
                System.out.println("Send out meeting reminders");
                break;
            case "THU" :
                System.out.println("Order snacks for delivery");
                break;
            case "FRI" :
                System.out.println("Meeting at 9 AM");
                break;
            case "SAT" :
                System.out.println("Take another rest");
                break;
            default :
                System.out.println("Take A Rest");
                break;

        }

    }
}
