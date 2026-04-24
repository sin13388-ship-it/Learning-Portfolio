package org.example;

import java.util.Scanner;


public class P20_Switch_In_Char {
    static void main() {
        System.out.println("Please input your score grade, A,B,C,D,F :");
        char score =new Scanner(System.in).next().charAt(0);
        switch (score){
            case 'A' :
                IO.println("Your Score is between 90~100");
                break;
            case 'B' :
                IO.println("Your Score is between 80~89");
                break;
            case 'C' :
                IO.println("Your Score is between 70~79");
                break;
            case 'D' :
                IO.println("Your Score is between 60~69");
                break;
            case 'F' :
                IO.println("Please major it again");
                break;
            default:
                IO.println("Invalid input");
                break;
        }
    }
}
