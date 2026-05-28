package org.example;

import java.util.ArrayList;
import java.util.Iterator;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    static void main(String[] args) {

        ArrayList<Integer> originNumbers = new ArrayList<>();
        for(int i = 2; i <= 50; i++) originNumbers.add(i);

        // 第一次輸出
        System.out.println("Before: " + originNumbers);
        Iterator<Integer> primeNumbers = originNumbers.iterator();
        while(primeNumbers.hasNext()){
            int num = primeNumbers.next();
            // 質數判斷邏輯
            for(int j = 2; j < num; j++){
                if(num % j == 0){
                    primeNumbers.remove();
                    break;
                }
            }
        }
        // 第二次輸出
        System.out.println("After: " + originNumbers);
    }
}
