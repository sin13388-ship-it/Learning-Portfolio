package org.example;


public class ch9_15_bank_service {
    static void main() {

        TaipeiBank persionAccount=new TaipeiBank("Andy");
        persionAccount.saveMoney(10000);
        int taiwanDollar =1000;
        persionAccount.saveMoney(1000);
        System.out.printf("User :　%s\n", persionAccount.getName());
        System.out.printf("Balance :　%d\n", persionAccount.getBalance());
        System.out.printf("The NTD : %d can be exchanged %5.6f\n",taiwanDollar,persionAccount.exchangeTWtoUS(taiwanDollar));

    }
}

class TaipeiBank{

    private String name;
    private  int balance;
    private int changeRateTWtoUS=30;
    private double handlingCharge =0.01; /* 1% */

    TaipeiBank(String name){
        this.name=name;
        this.balance=0;
    }

    public String getName(){
        return name;
    }

    public void saveMoney(int money){
        balance+=money;
    }
    public int withdrawMoney(int money){
        if(money > balance) return -1;
        balance -=money;
        return 0;
    }
    public int getBalance(){
        return balance;
    }
    public double exchangeTWtoUS(int money){
        double usDollar=0;
        updateExchangeRate();
        usDollar=(double)money/changeRateTWtoUS * (1- handlingCharge);
        return usDollar;
    }

    private void updateExchangeRate(){
        if (balance >=10000) handlingCharge =0.008;
        else handlingCharge =0.01;
    }


}
