package org.example;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    static void main() {
       /*
       *  '=' assignment
       *
       *
       * */
        int x, y, z ;

        x=y=z=100; //multi initialize

        System.out.println("x= " +x);
        System.out.println("y= " +y);
        System.out.println("z= " +z);

        x=(y) + 100;
        System.out.println("x= " +x);
        x=(y=y+2)+(z=z+100); // 合法 : ( y =100 +2 ) +(z=100+100) = 302
        System.out.println("x= " +x);

    }
}
