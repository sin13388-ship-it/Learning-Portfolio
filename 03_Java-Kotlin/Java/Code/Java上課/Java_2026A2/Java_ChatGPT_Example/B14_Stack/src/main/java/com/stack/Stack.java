package com.stack;

import java.util.ArrayList;

public class Stack {
    /*使用ArrayList來完成堆疊
    * 建立兩個方法 :
    * pop() : 會從ArrayList的開頭取出整數
    * push() : 會將一個整數新增至Arraylist 的開頭
    * 只要符合LIFO -> 堆疊 */

    static void main(String[] args) {

        ArrayList<Integer> myStack =new ArrayList<>();
        Stack.push(myStack,40);
        Stack.push(myStack,50);
        System.out.println("Pop 1: " + Stack.pop(myStack));
        System.out.println("Pop 2: " + Stack.pop(myStack));
        System.out.println("Pop 3: " + Stack.pop(myStack));
    }

    static void push(ArrayList<Integer> stack, int element)
    {
        /*使用Integer的好處，允許nullable
        * 如果只是單純的int, 不予許為空，會直接例外錯誤
        * 使用 Integer 回傳 null，能明確且優雅地告訴呼叫者：「目前堆疊中沒有任何東西可以取出」        *
        * */
        int indexPointer =0; /*從0，沒有一定*/
        stack.add(indexPointer,element);
    }

    static Integer pop(ArrayList<Integer> stack){
        int indexPointer =0; /*從0，沒有一定*/
        if(!isEmpty(stack)){
            return stack.remove(indexPointer);
        }else return null;

    }
    static Boolean isEmpty(ArrayList<Integer> stack){
        return stack.isEmpty();
    }
}
