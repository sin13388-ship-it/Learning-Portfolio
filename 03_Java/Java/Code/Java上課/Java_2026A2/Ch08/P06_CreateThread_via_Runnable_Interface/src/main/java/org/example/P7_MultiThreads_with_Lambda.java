package org.example;

public class P7_MultiThreads_with_Lambda {
    static void main(String[] args) {
        //使用lambda實作抽象方法
        Thread tortoiseThread =new Thread(()->{
            for(int i=1; i<=1000; i++){
                System.out.println("烏龜共跑 " + i + "公里");
            }
            System.out.println("--- " + Thread.currentThread().getName()+ " Thread End---");
        });
        tortoiseThread.setName("Tortoise");
        tortoiseThread.start();

        Thread  rabbitThread =new Thread(()->{
            for(int i=1; i<=1000; i+=3){
                System.out.println("兔子共跑 " + i + "公里");
            }
            System.out.println("--- " + Thread.currentThread().getName()+ " Thread End---");
        });
        rabbitThread.setName("Rabbit");
        rabbitThread.start();

        System.out.println("--- " + Thread.currentThread().getName()+ " Thread End---");
    }
}
