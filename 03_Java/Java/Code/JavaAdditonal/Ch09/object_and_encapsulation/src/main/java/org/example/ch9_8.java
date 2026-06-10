package org.example;

public class ch9_8 {
    static void main(String[] args) {
        Student S1 = new Student();
        S1.Sno = "1001";
        S1.Sname = "JOHN";
        S1.Score = 500; // ?? too big Max=100，無法設規則
        S1.Iam(); // 500

        Student_withEncapsulation s2 =new Student_withEncapsulation();
        s2.setScore(700);
        s2.setSname("Mary");
        s2.setSno("1002");
        s2.Iam();
    }
}
class Student {
    //Without encapsulation
    public String Sno;
    public String Sname;
    public int Score;
    public void Iam() {
        System.out.println("I am " + Sno + ":" + Sname + " score=" + Integer.toString(Score));
    }
}

class Student_withEncapsulation{
    private String Sno;
    private String Sname;
    private int Score;

    public void setSno(String sno) {
        Sno = sno;
    }

    public String getSno() {
        return Sno;
    }
    public String getSname() {
        return Sname;
    }
    public void setSname(String sname) {
        Sname = sname;
    }
    public int getScore() {
        return Score;
    }
    public void setScore(int score) {
        Score = score;
    }
    public void Iam() {
        System.out.println("I am " + Sno + ":" + Sname + " score=" + Integer.toString(Score));
    }

}