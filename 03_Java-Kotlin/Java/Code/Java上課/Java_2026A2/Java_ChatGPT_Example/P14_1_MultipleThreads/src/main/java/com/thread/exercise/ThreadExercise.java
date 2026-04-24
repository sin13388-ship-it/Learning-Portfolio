package com.thread.exercise;

import java.util.ArrayList;

public class ThreadExercise {
    static void main(String[] args) {
        Thread.currentThread().setName("Main_Thread");
        System.out.println(Thread.currentThread().getName() + "Finished");
        Thread factorialThread =new Thread(new FactorialTask(10));
        factorialThread.setName("Factorial thread");

        Thread primeThread=new Thread(new PrimeNumberTask(500));
        primeThread.setName("Prime thread");
        factorialThread.start();
        primeThread.start();

    }
}

class FactorialTask implements Runnable{

    private int n;
    FactorialTask(int n){
        this.n =n;
    }
    @Override
    public void run() {
        int res=1;
        for(int i = (int)n; i>=1; i--){
            res *=i;
        }
        System.out.printf("Factorial(%d)= %d\n", n, res);
        System.out.println(Thread.currentThread().getName() + " Finished");
    }
}

class PrimeNumberTask implements Runnable{
    private int n;
    private ArrayList<Integer> list =new ArrayList<>();
    PrimeNumberTask(int n) {
        this.n=n;
    }
    @Override
    public void run() {
        boolean isPrime=true;
        for(int i =2; i <=n; i++){
            for(int j=2; j <i ; j++){

                if (i%j==0) {
                    isPrime=false;
                    break;
                }

            }
            if(isPrime) list.add(i);
            isPrime=true;
        }
        System.out.println(list + "\n Total : "+ list.size());
        System.out.println(Thread.currentThread().getName() + " Finished");
    }
}