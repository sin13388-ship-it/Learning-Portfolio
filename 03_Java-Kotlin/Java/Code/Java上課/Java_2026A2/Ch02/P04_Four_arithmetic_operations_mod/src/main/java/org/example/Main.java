package org.example;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    static void main() {
        /*
        * 四則運算
        * 整數除法
        * 強制型轉
        * */

        int x=25, y=3, z;

        System.out.println("x =" + x);
        System.out.println("y =" + y);

        z=x+y;
        System.out.println("z=x+y =" + z);
        z=x-y;
        System.out.println("z=x-y =" + z);
        z=x*y;
        System.out.println("z=x*y =" + z);
        z=x/y;
        System.out.println("z=x/y =" + z);

        double f =0;
        f =x/y;
        System.out.printf("f (wo/ casting)= x/y => %f%n",f);
        f =x/(double)y;
        System.out.printf("f (w/ casting) = x/y => %7.5f%n",f);

    }
}
