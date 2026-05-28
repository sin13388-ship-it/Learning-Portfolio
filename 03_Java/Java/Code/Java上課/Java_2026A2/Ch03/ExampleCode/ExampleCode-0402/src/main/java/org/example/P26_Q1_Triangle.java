package org.example;

public class P26_Q1_Triangle {
    static void main(String[] args) {
        /*
        * Triangle
        * 相依性迴圈寫法
        * 印出第一象限的三角形
        * */

        int order=4;
        for(int i=0; i<=4; i++){
            for(int j =0; j<=i; j++){
                //用相依性的方式寫
                System.out.printf("%c",'*');
            }
            System.out.println();
        }
    }
}
