package InterfaceExercise;

public class P57_Interface_Demo {
    static void main(String[] args) {
        GrandFather G= new GrandFather();
        Father F= new Father();
        Son S=new Son();

        System.out.println("-----GrandFather------");
        G.driving();
        System.out.println("----------Father--------");
        F.driving();
        F.swimming();
        System.out.println("-------------Son---------");
        S.driving();
        S.driving("Ford");
        S.swimming();
        S.running();
    }
}

interface CanDriving{
    void driving();
}
interface  CanSwimming{
    void swimming();
}
interface CanRunning{
    void running();
}

class GrandFather implements CanDriving{
    @Override
    public  void driving(){
        System.out.println("I can do GrandFather Driving");
    }
}

class Father extends GrandFather implements CanSwimming{
    public void swimming(){
        System.out.println("I can do Father Swimming");
    }
}

class Son extends Father implements CanRunning{
     @Override
    public void running() {
        System.out.println("I can do  Son running");
    }
    public void driving(String type){
        System.out.println("I can do Son " + type + " Driving");
    }
}