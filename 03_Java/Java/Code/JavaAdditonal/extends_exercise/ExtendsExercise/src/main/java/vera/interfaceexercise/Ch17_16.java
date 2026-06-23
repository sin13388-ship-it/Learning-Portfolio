package vera.interfaceexercise;

/*使用介面作為參數傳遞至方法
* 明確class和匿名class
* lambda
* */
public class Ch17_16 {
    static void main(String[] args) {
        //有明確的類別
        Animal aObj =new Temp();
        Cat cat =new Cat();
        cat.showMe(aObj);
        //匿名類別
        Cat cat2 =new Cat();
        cat2.showMe(new Animal() {
            @Override
            public void running() {
                System.out.println("Running...(Anonymous)");
            }
        });
        //Lambda
        Cat cat3 =new Cat();
        cat3.showMe(()->{System.out.println("Running...(Lambda)");}
        );
    }
}
interface Animal{
    void running();
}
class Temp implements Animal{
    @Override
    public void running() {
        System.out.println("Running(Temp)....");
    }
}
class Cat{
    public void showMe(Animal object){
        System.out.println("showMe...");
        object.running();
    }
}