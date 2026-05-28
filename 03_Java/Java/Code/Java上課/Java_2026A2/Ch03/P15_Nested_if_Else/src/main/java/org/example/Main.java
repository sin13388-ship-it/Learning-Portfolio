package org.example;

import java.util.Scanner;

public class Main {
    static void main() {
        /*
        * Nested if else
        * 讓使用者輸入賣上，
        * 根據賣上的金額輸出對應的bonus
        * 只有販賣數量大於3 ，才能領取較多的bonus
        * 對於規格類(邊界)，使用final 代表為常數
        * final 只能設一次初始值
        * */

        final int MIN_ITEM =3;
        final int MIN_VALUE =1000;
        final int SMALL_BONUS =10;
        final int MEDIUM_BONUS =25;
        final int LARGE_BONUS =50;
        int bonus=0;

        int itemSold, totalValue;

        Scanner _scanner =new Scanner(System.in);
        System.out.println("請輸入賣出多少項目，及賣出多少金額");
        itemSold =_scanner.nextInt();
        totalValue=_scanner.nextInt();

        if(itemSold >= MIN_ITEM){
            if (totalValue >= MIN_VALUE) bonus=LARGE_BONUS;
            else  bonus= MEDIUM_BONUS;
        }else
        {
            bonus= SMALL_BONUS;
        }

        System.out.printf("共賣出 %d items, 總金額為 %d %n",itemSold,totalValue);
        System.out.printf("Bonus為 %d %n",bonus);

    }
}
