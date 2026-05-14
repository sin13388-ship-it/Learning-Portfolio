package com.vera.ioexception;

public class ch20_23 {

    static void main(String[] args) {
        try{
            System.out.println("Try block");
            throw  new MyException("Throw an exception for testing");
        }
        catch(MyException exception){
            String msg=exception.getMsg();
            System.out.println("Exception block");
            System.out.println(msg);
        }
    }
}
class MyException extends Exception{
    //Custom exception
    String string;
    MyException(String msg){
        string=msg;
    }
    String getMsg(){
        return "MyException error : "+string;
    }
}
