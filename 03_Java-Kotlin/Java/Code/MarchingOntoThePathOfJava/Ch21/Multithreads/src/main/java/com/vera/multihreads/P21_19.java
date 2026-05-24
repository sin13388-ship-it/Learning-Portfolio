package com.vera.multihreads;

/*
* Inter-thread communication 練習
* 假設有一個銀行類別bank，存款和提款為同步
* 如果發生存款不足，則會進入等待存款的執行緒
*
* */

public class P21_19 {
    static void main(String[] args) {
        Bank bank=new Bank();
        Thread t1=new Thread(){
            public void run(){
                bank.withdraw(15000);
            }
        };
        t1.start();
        Thread t2 =new Thread(){
            public void run(){
                bank.deposit(5000);
            }
        };
        t2.start();
    }
}
class Bank{
    private int balance=10000;
    /*真正需要保護的確實是 balance，但 Java 的鎖機制無法直接鎖住一個變數，只能鎖住物件（Object）。
    * 「任何執行緒要執行這個方法，必須先取得這個 Bank 物件的鎖（lock），用完才釋放。」
    * 所以同一時間，只有一個執行緒能進入任何一個 synchronized 方法，balance 自然就被間接保護了。*/
    public  synchronized void withdraw(int amount){
        System.out.println("Withdraw process...");
        if(amount > balance)
        {
            System.out.println("Insufficient funds. Please deposit.");
        }
        //call deposit thread
        while (amount>balance){
            try{
                //讓當前執行緒釋放鎖並進入等待狀態
                wait();
            }
            catch (InterruptedException e){
                System.out.println(e);
            }
        }
        balance-=amount;
        System.out.println("Withdraw finished..");
    }

    public  synchronized void deposit(int amount){
        System.out.println("Deposit process...");
        balance +=amount;
        System.out.println("Deposit finished...");
        notify(); //喚醒一個正在等待的執行緒
    }
}