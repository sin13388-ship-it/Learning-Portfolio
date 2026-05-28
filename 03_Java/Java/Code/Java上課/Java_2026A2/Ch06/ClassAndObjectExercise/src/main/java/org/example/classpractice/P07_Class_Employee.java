package org.example.classpractice;

public class P07_Class_Employee {

    static void main(String[] args) {

        Employee employee1, employee2;

        employee1=new Employee();
        employee1.name="Andy";
        employee1.salary=3000000;
        employee1.address="Tau-yuan";

        employee2=new Employee();
        employee2.name="Lily";
        employee2.salary=3500000;
        employee2.address="Tainan";

        employee1.mailCheck();
        employee2.mailCheck();
    }
}
class Employee
{
    String name;
    String address;
    double salary;

    Employee(){}

    /*private constructor*/

    Employee(String name, String add, double salary){
        this(name, add);
        this.salary=salary;
    }
    private Employee(String name, String add){
        this.name=name;
        this.address=add;
    }

    double computeWeeklyPay(){
        return salary/52;
    }
    void mailCheck(){
        System.out.println("Mailing check to name: " + name+ " addr: " + address + " Salary: "+ salary + " WeeklyPay :" + computeWeeklyPay());
    }
}