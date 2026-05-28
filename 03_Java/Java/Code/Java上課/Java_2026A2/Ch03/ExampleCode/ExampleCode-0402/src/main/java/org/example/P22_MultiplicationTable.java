package org.example;

public class P22_MultiplicationTable {

    static void main() {
        /*
        * 99乘法表
        * 每列只有3組
        * */
        int i, j, k;
        boolean isSplit;
        int offset =1;
        k=0;

        for (i=1; i<=9;i+=3){
            for(j=1; j<=9; j++){
                for(k=i; k<i+3; k++){
                    System.out.printf("%d x %d = %2d \t", k ,j, k*j);
                }
                System.out.printf("\n");
            }
            System.out.printf("==========================\n");
        }
    }
}
