package org.example;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

import java.util.Scanner;

public class Main {
    static void main() {
        /*
        * 讓使用者輸入業績
        * 並計算可以收到多少的回扣
        * 對於不會變動的變數，用final 的關鍵字
        * */
        final double LOW_LIMIT =500.0;
        final double MED_LIMIT =1000.0;
        final double LOW_RATE =0.05;
        final double MED_RATE =0.06;
        final double HIGH_RATE =0.08;

        double salesAmount;
        double CommissionRate;

        Scanner _scanner = new Scanner(System.in);
        System.out.println("Please input your sales amount : ");
        salesAmount=_scanner.nextDouble();

        if (salesAmount <= LOW_LIMIT){
            CommissionRate =LOW_RATE;

        }else if (salesAmount <= MED_RATE) {
            CommissionRate =MED_RATE;
        }else{
            CommissionRate =HIGH_RATE;
        }

        System.out.println("SalseAmount: " + salesAmount + "CommissionRate : " + CommissionRate);

    }
}
