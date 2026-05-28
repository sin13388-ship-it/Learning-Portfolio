package org.example;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    static void main() {
        /*
        * Math -> pow(x,y) x^y
        * ++i , --i, i++, i--
        * i +=1; i -=1;
        * */
        int x=2;
        int pow=3;
        double res;

        res =Math.pow(x,pow);
        System.out.println("a ^ b = " + res);

        double a=2.2;
        double b=3.3;

        res =Math.pow(a,b);
        System.out.printf("a ^ b = %.3f%n", res);

        int i=10;
        ++i;
        System.out.println("i= " + i);//11
        i--;
        System.out.println("i= " + i); //10

        i =20;
        System.out.println("i (i--) = " + i--);  // 20
        System.out.println("i (i) = " + i ); //19
        System.out.println("i (--i) = " + --i);  // 18

    }
}
