package abstractmethod;

public class AbstrcatClassExercise {
    /*Abstact class exercise
    * 抽象類別不能被實體化，只能被用於繼承*/
    static void main(String[] args) {
        Car myCar =new BMW();
        myCar.refuel();
        myCar.run();

        Arithmetic myCalculator =new CalDivide(5,0);
        myCalculator.calculate();
    }
}

abstract class Car{
    abstract void run(); //abstract method
    Car(){ //一般方法
        System.out.println("I have a car!");
    }
    public void refuel(){ //default method
        System.out.println("Fueling up");
    }
}
class BMW extends Car{
    private String name="BMW";
    /*繼承的類別必須覆寫抽象方法*/
    @Override
    void run() {
        System.out.println(name+ " is running");
    }
    BMW(){
        System.out.println("I have a BMW!");
    }
}

abstract class Arithmetic {
    /*建立一個抽象類別，並提供四則運算的抽象方法 calculate, 供子類別繼承*/
    public int x;
    public int y;
    Arithmetic(int x, int y){
        this.x =x;
        this.y=y;
        System.out.println("Initialize parameters");
    }
    abstract  double calculate();
}
class CalPlus extends Arithmetic{
    CalPlus(int x, int y){
        super(x,y);
    }
    @Override
    double calculate() {
        return x+y;
    }
}

class CalMinus extends Arithmetic{
    CalMinus (int x, int y){
        super(x,y);
    }
    @Override
    double calculate() {
        return x-y;
    }
}

class CalMultiple extends Arithmetic{
    CalMultiple(int x, int y){
        super(x,y);
    }
    @Override
    double calculate() {
        return x*y;
    }
}

class CalDivide extends Arithmetic{
    CalDivide(int x, int y){
        super(x,y);
    }
    @Override
    double calculate() throws ArithmeticException {
        if(y ==0) throw new ArithmeticException();
        return x/y;
    }
}