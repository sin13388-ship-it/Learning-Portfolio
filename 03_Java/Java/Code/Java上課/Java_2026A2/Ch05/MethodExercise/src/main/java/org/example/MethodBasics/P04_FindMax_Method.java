package org.example.MethodBasics;

import java.util.Scanner;

public class P04_FindMax_Method {
    static void main(String[] args) {
        /*
        * 方法宣告
        * 讓User 輸入 2個數字並比大小
        * */
        Scanner scanner =new Scanner(System.in);
        System.out.println("Please input 1st number :");
        int x = scanner.nextInt();
        System.out.println("Please input 2nd number :");
        int y = scanner.nextInt();
        System.out.println("The Max value is " + findMax(x,y)); /*Arguments*/
    }
    static int findMax(int x, int y){ /*Parameters*/
        if (x > y) return x;
        else return y;
    }
}
