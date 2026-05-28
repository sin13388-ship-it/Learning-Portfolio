package org.example.Class;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;

public class P22_LotteryGenerator {

    static void main(String[] args) {
        /*
        * HashSet :　不重複的集合
        * 如果 add 相同的數值，會放不進去
        * 集合是無序的
        * 使用 List<Integer> 取代 int[]
        * 使用Tree set 會排序
        * */

        ArrayList<List<Integer>> lotteryNumbers = new ArrayList<>();

        for(int i=0; i<4; i++)
        {
             HashSet<Integer> lotteryElements =new HashSet<Integer>();
            //TreeSet<Integer> lotteryElements =new TreeSet<Integer>();
            while(lotteryElements.size()<6)
            {
                lotteryElements.add((int)(Math.random()*49+1));
            }
            lotteryNumbers.add(new ArrayList<Integer>(lotteryElements));
        }

        /*Output*/
        for(var e:lotteryNumbers)
        {
            for (var x:e)
            {
                System.out.printf("%d \t", x);
            }
            System.out.println();
        }
    }
}
