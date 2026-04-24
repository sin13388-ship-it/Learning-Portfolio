package org.example.MethodBasics;

public class P09_CallByValue {
    /*
    * Call by value
    * 方法帶有parameters
    * 用call by value 的方式進行
    * */
    static void main(String[] args) {

        int a =10;
        int b =20;

        multiply_10(a);
        b=multiplyTenAndReturnResult(b);
        System.out.println(b);

    }
    static void multiply_10(int a)
    {
        a= a* 10;
        System.out.println(a);
    }
    static int multiplyTenAndReturnResult(int a)
    {
        return a*10;
    }





}
