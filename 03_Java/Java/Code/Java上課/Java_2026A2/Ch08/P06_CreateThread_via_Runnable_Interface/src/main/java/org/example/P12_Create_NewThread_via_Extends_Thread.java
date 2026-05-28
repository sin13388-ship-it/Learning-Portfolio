package org.example;

public class P12_Create_NewThread_via_Extends_Thread {
    static void main(String[] args) {
        Thread.currentThread().setName("MainThread");
        RabbitThread rabbitThread =new RabbitThread("rabbitThread");
        TortoiseThread tortoiseThread =new TortoiseThread("tortoiseThread");
        rabbitThread.start();
        tortoiseThread.start();
        System.out.println("--- " + Thread.currentThread().getName()+ " Thread End---");
    }
}
class RabbitThread extends Thread{
    RabbitThread(String name){
        super(name);
    }
    public void run(){
        for(int i=1; i<=1000; i+=3){
            System.out.println("兔子共跑 " + i + "公里");
        }
        System.out.println("--- " + Thread.currentThread().getName()+ " Thread End---");
    }
}

class TortoiseThread extends Thread{
    TortoiseThread(String name){
        super(name);
    }
    public void run(){
        for(int i=1; i<=1000; i++){
            System.out.println("烏龜共跑 " + i + "公里");
        }
        System.out.println("--- " + Thread.currentThread().getName()+ " Thread End---");
    }
}