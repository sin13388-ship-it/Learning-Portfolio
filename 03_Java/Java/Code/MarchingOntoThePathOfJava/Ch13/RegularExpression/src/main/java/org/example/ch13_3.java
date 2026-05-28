package org.example;

import java.util.Scanner;

public class ch13_3 {
    /*讓使用者輸入一個字串
    * 使用正規表達式驗證是否為數字
    * 正規表達式中數字是\d
    * 要打出反斜線要用脫逸字元*/
    static void main() {
        Scanner scanner =new Scanner(System.in);
        String pattern ="\\d";
        String inputString ;
        System.out.println("請輸入字串 :");
        inputString=scanner.next();
        if(inputString.matches(pattern))
            System.out.println(inputString + ": 是 0-9 的數字");
        else
            System.out.println(inputString + ": 不是 0-9 的數字");

    }
}
