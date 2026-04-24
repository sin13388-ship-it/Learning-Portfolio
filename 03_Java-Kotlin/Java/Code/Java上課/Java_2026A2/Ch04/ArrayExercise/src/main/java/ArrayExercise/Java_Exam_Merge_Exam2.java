package ArrayExercise;

public class Java_Exam_Merge_Exam2 {
    static void main(String[] args) {

        int n =1;
        long sum=0;
        /*
        * 找出pattern
        *
        * */

        do
        {
            int x=n+1;
            int y=n+2;
            int z=n+3;
            sum=sum+((n*(n+2)*(n+4)*(n+6)) - (x*(x+2)*(x+4)*(x+6))) ;
            sum=sum+(-(y*(y+2)*(y+4)*(y+6)) + (z*(z+2)*(z+4)*(z+6))) ;
            n+=4;
        } while (n<100);

        System.out.println(sum);

        long sum1 = 0;
        int n1 = 1;

        // We process in blocks of 4. Since the total terms are 100,
        // the last block starts at n = 97 (97, 98, 99, 100).
        do {
            sum1 += calculateTerm(n1);     // + Term 1
            sum1 -= calculateTerm(n1 + 1); // - Term 2
            sum1 -= calculateTerm(n1 + 2); // - Term 3
            sum1 += calculateTerm(n1 + 3); // + Term 4

            n1 += 4;
        } while (n1 < 100); // Stop once n reaches 101

        System.out.println("The total sum is: " + sum1);
    }

    // Helper method to calculate n * (n+2) * (n+4) * (n+6)
    private static long calculateTerm(long i) {
        return i * (i + 2) * (i + 4) * ( i + 6);
        // Note: Using long here prevents integer overflow during multiplication
    }
}
