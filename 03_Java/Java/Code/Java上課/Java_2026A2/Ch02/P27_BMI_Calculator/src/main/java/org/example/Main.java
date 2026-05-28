package org.example;


    import java.util.Scanner;

public class Main {
    static void main() {
        /*
        * BMI 計算器
        * 輸入 體重; 身高
        * BMI = Weight / Heigh ^2 (M)
        * */

        Scanner _scanner =new Scanner(System.in);

        System.out.println("Please input weight (kg) : ");
        double weight=_scanner.nextDouble();

        System.out.println("Please input heigh (cm) : ");
        double heigh=_scanner.nextDouble();

        heigh /=100;

        double bmi=0.0;

        bmi = weight / (heigh * heigh);
        System.out.printf("BMI : %.2f%n", bmi);

    }
}
