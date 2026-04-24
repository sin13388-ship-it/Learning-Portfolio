package org.example;

public class P21_Item_For_Loop_Practice {
    static void main(String[] args) {
        /*
         *
         * Sum= n(n+1)^2
         */
        int sum =0;
        for (int i=1; i<=10; i++){
            sum+=i * (i+1)* (i+1);
        }
        System.out.println("Sum = "+sum);
    }
}
