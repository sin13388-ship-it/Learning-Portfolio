package vera.interfaceexercise;

//Interface Fly
interface Fly{
    void flying();
}
//Class can fly
class Bird implements Fly{
    @Override
    public void flying() {
        System.out.println("Flying...");
    }
}
class AirPlane implements Fly{
    @Override
    public void flying() {
        System.out.println("AirPlane....");
    }
}

//Interface Shape
interface Shape{
    double area();
    String showObjectInfo();
}
//Shape class
class Rectangle implements Shape{
    int width;
    int height;
    Rectangle(int width, int height){
        this.width=width;
        this.height=height;
    }
    @Override
    public double area() {
        return width * height;
    }

    @Override
    public String showObjectInfo() {
        return "Rectangle";
    }
}
class Circle implements Shape{
    static double PI= 3.14159;
    double radius;

    Circle(double radius){
        this.radius=radius;
    }
    @Override
    public double area() {
        return radius*radius*PI;
    }

    @Override
    public String showObjectInfo() {
        return "Circle";
    }
}

//Interface Vehicle
interface Vehicle{
    String getBrand();
    String Run();
    default String alarmOn(){
        return "alarmOn...";
    }
    default String alarmOff(){
        return "alarmOff...";
    }
}
class Car implements Vehicle{
    private String brand;
    Car(String brand){
        this.brand=brand;
    }
    @Override
    public String getBrand() {
        return brand;
    }
    @Override
    public String Run() {
        return "Car is running";
    }
    public String alarmOff(){
        return "自己要關閉";
    }
}

public class Ch17_01interface {
    static void main(String[] args) {
        Bird bird =new Bird();
        bird.flying();
        AirPlane plane =new AirPlane();
        plane.flying();

        Shape  myShape=new Rectangle(5,10);
        System.out.println("Myshape: " + myShape.showObjectInfo() + " area is " + myShape.area());
        myShape=new Circle(2.5);
        System.out.println("Myshape: " + myShape.showObjectInfo() + " area is " + myShape.area());

    }
}


