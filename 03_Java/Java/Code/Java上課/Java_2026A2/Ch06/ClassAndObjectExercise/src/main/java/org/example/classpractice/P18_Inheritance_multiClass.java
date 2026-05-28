package org.example.classpractice;

public class P18_Inheritance_multiClass {
    static void main(String[] args) {
        D classDObject =new D (2,3,4);
        System.out.printf("classDObject.a= %d \n", classDObject.a);
        System.out.printf("classDObject.b= %d \n", classDObject.b);
        System.out.printf("classDObject.d= %d \n", classDObject.d);

        /*class D 是 A 的子類別，繼承A 屬性，所以可以實作A 類別*/
        /*但是A類別不能向下取得子類別的屬性*/
        /*介面可以實作父類別，再根據需要轉型*/

        System.out.println();

        A classDObject2 =new D (5,6,7);
        System.out.printf("classDObject.a= %d \n", classDObject2.a);
        System.out.printf("classDObject.b= %d \n", ((B)classDObject2).b); /*強制型轉*/
        System.out.printf("classDObject.d= %d \n", ((D)classDObject2).d);
    }
}
class A{
    int a;
    A(int a){
        this.a=a;
    }
}
class B extends A{
    int b;
    B(int a, int b){
        super(a);
        this.b=b;
    }
}
class D extends B {
    int d;
    D(int a, int b, int d){
        super(a,b); /*初始化上一層*/
        this.d=d;
    }
}