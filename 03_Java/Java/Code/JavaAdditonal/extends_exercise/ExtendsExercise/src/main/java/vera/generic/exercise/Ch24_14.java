package vera.generic.exercise;

import java.util.ArrayList;
import java.util.List;

public class Ch24_14 {
    static void main(String[] args) {

        ArrayList<Student> arr =new ArrayList<>();

        //匿名物件加入arrayList
        arr.add(new Student("Mary",101,96));
        arr.addAll(List.of(new Student("Lily",102,78),
                new Student("Bob",103,96),
                new Student("Nancy",104,88)
                ));

        //修改物件裡的值，先用Get 拿到物件，用setter 修改
        arr.get(0).setsName("TestMary");

        //Travel
        System.out.println("Name, No, Score:");
        arr.forEach(s->{
            System.out.println(s.getsName()+" , "+ s.getNo() + " , "+ s.getScore());
        });

        arr.remove(0);

        arr.forEach(s->{
            System.out.println(s.getsName()+" , "+ s.getNo() + " , "+ s.getScore());
        });
    }
}
class Student{

    private String sName;
    private int no;
    private int score;

    public String getsName() {
        return sName;
    }

    public void setsName(String sName) {
        this.sName = sName;
    }

    public int getNo() {
        return no;
    }

    public void setNo(int no) {
        this.no = no;
    }

    public int getScore() {
        return score;
    }

    public void setScore(int score) {
        this.score = score;
    }

    public Student(String sName, int no, int score) {
        this.sName = sName;
        this.no = no;
        this.score = score;
    }
}