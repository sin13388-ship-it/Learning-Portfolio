package employee_class_exercise;

public class P49_Final_Class_Mrthod_Static_Demo {
    static void main(String[] args) {
            Plane plane =new Plane(10, 20);
            Space space=new Space(1,2,3);
            Plane space2=new Space(4,5,6);

        System.out.println("x = " + plane.x + " y = " + plane.y + " Area = " + plane.computeArea());
        System.out.println("x = " + space.x + " y = " +  space.y +  " z= " + space.z + "Area = " +  space.computeArea());
        /*Attribute 要 type casting, method 不用*/
        System.out.println("x = " + space2.x + " y = " +  space2.y +  " z= " + ((Space)space2).z + "Area = " +  space2.computeArea());

        System.out.println("Plane.computeExtraArea() : " + Plane.computeExtraArea()); /*不是override*/
        System.out.println("Space.computeExtraArea() : " + Space.computeExtraArea()); /*不是override*/
    }
}

class Plane{
    int x;
    int y;
    static final int extra=100;
    Plane(int x, int y){
        this.x=x;
        this.y=y;
    }
    int computeArea(){
        return x*y;
    }
    static int computeExtraArea(){
        /*static  method 不能被override*/
        return extra;
    }
}

class Space extends Plane{
    int z;
    static int ss =10;
    Space(int x, int y, int z){
        super(x,y);
        this.z=z;
    }
    @Override
    int computeArea(){
        return x*y*z;
    }
    static int computeExtraArea(){
        /*static  method 不能被overrode*/
        return extra + ss;
    }
}