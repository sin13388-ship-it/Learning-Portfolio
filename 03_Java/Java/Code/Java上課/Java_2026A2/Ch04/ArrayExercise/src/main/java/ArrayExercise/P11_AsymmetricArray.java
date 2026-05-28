package ArrayExercise;

public class P11_AsymmetricArray {
    /*Java 可以宣告不對稱的陣列*/

    static int[][] x; /*static Attributes; belongs class scope*/
    static int[][] y ={{44,55},{66,77,88}}; /*Declare & initialize*/

    static void main(String[] args) {

        x=new int[2][];

        x[0]=new int[]{1,2,3};
        x[1]=new int[]{1,2};

        displayInfo2(x);

        x[0]=new int[]{11,22,33};
        x[1]=new int[]{11,22};

        theIdiomaticWayForDisplayInfo(y);
    }

    static void displayInfo(){

        /*Static 可以直接取用，相當於Global 變數*/
        for(int e:x[0]){
            System.out.printf("%d\t",e);
        }
        System.out.println();

        for(int e:x[1]){
            System.out.printf("%d\t",e);
        }
        System.out.println();
    }

    static void displayInfo2(int [][] inputArray){
        /*For each 遍歷 2D - Array 的方法*/
        /*Hard coding*/
        for(int e:inputArray[0]){
            System.out.printf("%d\t",e);
        }
        System.out.println();

        for(int e:inputArray[1]){
            System.out.printf("%d\t",e);
        }
        System.out.println();
    }
    static void theIdiomaticWayForDisplayInfo(int [][] inputArray){
        for(int[] Layer1 : inputArray)
        {
            for(int e : Layer1){
                System.out.printf("%d\t",e);
            }
            System.out.println();
        }
    }
}
