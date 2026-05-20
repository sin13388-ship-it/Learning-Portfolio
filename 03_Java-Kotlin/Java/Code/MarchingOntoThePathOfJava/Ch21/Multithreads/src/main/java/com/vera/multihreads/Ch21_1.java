package com.vera.multihreads;

public class Ch21_1 {
    /*當一個 Java 程式啟動時，負責執行應用程式進入點（Entry Point）的主執行緒（Main Thread），其預設名稱為 main*/
    static void main(String[] args) {
        Thread thread= Thread.currentThread(); //建立目前執行緒的物件
        System.out.println("Current thread= " + thread.getName());
        thread.setName("MyThread"); //更改名稱
        System.out.println("Current thread= " + thread.getName());
        System.out.println("Thread ID = " + thread.threadId());
    }
}
