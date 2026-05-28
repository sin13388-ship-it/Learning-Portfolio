package com.vera.threadsexample;

public class P14ThreadRunnableTask {
    static void main(String[] args) {
        Thread.currentThread().setName("Main_Thread");
        System.out.println(Thread.currentThread().getName() + "is Now Running");

        Thread workThread =new Thread(new RunnableTask());
        workThread.setName("workThread");
        workThread.setPriority(Thread.MAX_PRIORITY);

        workThread.start();
        System.out.println(Thread.currentThread().getName() + "is Ending");


        /*Lambda*/
        Thread viaLambdaTask =new Thread(()->{
            for (int i=0; i<=12; i++)
                System.out.println(Thread.currentThread().getName() + ": " + i );
            System.out.println(Thread.currentThread().getName() + "is Ending");
        });
        viaLambdaTask.setName("LambdaThread");
        viaLambdaTask.setPriority(Thread.MIN_PRIORITY);
        viaLambdaTask.start();
    }

}
class RunnableTask implements Runnable{
    @Override
    public void run() {
        for (int i=0; i<=10; i++)
            System.out.println(Thread.currentThread().getName() + ": " + i );
        System.out.println(Thread.currentThread().getName() + "is Ending");
    }
}