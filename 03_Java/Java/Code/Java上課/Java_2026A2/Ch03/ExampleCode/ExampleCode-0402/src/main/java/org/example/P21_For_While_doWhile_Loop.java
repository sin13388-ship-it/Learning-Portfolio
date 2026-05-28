package org.example;

public class P21_For_While_doWhile_Loop {
    static void main(){
        /*
        * For loop 練習
        * While loop
        * doWhile loop
        * */
        int sum;
        sum=0;

        //For loop
        for(int i =0; i<=10; i++){
            sum+=i;
        }
        System.out.println("Sum (For loop) = "+ sum);
        //While loop
        sum=0;
        int i=1;
        while(i<=10){
            sum=sum+i;
            i++;
        }
        System.out.println("Sum (While loop)= "+ sum);
        //doWhile
        sum=0;
        i=1;
        do{
            sum+=i;
            i++;
        }while(i<=10);
        System.out.println("Sum (do while)= "+ sum);
    }
}
