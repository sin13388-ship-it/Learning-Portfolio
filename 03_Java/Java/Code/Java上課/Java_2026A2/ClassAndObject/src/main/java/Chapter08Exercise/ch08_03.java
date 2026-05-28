package Chapter08Exercise;

public class ch08_03 {
    static void main(String[] args) {
        SmallMath test =new SmallMath(5,6);
        test.add();
        test.multiple();

    }
}
class SmallMath{
    int x,y;
    SmallMath(int x, int y){
        this.x=x;
        this.y=y;
    }
    public void add(){
        System.out.println("add= " + (x+y));
    }
    public  void multiple(){
        System.out.println("Multiple= " + (x*y));
    }
}