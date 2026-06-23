package vera.generic.exercise;

import java.util.HashMap;

public class Ch24_16 {
    static void main(String[] args) {
        /*HashMap 裡放的是物件*/

        HashMap<String, Phone> phonePriceTable =new HashMap<>();
        //Add
        phonePriceTable.put("iPhone 17 Pro Max", new Phone("iPhone 17 Pro Max (256GB)",41900 ));
        phonePriceTable.put("iPhone 17 Pro", new Phone("iPhone 17 Pro (128GB)",36900 ));
        phonePriceTable.put("Galaxy S26 Ultra", new Phone("iPhone 17 Pro Max (256GB)",43900 ));
        phonePriceTable.put("Pixel 10a", new Phone("Pixel 10a (128GB)",14990 ));

        System.out.println("\nTravel======");
        //Travel
        phonePriceTable.forEach((key, phone)->
                System.out.println("key= " + key + " | name= "+ phone.getpName() +" | price= " + phone.getPrice()));

        //Modify
        System.out.println("\nModify======");
        phonePriceTable.get("Pixel 10a").setPrice(12990);
        phonePriceTable.forEach((key, phone)->
                System.out.println("key= " + key + " | name= "+ phone.getpName() +" | price= " + phone.getPrice()));

        //Remove
        System.out.println("\nRemove======");
        phonePriceTable.remove("Pixel 10a");
        phonePriceTable.forEach((key, phone)->
                System.out.println("key= " + key + " | name= "+ phone.getpName() +" | price= " + phone.getPrice()));

    }
}

class Phone{
    private String pName;
    private int price;

    public Phone(String pName, int price) {
        this.pName = pName;
        this.price = price;
    }

    public String getpName() {
        return pName;
    }

    public void setpName(String pName) {
        this.pName = pName;
    }

    public int getPrice() {
        return price;
    }

    public void setPrice(int price) {
        this.price = price;
    }
}
