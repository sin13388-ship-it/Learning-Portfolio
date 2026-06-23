package vera.generic.exercise;

import java.util.HashMap;
import java.util.Map;
import java.util.function.BiConsumer;

/*Map Exercise*/
public class Ch24_13 {
    static void main(String[] args) {

        /*HashMap 是無序的*/
        HashMap<Integer, String> map1 =new HashMap<>();
        map1.put(105, "Cat");
        map1.put(102, "Dog");
        map1.put(106, "Bird");
        System.out.println(map1); //可以直接Output

        //新增跟修改都是用put，若key已存在會覆蓋原本的資料
        map1.put(102, "Horse");
        System.out.println(map1); //可以直接Output

        //取值
        var mapVal = map1.get(102);
        System.out.println("The value is : " + mapVal);

        //Travel
        System.out.println("Travel------");

        /*Map 無法用for loop, 因為key 是無序的
        * >> 使用Map.Entry/entrySet 拿到 key-value pair*/
        for (Map.Entry<Integer, String> pair : map1.entrySet()){
            System.out.println("key: " + pair.getKey() +" , Value: "+ pair.getValue());
        }


        /*forEach Anonymous */
        System.out.println("Travel (anonymous)------");
        map1.forEach(new BiConsumer<Integer, String>() {
            @Override
            public void accept(Integer integer, String s) {
                System.out.println("key: " +integer +" , Value: "+s);
            }
        });

        /*forEach Lambda */
        System.out.println("Map1 Travel (Lambda)------");
        map1.forEach((key,s)->System.out.println("key: " +key +" , Value: "+s));

        /*Map 型態是Object
        * 類似於Kotlin 的 <Any>?
        * */
        HashMap<Object, Object> map2 =new HashMap<>();
        map2.put(102, "aaaa");
        map2.put("A01",345);
        map2.put(true, "isConnected");
        map2.put(false, "isDisconnected");
        System.out.println("Map2 Travel (Lambda)------");
        map2.forEach((key,s)->System.out.println("key: " +key +" , Value: "+s));



    }
}
