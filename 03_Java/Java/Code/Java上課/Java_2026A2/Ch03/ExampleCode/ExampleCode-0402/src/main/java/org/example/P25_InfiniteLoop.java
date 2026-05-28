package org.example;

import java.util.Scanner;

public class P25_InfiniteLoop {
    static void main(String[] args) {
        /*這是 Java 規範中定義的唯一標準入口點。
        當你在命令行輸入 java YourClassName 時，
        JVM 會尋找具有這個精確簽名（Signature）的方法。
        不能直接啟動：如果你試圖執行一個只有 static void main() 的類別，
        JVM 會報錯，提示找不到 main 方法（或是找不到符合標準簽名的方法）。
        多載 (Overloading)：Java 允許方法多載，所以你可以同時在同一個類別裡寫這兩個方法，
        但執行時永遠是從有 String[] args 的那個開始。*/

        /*
        * 猜數字
        * for(;;) -> 無限迴圈
        *
        * */

        Scanner _scanner =new Scanner(System.in);
        final int passCode=1788;
        boolean isTrue=false;
        int inputCode;
        int retry=0;

        for(;;){
            System.out.println("Please input your passcode");
            inputCode=_scanner.nextInt();
            if(inputCode==passCode)
            {
                System.out.println("Success!");
                break;
            }else System.out.println("Passcode is error...");
        }
    }
}
