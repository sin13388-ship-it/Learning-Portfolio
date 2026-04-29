package Chapter08Exercise;

public class ch08_01 {

    static void main(String[] args) {
        MyClass obj =new MyClass();
        System.out.println("Before text :" + obj.text);
        obj.text="DEF";
        System.out.println("After modified text :" + obj.text);
        obj.clear();
        System.out.println("clear text :" + obj.text);
    }
}
class MyClass{
    public String text ="ABC";
    public void clear(){
        text="";
    }
}