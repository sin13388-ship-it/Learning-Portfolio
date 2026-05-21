package com.vera.multihreads;


/*Join 讓當前執行緒執行完才開始下一個執行緒*/
public class P21_9 {
    static void main(String[] args) {
        Thread horse1=new Thread(new HorseRacing("Horse1"));
        Thread horse2=new Thread(new HorseRacing("Horse2"));
        horse1.start();
        /*Join 有Throws 關鍵字*/
        try {
            horse1.join();
        }catch (InterruptedException e){
            System.out.println(e);
        }
        horse2.start();
    }
}
