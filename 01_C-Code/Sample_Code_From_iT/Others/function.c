#include<stdio.h>
int power1(int x,int y);
int power2(int x,int y);
int power1(int x,int y)
{
	int i;
	int sum=1;
	for(i=1;i<=y;i++)
	{
		sum *= x;		
	}
	return sum;
}

int power2(int x,int y)
{
	if (y==0)
	{
		return 1;
	}
	y--;
	return x*power2(x,y);
}

int main(void)
{
	int x,y;
	printf("input x\n");
	scanf("%d",&x);
	printf("input y\n");
	scanf("%d",&y);

	printf("x=%d",x);
	printf("y=%d",y);
	printf("x=%d,y=%d,xy=%d",x,y,power1(x,y));
	printf("x=%d,y=%d,xy=%d",x,y,power2(x,y));

	
	return 0;
}
