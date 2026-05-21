package com.vera.multihreads;


/*
* 使用Runnable介面 執行 Thread
* 如果建構的Threads 卻沒有傳入runnable 物件，Thread 不會有動作
* */
public class Ch21_7 {
    static void main(String[] args) {
        Thread horse1=new Thread(new HorseRacing("Horse1"));
        Thread horse2=new Thread(new HorseRacing("Horse2"));
        horse1.start();
        horse2.start();
    }
}

class HorseRacing implements Runnable {
    private String name;
    HorseRacing(String name){
        this.name=name;
    }
    @Override
    public void run() {
        for(int i=1; i<=1000; i++){
            System.out.println("Execute " +name + " : "+ i+ " loop") ;
        }
        System.out.println(name + " end...");
    }
}