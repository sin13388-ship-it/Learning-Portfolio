package org.example.MethodBasics;

public class P05_Observe_Stack {
    static void main(String[] args) {
        /*To observe stack changing*/

        int i=5;
        int j=2;
        int k =max(i,j);
        System.out.println("i= " +i + "j= " + j + "k= " + k);

    }
    static int max(int num1, int num2){
        int result;
        if (num1 > num2) result=num1;
        else result =num2;
        return result;
    }
}
