#include "C_Code_0512Example.h"

typedef float temperature;
void exercise5_typedefine();
void exercise6_union();
void exercise7_payment_select();

union paid{
	char creditCard[21];
	char bankAccount[16];
	int iCash;
};

union payment{
	char creditCard[17];
	int iCash;
};



void exercise5_typedefine(){	
	temperature fahrenheit, celisus;	
	printf("Please input a temperatue in fahrenheit \n");
	scanf("%f", &fahrenheit);
	fflush(stdin);
	celisus=(fahrenheit-32)*5/9;
	printf("The celisus= %f", celisus);
}

void exercise6_union(){
	
	union paid money;
	int i;
	printf("Please enter a bank account number: ");
	scanf("%s", &money.bankAccount);
	fflush(stdin);
	printf("Bank: %s\n", money.bankAccount);
	for(i=0; i<sizeof(money);i++) printf("%2c",money.creditCard[i]);
	printf("\n");
	printf("Please enter a creditCard number: ");
	scanf("%s", &money.creditCard);
	fflush(stdin);	
	printf("creditCard : %s\n", money.creditCard);
	for(i=0; i<sizeof(money);i++) printf("%2c",money.creditCard[i]);
	printf("\n");
	
	printf("Please enter a cash amount: ");
	scanf("%d", &money.iCash);
	fflush(stdin);
	printf("Cash : %4d\n", money.iCash);
	for(i=0; i<sizeof(money);i++) printf("%2c",money.creditCard[i]);
	printf("\n");	
	
	printf("creditCard : %s\n", money.creditCard);	
	for(i=0; i<sizeof(money);i++) printf("%2c",money.creditCard[i]);
	printf("\n");
	
}

void exercise7_payment_select(){	
	int amt =1500;
	int opt;
	
	printf("Please select a payment method (0: Credit Card, 1: Cash)\n");
	scanf("%d",&opt);
	fflush(stdin);	
	union payment myPayment;	
	if(opt==0){
		printf("Please input your credit card numbers [16 char.]\n");
		fgets(myPayment.creditCard,17,stdin);
		fflush(stdin);
		if(strlen(myPayment.creditCard) !=16){
			printf("The credit card no. format is invalid, please re-operate\n");
			opt=0;
		}
		else
		{
			printf("Payment completed!\n");
		}
	}
	else if (opt==1){
		printf("Please input the amount of cash\n");
		scanf("%d",&myPayment.iCash);
		fflush(stdin);
		
		if (myPayment.iCash > amt){
			printf("Insufficient amount! Full payment required\n");
			opt=0;
		}
		else
		{
			printf("Payment completed!\n");
		}
	}

}



