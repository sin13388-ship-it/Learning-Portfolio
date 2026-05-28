package org.example.classpractice;

public class P14_Student_CTOR {
    static void main(String[] args) {

        Student person1 =new Student("Andy", 95);
        person1.printInfo();
        Student person2=new Student();
        person2.printInfo();
        Student person3=new Student(86, "Lily");
        person3.printInfo();
    }
}
class Student{

    int score;
    String name;

    Student(String name, int score){
        this.name=name;
        this.score=score;
    }
    Student(int score, String name ){
      /*再包一層*/

       this(name, score);
    }
    Student()
    {
        /*Initialize*/
        /*this () 會呼叫標準Constructure，並給入初始值*/
        /*可以用來給定serial port 預設值*/
        this("Bill", 78);
    }
    public void printInfo(){
        System.out.printf("Name: %s | Score : %d \n", name, score);
    }
}