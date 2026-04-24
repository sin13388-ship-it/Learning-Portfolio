package org.example;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

import java.util.Scanner;

public class Main {
    static void main() {
        /*
        * 讓使用者輸入成績
        * 根據使用者的分數輸出對應的grade 等級
        * A, B, C ,D, F = 90 ,80 ,70, 60, Fail
        * 判斷區間的切割必須乾淨且不overlap
        * */

        double score;
        char grade;

        System.out.println("Please input your score :");
        Scanner _scanner =new Scanner(System.in);
        score =_scanner.nextDouble();
        if(score >=90) grade ='A';
        else if(score >=80) grade='B';
        else if(score >=70) grade='C';
        else if(score >=60) grade='D';
        else grade='F';

        System.out.println("Score : " + score + ", Grade : " + grade);



    }
}
