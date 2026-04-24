package org.example;


 import java.util.Scanner;
//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    static void main() {
        /*
        * 讓使用者輸入年齡，並判斷是否符合投票年齡
        * 語法與C code 相同
        * */
        int age;
        Scanner _scanner =new Scanner(System.in);
        System.out.println("Please input your age :");

        age =_scanner.nextInt();

        if (age >=18){

            System.out.println("可以領取選票");

        } else {
            System.out.println("無法投票");
        }

        System.out.println("Thank you");

    }
}
