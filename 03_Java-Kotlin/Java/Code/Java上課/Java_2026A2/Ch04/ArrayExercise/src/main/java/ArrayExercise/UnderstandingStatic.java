package ArrayExercise;

class  person {
    int age;
    String name;
    static String classfication ="ManKind";
}

public class UnderstandingStatic {

    static void main(String[] args) {
        /*
        * static fields are "global" within the scope of their class,
        * and global state is a common source of bugs.
        * Since every instance of a class shares the same memory address for a static variable,
        * a change in one place is reflected everywhere.*/

        /*
        * Tips :The most effective way to prevent accidental changes is to make the variable immutable.
        * If a static variable is meant to be a constant (like a configuration value or a shared label),
        * always use final.
        * */

        person p1= new person();

        p1.age=12;
        p1.name="Andy";
        System.out.println("The person1 name = " + p1.name);
        System.out.println("The person1 age = " + p1.age);
        System.out.println("The person1 classification = " + person.classfication );

        person p2= new person();

        p2.age=12;
        p2.name="Andy";
        person.classfication="ManKind2"; /*全域變數會被改掉*/
        System.out.println("The person1 name = " + p2.name);
        System.out.println("The person1 age = " + p2.age);
        System.out.println("The person1 classification = " + person.classfication ); /*此處會變成 MainKind2*/

    }

}
