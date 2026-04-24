package org.example;

import java.util.Scanner;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    static void main() {
        /*
        * 使用Switch case
        * 讓使用者輸入年分，並顯示該年級
        * switch (case){ case a: break;}
        * */
        Scanner _scanner =new Scanner(System.in);
        int year;
        System.out.println("Please input your academic year");
        year=_scanner.nextInt();
        switch (year){
            case 1 :
                System.out.println("Freshman");
                break;
            case 2 :
                System.out.println("Sophomore");
                break;
            case 3 :
                System.out.println("Junior");
                break;
            case 4 :
                System.out.println("Senior");
                break;
            default:
                System.out.println("Invalid year");
                break;
        }
   }
}
