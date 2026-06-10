package com.vera.multihreads;

/*
* 有些時候某些類別只會使用一次，此時可以使用匿名類別
* 匿名類別只有本體
* 使用Ch21_14來改
* */
public class P21_15 {
    static void main(String[] args) {
        //沿用P21_14的類別
        Demo2 demo =new Demo2(); /*因為demo2 的方法有synchronized 所以會鎖住資源*/
        //匿名類別需要繼承某個類別或實作某個介面才能使用
        Thread t1=new Thread(){
          public void run(){
              demo.printDemo(10);
          }
        };
        Thread t2=new Thread(){
            public void run(){
                demo.printDemo(100);
            }
        };
        t1.start();
        t2.start();
    }
}
