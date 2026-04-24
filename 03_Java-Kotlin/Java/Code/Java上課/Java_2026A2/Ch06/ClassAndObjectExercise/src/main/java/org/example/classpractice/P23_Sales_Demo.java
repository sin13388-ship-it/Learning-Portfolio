package org.example.classpractice;

public class P23_Sales_Demo {
    static void main(String[] args) {
        Sales sales =new Sales("Andy", 123, 0.08);

        sales.addToSales(1000000);
        System.out.printf("The sales : %s , commissionRate is %10.3f", sales.getName(),sales.computeCommission());
    }
}


class Sales{
    private String name;
    private int id;
    private double comissionRate;
    private double sales;

    Sales(String name, int id, double commissionRate){
        this.name=name;
        this.id=id;
        this.comissionRate=commissionRate;
        sales=0;
    }
    public void addToSales(double s){
        sales +=s;
    }
    public String getName(){
        return name;
    }

    public double getComissionRate(){
        return comissionRate;
    }
    public double computeCommission(){
        double commission =0;
       if(sales > 0.0)
       {
           commission=sales * comissionRate;
       }
        return commission;
    }
}
