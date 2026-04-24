package employee_class_exercise;

public class P32_Employee_Salary_Hourly_Demo {
    static void main(String[] args) {
            Employee e =new Employee("Andy", "Taipei");
            Salary s =new Salary("Lily", "Tainan", 12345 );
            Hourly h =new Hourly("Harry", "Tau yuan,", 198, 40);

        System.out.println(e.mail() + " with computePay : " + e.computeRate());
        System.out.println(s.mail() + " with computePay : " + s.computeRate());
        System.out.println(h.mail() + " with computePay : " + h.computeRate());

        System.out.println();

        System.out.println(e.mail() + " with computePay : " + payEmployee(e));
        System.out.println(s.mail() + " with computePay : " + payEmployee(s));
        System.out.println(h.mail() + " with computePay : " + payEmployee(h));

    }

    static double payEmployee(Employee e){
       return e.computeRate();
    }

}
class Employee{
    String name;
    String address;
    Employee(String name, String address){
        this.name=name;
        this.address=address;
    }
    String mail(){
        String mailString;
        mailString = String.format("Mail to %s  %s \n", name, address);
        return mailString;
    }

    double computeRate(){
        return 0;
    }
}

class Salary extends Employee{
   double salary;
   Salary(String name, String address, double salary)
   {
       super(name, address);
       this.salary=salary;
   }
   @Override
   double computeRate(){
              return salary/52;
   }
}

class Hourly extends Employee{
    double hourlyRate;
    double hoursWorked;
    Hourly(String name, String address, double hourlyRate, double  hoursWorked){
        super(name, address);
        this.hourlyRate=hourlyRate;
        this.hoursWorked=hoursWorked;
    }
    @Override
    double computeRate(){
        return hourlyRate * hoursWorked;
    }
}

