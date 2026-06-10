package com.vera.composition;

public class ch14_18 {
    static void main(String[] args) {
        Sentra sentra =new Sentra();
        sentra.setMaxSpeed(220);
        sentra.setColor("Blue");
        sentra.showCarInfo();
        sentra.sentraShow();
    }

}
class  Car{
    private int maxSpeed;
    private  String color;
    public void setMaxSpeed(int maxSpeed){
        this.maxSpeed=maxSpeed;
    }
   public void setColor(String color){
        this.color=color;
    }
    public void showCarInfo(){
        System.out.println("max speed = " + maxSpeed + " color = "+color);
    }
}
class Engine{
    public void starting(){
        System.out.println("Engine starting");
    }
    public void running(){
        System.out.println("Engine running");
    }
    public void stopping(){
        System.out.println("Engine stopping");
    }
}
class Sentra extends Car{
    public void sentraShow(){
        Engine sentraEngine =new Engine();
        sentraEngine.starting();;
        sentraEngine.running();
        sentraEngine.stopping();
    }
}