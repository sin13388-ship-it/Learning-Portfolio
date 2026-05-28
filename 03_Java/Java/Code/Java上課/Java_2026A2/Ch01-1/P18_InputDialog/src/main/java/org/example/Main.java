package org.example;

import javax.swing.*;

public class Main {
    /*
    * Input Dialog
    * */
    static void main() {
        String inpStr;
        inpStr=JOptionPane.showInputDialog(null , "Please Input Your Name: ");
        JOptionPane.showMessageDialog(null, "Hello, " + inpStr + ", "+ "Nice to meet you !!");
    }
}
