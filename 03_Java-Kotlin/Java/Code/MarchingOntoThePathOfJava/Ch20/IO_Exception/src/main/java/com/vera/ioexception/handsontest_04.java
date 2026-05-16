package com.vera.ioexception;

import java.util.*;

public class handsontest_04 {
    static void main(String[] args) {

        Scanner scanner=new Scanner(System.in);

        int x=0, y=0;

        String cmd="";
        while (! cmd.equals("n") )
        {
            try
            {
                System.out.println("請輸入兩個整數，間隔用空白隔開");
                x=scanner.nextInt();
                y=scanner.nextInt();
                System.out.println("數字除法結果是"+ x/y);
            }
            catch (InputMismatchException e){
                System.out.println("輸入資料類型錯誤"+e);
            }
            catch (ArithmeticException e){
                System.out.println("除數為0的異常"+e);
            }
            finally {
                scanner.nextLine(); //buffer clear
                System.out.println("是否繼續? (y/n)");
                cmd=scanner.next();
            }
        }
        scanner.close();
    }
}
