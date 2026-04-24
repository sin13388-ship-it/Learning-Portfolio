package org.example;

import java.util.Scanner;

public class Homework_0402 {
    static void main(String[] args){
        /*
        * Java homework
        *
        * #1 : Using for loop to sum : 1+3+...+49 (for odd)
        * #1 : Using for loop to sum : 2+4+...+50 (for even)
        * #2 : Using while loop to sum : 1+3+...+49 (for odd)
        * #2 : Using while loop to sum : 2+4+...+50 (for even)
        * 01_張紫琳_iCap_HW01
        * Title : iCap_HW01
        * */

        Scanner _scanner =new Scanner(System.in);

        System.out.println("Please input mode : 1: odd; 2: even");
        int mode =_scanner.nextInt();
        int sum=0;
        int i=0;

        if(mode==1)
        {
            //for odd
            for(i =1; i<=49; i+=2)
            {
                sum+=i;
            }
            System.out.println("Sum (For loop) : 1 + 3 + .... +49 =" +sum);
            sum=0;
            i=1;
            while(i <=49)
            {
                sum+=i;
                i+=2;
            }
            System.out.println("Sum (While loop) : 1 + 3 + .... +49 =" +sum);
        }
        else if (mode ==2)
        {
            //for even
            for(i =2; i<=50; i+=2)
            {
                sum+=i;
            }
            System.out.println("Sum (For loop) : 2+ 4 + .... +50 =" +sum);
            sum=0;
            i=2;
            while(i <=50)
            {
                sum+=i;
                i+=2;
            }
            System.out.println("Sum (While loop) : 2 + 4 + .... +50 =" +sum);

        }
        else System.out.println("Invalid mode");

    }
}
