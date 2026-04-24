package org.example.classpractice;
import java.util.Scanner;
public class iCapHW02 {
    static void main(String[] args) {
        Scanner _scanner =new Scanner(System.in);
        System.out.println("Please base and heigh : ");
        double base;
        double heigh;
        base=_scanner.nextDouble();
        heigh=_scanner.nextDouble();
        System.out.printf("The base is %f, heigh is %f \n  Area= %f \n", base, heigh, getArea(base, heigh));
    }
    static double getArea(double base, double height){
        return  base * height/2;
    }
}


