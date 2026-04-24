package ArrayExercise;

public class P08_Ref_to_Another_Object {

    static void main(String[] args) {
        /*Change reference type*/

        int[] x={4,5,8}; //Reference type

        for(int e: x) System.out.printf("%d \t", e);
        System.out.println();

        int[] y =x;
        x=new int[] {7,8};
        for(int e: x) System.out.printf("%d \t", e);
        System.out.println();
        for(int e: y) System.out.printf("%d \t", e);
        System.out.println();


    }



}
