package org.example.MethodBasics;

public class P13_StaticMethod_StaticAttribute
{

    static void main(String[] args) {
        /*
         * 一個.java 的檔案只能有一個class 是 public
         * 類別練習 : get 類別屬性和物件屬性
         *
         * */

        A.printData(); /*屬於類別方法，從類別呼叫*/
        System.out.println(A.printA()); /*屬於類別方法，從類別呼叫*/
        A testA=new A();
        System.out.println(testA.printB()); /*物件方法，必須實作後才能呼叫方法*/
    }
}
class A
{
    static int s_a=5; /*Static attribute : 靜態屬性 -> 類別屬性*/
    int i_b=3; /*Instance attribute : 實體屬性 -> 物件屬性 */
    static  void printData() {
         System.out.println("s_a= " + s_a);

        // System.out.println("i_b= " + i_b);  /*此處會違例，i_b 是物件屬性*/
        System.out.println("s_a= " + new A().i_b); /*可以但不建議, 存取物件屬性要實作A這個類別*/
    }
    static String printA()
    {
        return " s_a = " +s_a;
    }
    String printB()
    {
        return " i_b = " +i_b; /*同為物件不會違例*/
    }
}
