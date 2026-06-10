package com.vera.multihreads;

import java.sql.SQLOutput;

/*
* Synchronization
* 執行緒的記憶體空間是共享的，所以需要有一個機制處理共享資源

* */
public class Ch21_13 {
    static void main(String[] args) {
        //示範沒有同步會發生的問題，資源會互相影響
        Demo demo =new Demo();
        Thread thread1=new Thread(new JobThreads1(demo));
        Thread thread2=new Thread(new JobThreads2(demo));

        thread1.start();
        thread2.start();

    }
}
class Demo{
    public void printDemo(int n){
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

class JobThreads1 extends Thread{
    Demo pd;
    JobThreads1(Demo demo){
        pd=demo;
    }
    public void run(){
        pd.printDemo(10);
    }
}

class JobThreads2 extends Thread{
   //Demo pd;

    Demo pd;
    JobThreads2(Demo demo){
        pd=demo;
    }
    public void run(){
        pd.printDemo(100);
    }
}



