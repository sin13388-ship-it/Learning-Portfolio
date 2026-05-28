package org.example.MethodBasics;

public class P10_Swap_Value_Reference {
    static void main(String[] args) {
        /*Swap
        * 陣列、物件、類別是傳參考
        * 傳參考會被改變
        * 基本型態是傳值
        * */

        int data0=10, data1=20;
        int[] data = new int[]{10,20};

        swapByValue(data0, data1);
        System.out.printf("The data 0 : %d, data 1 : %d %n", data0 ,data1);
        swapByRef(data);
        System.out.printf("The data 0 : %d, data 1 : %d %n", data[0] ,data[1]);

    }
    static void swapByValue(int data0, int data1)
    {
        int temp =0;
        temp=data0;
        data0=data1;
        data1=temp;
    }
    static void swapByRef(int[] data)
    {
        int temp=0;
        temp=data[0];
        data[0]=data[1];
        data[1]=temp;
    }
}
