package com.vera.ioexception;

//新增一個NotEnoughException，當餘額不足時會發生異常並顯示短少的金額
//使用throws關鍵字合法處裡異常
public class Ch20_24 {
    static void main(String[] args) {
        MyBank myBank=new MyBank();

        try{
            myBank.deposit(1000);
            System.out.println("Balance : " + myBank.getBalance());
            myBank.withdraw(5000);
        }
        catch (NotEnoughException e) {
            System.out.println("Insufficient balance : "+ e.getShortfall());
            e.printStackTrace(); //列印出位置
        }




    }
}
class NotEnoughException extends  Exception{
    private int shortfall;
    NotEnoughException(int shortfall){
        this.shortfall=shortfall;
    }
    int getShortfall(){
        return shortfall;
    }
}
class MyBank{
    private int balance;
    void deposit(int cashIn){
        balance+=cashIn;
    }
    void withdraw(int cashOut) throws NotEnoughException{
        if (balance>cashOut) balance-=cashOut;
        else throw new NotEnoughException(cashOut-balance);
    }
    int getBalance(){
        return balance;
    }

}
