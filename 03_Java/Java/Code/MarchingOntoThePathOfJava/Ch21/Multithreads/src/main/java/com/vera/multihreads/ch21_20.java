package com.vera.multihreads;

/*
* 簡單的工廠生產、庫存管理
* 使用執行緒來完成以下的工作 :
*  當還有庫存時，停止生產並通知消費
*  當庫存為0時，通知消費並停止生產
* */

import java.util.Random;

public class ch21_20 {
    static void main(String[] args) {

        //same factory
        Factory factory=new Factory();
        Producer producer =new Producer(factory);
        Consumer consumer=new Consumer(factory);

        producer.start();
        consumer.start();
    }
}

class Factory{
    /*擁有兩個方法: produce, consume
    * produce :　如果庫存就停止生產，並等待/通知消費
    * consume : 如果沒有庫存停止消費， 並等待/通知生產*/

    private int inventory;
    private boolean isEmpty;
    Factory(){
        isEmpty=true;
    }
    public synchronized void  produce(int amount){
        while(!isEmpty){
            try {
                wait();
            }catch (InterruptedException e){
                System.out.println(e);
            }
        }
        inventory =amount;
        System.out.println("Produce: " + amount);
        isEmpty=false;
        notify();
        try
        {
            Thread.sleep(500);

        }catch (InterruptedException e)
        {
            System.out.println(e);
        }
    }

    public synchronized void consume(){
        while (isEmpty){
            try
            {
                wait();
            }catch (InterruptedException e)
            {
                System.out.println(e);
            }
        }
        isEmpty=true;
        System.out.println("Cosume : " + inventory);
        notify();
        try{
            Thread.sleep(500);
        }catch (InterruptedException e)
        {
            System.out.println(e);
        }
    }
}
class Producer extends  Thread{
    private Factory factory;
    Producer(Factory factory){
        this.factory=factory;
    }
    public void run(){
        //Keep producing
        Random rand=new Random();
        while(true){
            factory.produce(rand.nextInt(1000));
        }
    }
}
class  Consumer  extends  Thread{
    private Factory factory;
    Consumer(Factory factory){
        this.factory=factory;
    }
    //Keep consuming
    public void run(){
        while(true){
            factory.consume();
        }
    }
}
