package ArrayExercise;

import java.util.ArrayList;

public class PrimeNumbers {
    static void main(String[] args) {
        /*
        * 使用泛型 ArrayList<DataType>
        * 使用size 計算長度
        * int columnsInFirstRow = matrix.get(0).size(); for 2D array
        * */

        final int MAX =100;
        ArrayList<Integer> PrimeNumbers  =new ArrayList<Integer>();
        for (int i=2; i<= MAX; i++){
            int j=2;
            /* boolean isPrime =true; */
            do{
                if(i%j==0) {
                    /*isPrime = false; */
                    break;
                }
                j++;
            }while (j<i);

            /*if (isPrime) PrimeNumbers.add(i) */
            if (j==i) PrimeNumbers.add(i); /* 用flag 寫會更好一點 */
        }
        for(int e: PrimeNumbers) System.out.println(e);
        System.out.println("Total = " + PrimeNumbers.size());
    }
}
