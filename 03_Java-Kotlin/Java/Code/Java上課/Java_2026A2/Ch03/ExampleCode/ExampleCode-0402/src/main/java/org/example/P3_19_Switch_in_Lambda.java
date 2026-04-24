package org.example;

import java.util.Scanner;

public class P3_19_Switch_in_Lambda {
    static void main() {
        /*
        * 使用lamda表示式
        *
        * */
        System.out.println("Please input your score grade, A,B,C,D,F :");
        char score =new Scanner(System.in).next().charAt(0);
        switch (score){
            case 'A' -> IO.println("Your Score is between 90~100");
            case 'B' -> IO.println("Your Score is between 80~89");
            case 'C' -> IO.println("Your Score is between 70~79");
            case 'D' -> IO.println("Your Score is between 60~69");
            case 'F' -> IO.println("Please major it again");
            default  -> IO.println("Invalid input");
        }
    }
}
