package com.vera.genericexercise;

public class P04_GenericMethod {
    /*
    * Generic method
    * 泛型可以增加一些限制，例如必須是Numbers 的類別
    * <T extends Numbers>, 只能輸入數字型態的類別
    *
    *
    * */

    static void main(String[] args) {
        Double[] doubles={1.1,2.2,3.3,4.4,5.5,6.6};
        Float[] floats={5.1f,6.2f,7.3f,8.4f,9.5f,10.6f};
        Integer[] integers={1,2,3,4,5,6};
        System.out.println("======Generic======");
        System.out.println("Integer : " + sumUPArray(integers));
        System.out.println("Double : " + sumUPArray(doubles));
        System.out.println("Float : " + sumUPArray(floats));

    }
    static <T extends Number> double sumUPArray(T[] genericeArray){
        /*輸入泛型回傳double*/
        double sum=0;
        for(var e : genericeArray)
        {
            sum += e.doubleValue();
        }
        return sum;
    }
}
