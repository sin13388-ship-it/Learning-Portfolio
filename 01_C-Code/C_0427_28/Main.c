#include "C_Code_0422Example.h" //名字打錯，算了

void peri(double);
void area(double);
const double pi=3.14; /*const 只能設定一次*/
void EncodingAndDecoding();
/*
* 使用 const 後： 編譯器會將該資料放到 Flash（唯讀記憶體） 中，而不是占用珍貴的 RAM。
* 這對記憶體極度緊張的專案來說，往往是決定專案能否編譯通過的關鍵
*/

int main(){	
	//peri(1.0);
	//area(1.0);
	EncodingAndDecoding();
	getchar();
	return 0;
} 
void peri(double r)
{
	printf("The circumference = %.2f\n", 2*pi*r);	
}
void area(double r)
{
	printf("The circle area = %.2f\n", pi*r*r);	
}

void EncodingAndDecoding(){
	
	/*
	* 字元移位加密解密 
	*
	*/	
	char str[50];
	int i;	
	scanf("%s", &str);
	fflush(stdin);
	if (str[0] == '+'){
		int i=1;		
		for (i =1; i < strlen(str); i++){
			str[i]+=2;
			if(str[i]>'Z') {
				str[i]-=26; /*輪詢*/
			}
		}		
	}
	if (str[0] == '-'){
		int i=1;		
		for (i =1; i < strlen(str); i++){
			str[i]-=2;
			if(str[i]<'A') {
				str[i]+=26;
			}
		}		
	}
	printf("%s",str);	
}
