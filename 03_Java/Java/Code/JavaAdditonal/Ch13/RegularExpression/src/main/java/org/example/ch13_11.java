package org.example;

public class ch13_11 {
    static void main(String[] args) {
        String str1="John";
        String str2="Johnson";
        String str3="Johnnason";
        String patternForPhoneNumber="John((na)?son)"; /*有沒有na 不重要*/

        System.out.println("Does the str1 match the format? " + str1.matches(patternForPhoneNumber));
        System.out.println("Does the str2 match the format? " + str2.matches(patternForPhoneNumber)); //0次
        System.out.println("Does the str3 match the format? " + str3.matches(patternForPhoneNumber));
    }

}
