package com.vera.genericexercise;

public class P24_Interface_Lambda {
    static void main(String[] args) {
        /*
        * () -> 1 + 2 + 3 的意思就是：「請建立類別並override方法，當有人呼叫它時，請回傳 1 + 2 + 3 的結果。
        * */

        /*anonymous 的寫法*/
        MyNumber myNumber =new MyNumber() {
            @Override
            public double getValue() {
                return 123.456;
            }
        };
        System.out.println(myNumber.getValue());

        MyNumber tmp =myNumber;

        /*從 anonymous 再延伸到 Lambda equation*/
        MyNumber myNumber2 =() ->1+2+3;
        System.out.println(myNumber2.getValue());

        /*
        * // Step 1
        * myNumber -> [Logic: Math.random() * 100]  (Object A)

        * // Step 2
        * // You create a new instance and move the pointer
        * myNumber -> [Logic: Math.sqrt(144)]       (Object B)
        * */
        myNumber =()->Math.sqrt(144);
        System.out.println(myNumber.getValue());
        System.out.println(tmp.getValue());

        NumberTest evenTest =n-> n%2 ==0; /*只有一個參數可以省略*/
        System.out.println( evenTest.test(201));

        NumberFunc evaluateFactorial=n->{
          int res=1;
          for (int i=1; i<=n; i++){
              res *=i;
          }
          return res;
        };
        System.out.println(evaluateFactorial.func(5));
    }
}

interface MyNumber {
    double getValue();
}

class Noname implements MyNumber{
    @Override
    public double getValue() {
        return 123.456;
    }
}

interface NumberTest{
    boolean test(int n);
}

interface NumberFunc{
    int func(int n);
}