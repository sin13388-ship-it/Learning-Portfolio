package org.example.classpractice;

public class P11_OverLoad_Method {

    static float add (int a , float b){
        return a+b; /*結果一樣但屬於不同簽章*/
    }
    static float add (float a, int b){
        return a+b; /*結果一樣但屬於不同簽章*/
    }

    static void main(String[] args) {
        /*
        * Static method
        * Overlaod 練習
        *
        *
        * */

        System.out.println(add(12,32.56f));
        System.out.println(add(12.34f,78));

    }

}
