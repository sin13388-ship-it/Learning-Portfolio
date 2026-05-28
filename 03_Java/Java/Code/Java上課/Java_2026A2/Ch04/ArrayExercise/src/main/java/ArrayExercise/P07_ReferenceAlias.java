package ArrayExercise;

public class P07_ReferenceAlias {
    static void main(String[] args) {

        /*myscore reference to score's memory*/
        /*1 line*/
        /*Local variable*/
        int[] score ={90,79,92};
        int[] myscore =score; /*like alias*/

        for(int e:score) System.out.printf("%d \t",e); System.out.println();
        for(int e:myscore) System.out.printf("%d \t",e); System.out.println();

        myscore[2]=101;
        for(int e:score) System.out.printf("%d \t",e); System.out.println();
        for(int e:myscore) System.out.printf("%d \t",e); System.out.println();
    }

}
