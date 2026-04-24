package ArrayExercise;

public class P02_Average_Temperature_ArrayApp {
    static void main(String[] args) {
        /*
        * Array declare
        * Calculate temperature's  average
        * Retrieve (For each 遍歷)
        * Set value
        * */

        double[] days =new double[7];
        days[0]=21.3;
        days[1]=22.3;
        days[2]=21.4;
        days[3]=22.5;
        days[4]=23.6;
        days[5]=21.7;
        days[6]=21.8;
        double avg;
        avg=0;
        /*For each*/
        for(double e:days){
            avg +=e;
        }
        /*Array .length*/
        avg =avg/days.length;
        System.out.printf("AVG Temperature of days : %.3f\n", avg);

        double[] days2={22.0,21.1,21.2,21.3,22.4,23.5,24.6};
        avg=0;
        for(double e:days2){
            avg += e;
        }
        avg =avg/days2.length;
        System.out.printf("AVG Temperature of days : %.3f\n", avg);

        System.out.printf("The 5th Temperature of days: %.3f\n", days[5]);

    }
}
