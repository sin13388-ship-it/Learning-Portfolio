package ArrayExercise;

public class Java_Exam_Merge {
    static void main(String[] args) {
        /*
        * 3D 陣列
        *
        * */


        int[][][] address ={
            {
                {34500,21400,56700},
                {23200,41400},
                {36800,55600}
            },
            {
                    {43500,28700,74700,58900},
                    {43500,29800,35700}
            },
            {
                    {54300,41200,76500},
                    {33500,22400},
                    {36800,24200,67900,45200}
            },
        } ;


        int max =address[0][0][0];
        int min =address[0][0][0];

        int[] maxLocation =new int[]{0,0,0};
        int[] minLocation =new int[]{0,0,0};

        for(int neighborHood =0; neighborHood < address.length; neighborHood++ ){
            int houseHold =0;
            do
            {

                for(int person=0; person< address[neighborHood][houseHold].length; person++)
                {
                    if (address[neighborHood][houseHold][person] > max)
                    {
                        max=address[neighborHood][houseHold][person];
                        maxLocation[0]=neighborHood;
                        maxLocation[1]=houseHold;
                        maxLocation[2]=person;

                    }
                    if (address[neighborHood][houseHold][person] < min)
                    {
                        min=address[neighborHood][houseHold][person];
                        minLocation[0]=neighborHood;
                        minLocation[1]=houseHold;
                        minLocation[2]=person;
                    }
                }
                houseHold++;

            } while(houseHold < address[neighborHood].length);

            /*
            for(int  houseHold =0;  houseHold < address[neighborHood].length;houseHold++)
            {
                for(int person=0; person< address[neighborHood][houseHold].length; person++)
                {
                    if (address[neighborHood][houseHold][person] > max)
                    {
                        max=address[neighborHood][houseHold][person];
                        maxLocation[0]=neighborHood;
                        maxLocation[1]=houseHold;
                        maxLocation[2]=person;

                    }
                    if (address[neighborHood][houseHold][person] < min)
                    {
                        min=address[neighborHood][houseHold][person];
                        minLocation[0]=neighborHood;
                        minLocation[1]=houseHold;
                        minLocation[2]=person;
                    }
                }
            }
            */


        }
        System.out.printf("The max value is %d \n", max);
        System.out.printf("The Max location is %d Neighborhood, %d Household, %d person \n", maxLocation[0],maxLocation[1],maxLocation[2]);

        System.out.printf("The max value is %d \n", min);
        System.out.printf("The Max location is %d Neighborhood, %d Household, %d person \n", minLocation[0],minLocation[1],minLocation[2]);

    }
}
