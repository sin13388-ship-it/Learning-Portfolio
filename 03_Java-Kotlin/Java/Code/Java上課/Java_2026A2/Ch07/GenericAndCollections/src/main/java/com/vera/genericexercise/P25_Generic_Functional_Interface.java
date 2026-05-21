package com.vera.genericexercise;

public class P25_Generic_Functional_Interface {
    static void main(String[] args) {

        //匿名類別String
        GenericFunc<String> reverse =new GenericFunc<String>(){
            @Override
            public String func(String t){
                String result="";

                for(int i =t.length()-1; i>=0;i--){
                    result += t.charAt(i);
                }
                return result;
            }
        };
        System.out.println(reverse.func("Andy"));
        //匿名類別Integer
        GenericFunc<Integer>factorial=new GenericFunc<Integer>() {
            @Override
            public Integer func(Integer t) {
                int res=1;
                for(int i =1; i <=t;i++){
                    res*=i;
                }
                return res;
            }
        };
        System.out.println(factorial.func(5));
        //Lambda
        GenericFunc<String>reverse2=(t)-> {
                String result="";
                for(int i =t.length()-1; i>=0;i--){
                    result += t.charAt(i);
                }
                return result;
        };
        System.out.println(reverse.func("Bill Gates"));

    }
}
interface GenericFunc<T>{
    T func(T t);
}