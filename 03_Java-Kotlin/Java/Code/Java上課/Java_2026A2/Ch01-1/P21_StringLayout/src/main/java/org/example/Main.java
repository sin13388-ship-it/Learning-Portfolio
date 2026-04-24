package org.example;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    static void main() {
        /*
        * String 輸出
        * 排版需要，靠左靠右
        * 不同進制下的顯示方式
        * %8d >> 8 : 總位數, d : 進制 or 型態
        * 對字串來說 : +/- 8 位數 , 是靠左靠右對齊總字數是8
        * 對數值來說，正負數會在前面加上正/負號
        * */
        int x=12345;
        double y=123.45;
        String s ="Exact";

        System.out.printf("x (dec) =%8d%n",x); //d: decimal
        System.out.printf("x (dec) =%-8d%n",x);
        System.out.printf("x (dec) =%+8d%n",x);

        System.out.printf("x (Hex) =%8x%n",x); //x: hex
        System.out.printf("x (Hex) =%-8x%n",x);
        //System.out.printf("x (Hex) =%8x%n",x); // 沒有'+'

        System.out.printf("x (Oct) =%8o%n",x); //o: oct
        System.out.printf("x (Oct) =%-8o%n",x);
        //System.out.printf("x (Oct) =%8o%n",x); // 沒有'+'

        System.out.printf("y (float) =%8.2f%n",y); //f: float, double
        System.out.printf("y (float) =%-8.2f%n",y);
        System.out.printf("y (float) =%+8.2f%n",y);

        System.out.printf("z (string) =%8s%n",s); //s: string
        System.out.printf("z (string) =%-8s%n",s);
    }
}
