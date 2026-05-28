package Chapter08Exercise;

public class ch08_04 {
    static void main(String[] args) {
        Student student1=new Student();
        student1.studentID="A12345";
        student1.studentName="Vera";
        Student student2=new Student();
        student2.studentID="A67890";
        student2.studentName="Bill";
        student1.iam();
        student2.iam();
    }
}

class Student{
    public String studentID;
    public String studentName;
    public void iam(){
        System.out.println("I am "+studentID+":" + studentName );
    }
}
