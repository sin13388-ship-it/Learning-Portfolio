package org.example;

public class ch13_7 {
    /*
    * 使用大括號處理重複出現的字串
    * 例如 "\\d\\d\\d" >> \\d{3}
    * 驗證台北市話
    * 規定寫法為 02-12345678
    * () 用括號分組，例如手機號碼 09xx-xxx-xxx
    * 可以寫成 : \\d{4}(-\\d{3}){2}; (-\\d{3}){2} 表示要重複兩次
    * */

    static void main() {
        /*驗證市話與手機*/

        String cellPhonePattern="\\d{4}(-\\d{3}){2}";
        String taipeiPhonePattern ="\\d{2}-\\d{8}";

        String test1="I love Java!";
        String test2="0952-909-090";
        String test3="(111)-11111111";
        String test4="02-12345678";

        System.out.printf("The string \" %s \" is cell phone number? %b | Taipei phone number ? %b \n", test1
        ,test1.matches(cellPhonePattern),test1.matches(taipeiPhonePattern));

        System.out.printf("The string \" %s \" is cell phone number? %b |  Taipei phone number ? %b \n", test2
                ,test2.matches(cellPhonePattern),test2.matches(taipeiPhonePattern));

        System.out.printf("The string \" %s \" is cell phone number? %b | Taipei phone number ? %b \n", test3
                ,test3.matches(cellPhonePattern),test3.matches(taipeiPhonePattern));

        System.out.printf("The string \" %s \" is cell phone number? %b | Taipei phone number ? %b \n", test4
                ,test4.matches(cellPhonePattern),test4.matches(taipeiPhonePattern));

    }

}
