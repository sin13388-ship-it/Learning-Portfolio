package org.example;

public class P28_Q3_Triangle {
    static void main(String[] args) {
        /*
         * Triangle
         * 相依性迴圈寫法
         * 印出三第象限的三角形
         * */
        int order=4;
        int i=0;
        for(i=0; i<=order; i++){
            for(int j =0; j<=order; j++){
                if (j<i) System.out.printf("%c",' ');
                else System.out.printf("%c",'*');
            }
            System.out.println();
        }
    }
}
