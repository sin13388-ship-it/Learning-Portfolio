package com.vera.multihreads;


/*
* Synchronized block
* 如果只有某部分需要同步可以使用 Synchronized block
* 鎖住部分區塊
* */

public class P21_16 {
    static void main(String[] args) {
        /*結果應與2!_14相同*/
        DemoSyncBlock demo =new  DemoSyncBlock ();
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
class DemoSyncBlock{
    public  void printDemo(int n){
        synchronized(this){
            for(int i=0; i< 10; i++){
                System.out.println("Output : " + (i*n));
            }
            try
            {
                Thread.sleep(500);
            }catch(InterruptedException e){
                System.out.println(e);
            }
        }
    }
}