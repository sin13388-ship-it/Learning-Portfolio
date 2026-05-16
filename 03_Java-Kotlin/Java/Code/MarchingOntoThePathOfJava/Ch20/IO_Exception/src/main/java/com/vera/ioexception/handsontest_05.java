package com.vera.ioexception;

public class handsontest_05 {
    static void main(String[] args) {
        int[] ages = {12,19,67};
        for(int i :ages)
        {
            try
            {
                Vote parseAge=new Vote();

                parseAge.parse(i);
                System.out.println(i+"歲歡迎投票");

            }
            catch (UnderageException e)
            {
                System.out.println(e.getAge()+"歲的年齡太輕");
                System.out.println("Error! "+e+": "+e.getMsg());
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
    private String msg;
    private int age;
    UnderageException(String msg, int age){
        this.msg=msg;
        this.age=age;
    }
    String getMsg(){
        return msg;
    }
    int getAge()
    {
        return age;
    }
}