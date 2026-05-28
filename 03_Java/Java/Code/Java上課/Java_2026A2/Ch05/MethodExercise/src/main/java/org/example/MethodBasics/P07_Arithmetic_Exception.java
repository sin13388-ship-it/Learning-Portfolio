package org.example.MethodBasics;

import java.util.Scanner;


public class P07_Arithmetic_Exception  {
    static void main(String[] args) throws Exception{

        /*
         * 例外錯誤練習
         * Try
         * {
         *      //敘述
         * }
         * Catch(Exception e)
         * {
         *      //例外處理
         * }
         * finally
         * {
         *      //不管如何都要做
         * }
         * */

        Scanner scanner =new Scanner(System.in);
        System.out.println("Please input a number :");
        int n1=scanner.nextInt();
        System.out.println("Please input another number :");
        int n2=scanner.nextInt();

        int result=0;

        result=n1/n2;
        System.out.println("The result is " + result);

        try /*執行*/
        {

            result=n1/n2;
            System.out.println("The result is " + result);
        }
        catch (Exception e) /*例外處理*/
        {

            System.out.println(e.toString());
        }
        finally { /*無論如何都要做*/
            System.out.println("Bye");
        }










    }
}
