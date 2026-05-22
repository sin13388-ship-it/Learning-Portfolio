package com.vera.multihreads;

public class Ch21_14 {
    static void main(String[] args) {
        //加了同步之後會先等執行緒的鎖
        Demo2 demo =new Demo2();
        Thread thread3=new Thread(new JobThreads3(demo));
        Thread thread4=new Thread(new JobThreads4(demo));

        thread3.start();
        thread4.start();
    }

}
class Demo2{
    public synchronized void printDemo(int n){
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
class JobThreads3 extends Thread{
    Demo2 pd;
    JobThreads3(Demo2 demo){
        pd=demo;
    }
    public void run(){
        pd.printDemo(10);
    }
}

class JobThreads4 extends Thread{
    //Demo pd;

    Demo2 pd;
    JobThreads4(Demo2 demo){
        pd=demo;
    }
    public void run(){
        pd.printDemo(100);
    }
}