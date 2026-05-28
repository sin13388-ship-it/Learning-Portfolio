package org.example.String;

public class P20_StringConstructure {
    static void main(String[] args) {
        /*
        * String constructure
        *
        *
        * */

        String msg ="Welcome to Java"; /*const*/
        String msg1 =new String("Another string");
        char[] msg2 ={'G','o','o','d',' ', 'd','a','y'};
        String msg3 =new String(msg2);
        System.out.println(msg);
        System.out.println(msg1);
        System.out.println(msg3);
        /*
            Welcome to Java
            Another string
            Good day
        * */
    }
}
