package org.example;

public class P29_Q4_Triangle {
    static void main(String[] args) {
        /*
        * Q4 Triangle
        *
        *
        * */
        int order=4;
        int i=0;
        for(i=0; i<=order; i++){
            for(int j =0; j<=order; j++){
                if (j<=(order-i)) System.out.printf("%c",'*');
                else System.out.printf("%c",' ');
            }
            System.out.println();
        }
    }
}
