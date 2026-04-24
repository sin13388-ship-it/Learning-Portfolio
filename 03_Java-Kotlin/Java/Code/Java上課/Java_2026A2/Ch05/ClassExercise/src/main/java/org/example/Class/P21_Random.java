package org.example.Class;

import java.util.ArrayList;
import java.util.Random;

public class P21_Random {
    static void main(String[] args) {
        /*
        * Random 練習
        * 產生 0 < x < 1 之間的變數
        * 使用Math.random 無法固定，每次都不一樣
        * */

        ArrayList<Double> randomElements =new ArrayList<Double>();

        Random random =new Random();
        random.setSeed(456); /*可以設定種子碼，固定生成亂數。無設定種子碼就會是隨機的*/

        for (int i =0; i <5; i++)
        {
            randomElements.add(random.nextDouble());
        }

        for(double e :randomElements) System.out.printf("%.5f \t ",e);
        System.out.println();




    }
}
