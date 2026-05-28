package org.example;

import javax.swing.*;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    static void main() {
        /*
        * Unicode
        * \\u 後方必須接 4 位十六進位數字
        * */

        String inpStr=null;
        inpStr= JOptionPane.showInputDialog(null, "請輸入字元 : ");
        char ch = inpStr.toCharArray()[0];
        JOptionPane.showMessageDialog(null, ch);
        int unicode =(int)ch;
        String unicode_Hex=Integer.toHexString(unicode).toUpperCase(); // 轉16進制，大寫
        JOptionPane.showMessageDialog(null, "相對應的Unicode : " + "\\u" + unicode_Hex);
    }
}
