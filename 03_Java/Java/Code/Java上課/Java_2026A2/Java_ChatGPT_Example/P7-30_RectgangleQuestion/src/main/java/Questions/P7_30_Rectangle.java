package Questions;

public class P7_30_Rectangle {

}
class Rectangle2{
    private  int width;
    private  int length;

    Rectangle2(int width, int length){
        this.width=width;
        this.length=length;
    }
    public int area(){
        return width * length;
    }
    public int getWidth(){
        return  width;
    }

    static void main(String[] args) {
        int areaNum;
        Rectangle2 rect  =new Rectangle2(20,40);
        areaNum=rect.area();
        System.out.printf("Width =%d Length=%d\n", rect.width, rect.length);
        System.out.printf("Area is correct %b\n", areaNum==800);
    }
}

