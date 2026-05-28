package com.vera.genericexercise;

public class P10_GenericInterface {

    static void main(String[] args) {
        Box mybox =new Box();
        mybox.store(123);
        mybox.showInfo();

        GBox<String> sgBox =new GBox<>();
        sgBox.store("GBOX");
        sgBox.showInfo();
        GBox<Integer> igBox =new GBox<>();
        igBox.store(456);
        igBox.showInfo();
    }
}
interface IGCollection<T>{
    void store(T t);
    void showInfo();
}

class Box implements IGCollection<Integer>{

    /*如果只是一般的類別實作泛型的介面，必須明確告知型別，因為compiler 不知道*/

    private int element;
    @Override
    public void store(Integer t) {
        element=t;
    }

    @Override
    public void showInfo() {
        System.out.println("Box element : " + element);
    }
}

class GBox<T> implements IGCollection<T>
{
    /*如果要實作泛型介面，類別也必須是泛型*/
    private T element;

    @Override
    public void store(T t) {
        element=t;
    }

    @Override
    public void showInfo() {
        System.out.println("GBox element : " + element);
    }
}