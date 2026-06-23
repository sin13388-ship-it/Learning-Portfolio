package vera.generic.exercise;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Consumer;

public class Ch24_05 {
    static void main(String[] args) {
        /*ArrayList Generic*/

        ArrayList<String> arr =new ArrayList<>();

        arr.addAll(List.of("AAA","BBB","CCC"));

        //Travel

        /*for each 變化型*/

        for(var s :arr){
            System.out.printf("%s\t", s);
        }
        System.out.println();

        /*forEach method (lamda 前身)
         *Consumer 是一個介面，包含一個抽象方法accept*/
        arr.forEach(new Consumer<String>() {
            @Override
            public void accept(String s) {
                System.out.printf("%s\t", s);
            }
        });
        System.out.println();

        /*lambda
         *Consumer 只有一個抽象方法，所以可以用lambda 來寫*/
        System.out.println("Lambda---");
        arr.forEach(s->System.out.printf("%s\t", s));
        System.out.println();

    }
}
