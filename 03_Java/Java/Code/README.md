# Jave Learning Journal
*Vera Chang*

## Overview

- 課程名稱與時間 :

  - Java, 96小時

- 上課內容 :  

  - 1.資料型態 2.流程控制 3.陣列 4.方法 5.物件與類別 6.封裝、繼承 7.方法覆寫與多型 8.抽象類別與抽象方法 9.匿名、例外處理、泛型

## Contents

---
- [正規表達式](#正規表達式)
- [Multi-thread](#Multi-thread)
- [Lambda expression](#Lambda-expression)


### 正規表達式

#### 語法與對應的例題
                                                                                                                                                                                                                                                                                                                                                         
|語法| 說明                                      | 例題         |
|--|-----------------------------------------|------------|
|boolean matches(String regex) | 傳回字串是否符合正規表達式，如果比對結果符合會傳回true, 否則為false | ch13_3.java |
|Pipe| 可以同時搜尋比對多個字串,ex: TOM\|Mary ，注意字串不可以空白   |ch13_10.java|
|?|假設某括號內的字串可有可無(xo)?|ch13_11.java|
####  語法相關補充

- matches 字串長度與pattern不對稱 :
  假設正規表達式的pattern 是 "\\d"，但輸入"aa23"，matches的結果會是false，因為沒有符合個位數為數字
- 可以用{}來表示重複的數字: "\\d\\d\\d" 可以表示成 "\\d{3}"
- 可以用小括號分組 : 手機號碼 : \\{4}(-\\d{3}){2} 可以表示09xx-xxx-xxx

### Multi-thread
#### Synchronized method
如果在方法名稱前宣告`synchronized` 則該方法即為同步方法，同步會lock當前的資源，直到方法執行完成。
```java
//同步物件方法
class Demo2{
  public synchronized void printDemo(int n){
    for(int i=0; i< 10; i++){
      System.out.println("Output : " + (i*n));
    }
    try
    {
      Thread.sleep(500);
    }catch(InterruptedException e){
      System.out.println(e);
    }
  }
}
```

```java
//同步靜態方法
class Demo2{
   synchronized static void printDemo(int n){
   //...
  }
}
```
#### 使用Anonymous class
- 匿名類別需要繼承某個類別或實作某個介面才能使用
未改寫前:
```java
class JobThreads3 extends Thread{
    Demo2 pd;
    JobThreads3(Demo2 demo){
        pd=demo;
    }
    public void run(){
        pd.printDemo(10);
    }
}
```
改寫後:
```java
//不需要建構子，外部變數（如 demo）直接從外層作用域捕捉，但該變數必須是 final 或 effectively final
Demo2 demo2 =new Demo2(); /*因為demo2 的方法有synchronized 所以會鎖住資源*/
        //匿名類別需要繼承某個類別或實作某個介面才能使用
        Thread t1=new Thread(){
          public void run(){
              demo2.printDemo(10);
          }
        };
```

#### Synchronized block
假設一個方法內只有一部份需要同步，可以使用`Synchronized block`
```java
class DemoSyncBlock{
    public  void printDemo(int n){
        synchronized(this){
            for(int i=0; i< 10; i++){
                System.out.println("Output : " + (i*n));
            }
            try
            {
                Thread.sleep(500);
            }catch(InterruptedException e){
                System.out.println(e);
            }            
        }
    }
}
```
#### Inter Thread Communication
執行緒間通訊是指多個執行緒之間協調合作、共享資訊的機制，讓執行緒能夠在特定條件下暫停或繼續執行，
避免忙碌等待（busy waiting）浪費 CPU 資源。

**核心概念**
當多個執行緒需要共同完成一項任務時，它們必須能夠互相「溝通」——例如，一個執行緒等待另一個執行緒完成某項工作後才繼續執行。

**主要機制**

|方法|說明|
|---|---|
|wait()|讓當前執行緒釋放鎖並進入等待狀態|
|notify()|喚醒一個正在等待的執行緒|
|notifyAll()|喚醒所有正在等待的執行緒|

**課本範例**
- 此範例有一個缺陷，假設存款還是不足，thread1 for withdraw 將會永遠等待
  - 引發 `Deadlock / Thread Starvation`情境

```java
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
```
- 解決方法1 : `timeout`
  優點：簡單直接，防止永久卡住。
  缺點：等待時間難以決定，不夠精確。
```java
while (amount > balance) {
    try {
        wait(5000); // 最多等 5 秒
    } catch (InterruptedException e) {
        System.out.println(e);
    }

    // Timeout 後跳出 while，需要再次檢查
    if (amount > balance) {
        System.out.println("Timeout！餘額仍不足，取款失敗。");
        return; // 放棄這次取款
    }
}
```
- 解決方法2: 加入放棄條件（更嚴謹）
```java
private boolean depositDone = false; // 新增旗標

public synchronized void withdraw(int amount) {
    while (amount > balance) {
        if (depositDone) {
            // 存款已完成但還是不夠，直接放棄
            System.out.println("存款已完成但餘額仍不足，取款失敗。");
            return;
        }
        try {
            wait();
        } catch (InterruptedException e) {
            System.out.println(e);
        }
    }
    balance -= amount;
}

public synchronized void deposit(int amount) {
    balance += amount;
    depositDone = true; // 標記存款已完成
    notifyAll();
}
```

### Lambda expression

#### Monitor Handler Exercise

- 說明 :
    - 模擬伺服器監控CPU, Memory 的使用量
- 架構 :
    - Monitor handler interface :  一個介面存放事件的處理結果
    - CPUMonitor, MemMonior: 主要邏輯的處理，此處用lambda
    - EventDispatcher : 派佈事件給有註冊的handler
    - Server Event : Data transport object , 用來存放事件的資料

- Server Event: 
    - 想要紀錄甚麼資料?

    |Type|說明|Default value|
    |----|---|-------------|
    |String|確認當前的資料來自誰|CPU、MEM、DISK...|
    |double|sensor 資料| 數值|
    |long|Time stamp| ms|

- Event Dispatcher:
    - 將收到的資料轉發給有訂閱的人
    - private attribute : 一個list 用來存放handler
    - register(iMonitorHandler) : 註冊handler
    - dispatch(ServerEvent) : 發布事件request 給各個handler 
