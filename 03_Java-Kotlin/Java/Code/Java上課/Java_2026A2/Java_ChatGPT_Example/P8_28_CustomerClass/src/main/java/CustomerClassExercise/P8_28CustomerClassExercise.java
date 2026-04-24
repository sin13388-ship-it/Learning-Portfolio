package CustomerClassExercise;

public class P8_28CustomerClassExercise {
    private  int id =3;

    static void main(String[] args) {
       //違例  id=5;
       // 違例  showID();
        P8_28CustomerClassExercise customerClassExercise =new P8_28CustomerClassExercise();
        customerClassExercise.id=5;
        customerClassExercise.showID();
    }
    protected void showID()
    {
        //protected 誤導，亂寫
        System.out.println(id);
    }
}
