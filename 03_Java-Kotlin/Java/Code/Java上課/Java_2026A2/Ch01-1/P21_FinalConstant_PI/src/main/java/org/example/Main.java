package org.example;

import javax.swing.*;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    static void main() {
        /*
        * final 修飾字 >> 變數不能變動
        * Parse 用法
        * */

        final double PI =3.14;
        double radius ;
        String strRadius;
        strRadius= JOptionPane.showInputDialog(null, "請輸入半徑 : ");
        double Radius;
        Radius=Double.parseDouble(strRadius);
        double area;
        area =Radius*Radius*PI;
        JOptionPane.showMessageDialog(null, "Area is " + area);
    }
}
