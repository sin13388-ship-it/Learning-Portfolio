#include <stdio.h>
float power(float,int);
float order(int);

int main(void)
{

int n=10;
double x=0.1;
int i;
double ans=0,temp=0;

//printf("%f\n",power(x,n));
//printf("%f\n",order(n));
//printf("sum(x^n/n!),n=0~%d x= %g\n",n,x);

for(i=0;i<=n;i++)
{
	temp=power(x,i)*order(i);
	ans=ans+temp;
}
printf("sum(x^n/n!),n=0~%d x= %g\n",n,x);
printf("ANS=%g",ans);


return 0;
}



float power(float x,int n) //計算x^n次方
{
int i;
float item;
if(n==0)
{
	item=1;
}
else
{
	item=x;
	for(i=2;i<=n;i++)
	{		
			item=x*item;		
	}
}
return item;
} 



float order(int n) //計算1/n!
{
int i;
int item1=1;
float item2=0;	//item2=1/n!

if(i==0)
{
	item1=1;
}
else
{
	for(i=1;i<=n;i++)
	{
		item1=item1*i;
	}
}
item2=(float)1/item1;

return item2;
}


