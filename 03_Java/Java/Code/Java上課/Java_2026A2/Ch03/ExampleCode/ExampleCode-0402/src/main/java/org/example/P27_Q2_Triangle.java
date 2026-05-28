package org.example;

public class P27_Q2_Triangle {
    static void main(String[] args) {
        /*
        * Q2 Triangle
        * 每列的總長度不變
        * 只是部分用' '取代
        * */

        int order =4;
        int length=4;
        for (int i=0; i<=order; i++){
            for(int j=0; j<=order; j++){
                if(j < length-i) System.out.printf("%c",' ');
                else System.out.printf("%c",'*');
            }
            System.out.println();
        }
    }
}
