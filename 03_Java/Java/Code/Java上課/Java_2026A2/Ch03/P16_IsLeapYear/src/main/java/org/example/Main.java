package org.example;

import java.util.Scanner;
//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    static void main() {
        /*
        * 讓使用者輸入西元年分
        * 輸出該年是否為閏年 (能被 4和 400 整除; 但若年份能被 100 整除，則為平年)
        * 地球繞太陽一圈的精確時間約為 365 天 5 小時 48 分 46 秒。
        * 如果每 4 年潤一次，平均一年是 365.25 天，這比實際多出了約 11 分鐘。
        * 這微小的誤差累積 128 年後會導致曆法多出一天。
        * 因此，規定「逢百不閏，逢四百再閏」是為了將平均一年的長度調整為 365.2425 天，
        * 這與實際的天文觀測值非常接近，每 3300 年才會產生約一天的誤差。
        * 使用巢狀式的方法寫
        *
        * */

        Scanner _scanner =new Scanner(System.in);
        int year;
        boolean isLeapYear;
        System.out.println("Please input year :");
        year =_scanner.nextInt();

        if(year %4 ==0){
            if(year %100 !=0 || year %400==0) isLeapYear=true;
            else isLeapYear=false;
        }else isLeapYear=false;

        if(isLeapYear) System.out.println("The " + year + " is leap year");
        else System.out.println("The " + year + " is normal year");

    }
}
