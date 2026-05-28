package org.example;

public class ch13_10 {

    static void main(String[] args) {
        /*使用pipe一次搜尋多個條件*/

        String str1="02-23339999";
        String str2="(02)-23339999";
        String str3="(111)-11111111";
        String patternForPhoneNumber="\\d{2}-\\d{8}|\\(\\d{2}\\)-\\d{8}";

        System.out.println("Does the str1 match the format? " + str1.matches(patternForPhoneNumber));
        System.out.println("Does the str2 match the format? " + str2.matches(patternForPhoneNumber));
        System.out.println("Does the str3 match the format? " + str3.matches(patternForPhoneNumber));

    }


}
