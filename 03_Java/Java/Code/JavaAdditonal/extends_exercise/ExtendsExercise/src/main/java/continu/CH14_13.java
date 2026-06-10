package continu;

public class CH14_13 {
    static void main(String[] args) {
        Cat cat =new Cat("Cherry", "fish");
        cat.eat(); //Animal method
        cat.printFavoriteFood(); //Mammal method
        cat.jumping(); //Cat method
    }
}
class Animal {
    protected String name;			// 宣告protected存取修飾符定義動物名字
    Animal(String name) {			// 建構方法最初化name
        this.name = name;
    }
    public void eat() {				// Animal方法eat
        System.out.println(name + " 正在吃食物");
    }
}

class Mammal extends Animal{
    protected String favorite_food;
    Mammal(String name, String favorite_food){
        super(name);
        this.favorite_food=favorite_food;
    }
    public void printFavoriteFood(){
        System.out.println(name + " like " +favorite_food);
    }
}
class Cat extends Mammal{
    Cat(String name, String favorite_food){
        super(name, favorite_food);
    }
    public void jumping(){
        System.out.println("The cat " + name + " is jumping");
    }
}