package org.example;

public class MultithreadingExercise {
    static void main() {
        Thread tortoiseThread = new Thread(new ToroiseRunnable()); /*把ToroiseRunnable 放到執行續裡*/
        tortoiseThread.start();

        Thread rabbitThread = new Thread(new  RabbitRunnable()); /*把ToroiseRunnable 放到執行續裡*/
        rabbitThread.start();

        System.out.println("--- Main 執行緒已經執行完畢了 ---");

    }
}

class ToroiseRunnable implements Runnable{

    @Override
    public void run() {
        for(int i=1; i<=1000; i++){
            System.out.println("烏龜共跑 " + i + "公里");
        }
        System.out.println("---Toroise Thread End---");
    }
}

class RabbitRunnable implements Runnable{

    @Override
    public void run() {
        for(int i=1; i<=1000; i+=3){
            System.out.println("兔子共跑 " + i + "公里");
        }
        System.out.println("---Rabbit Thread End---");
    }
}