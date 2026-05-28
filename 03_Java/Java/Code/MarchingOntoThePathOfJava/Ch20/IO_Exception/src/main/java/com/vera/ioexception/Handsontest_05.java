package com.vera.ioexception;

public class Handsontest_05 {
    public static void main(String[] args) {
        int[] ages = {12,19,67};
        Vote parseAge=new Vote();
        for(int i :ages)
        {
            try
            {
                parseAge.parse(i);
                System.out.println(i+"歲歡迎投票");
            }
            catch (UnderageException e)
            {
                System.out.println(e.getAge()+"歲的年齡太輕");
                System.out.println("Error! "+e.getClass().getSimpleName()+": "+e.getMessage());
            }
        }
        System.out.println("測試年齡愉快");
    }
}
class Vote {
    void parse(int age) throws UnderageException {
        if(age<18) throw new UnderageException("年齡不符規定", age);
    }
}
class UnderageException extends Exception{

    private int age;
    UnderageException(String msg, int age){
        super(msg); //直接使用exception 本來的
        this.age=age;
    }
    int getAge()
    {
        return age;
    }
}