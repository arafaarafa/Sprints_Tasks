
#include "testcase.h"

 ST_cardData_t card_data;
 ST_terminalData_t terminaldata;
 ST_transaction_t trans;
 ST_accountsDB_t accountrefrence;
/*******************************CARD_TEST_CASES************************/
void getCardHolderNameTest(void)
{
	uint8_t i=0;
	printf("tester name : basel nagy ahmed\nFunction Name: getCardHolderName\n");
	while (1)

{
		printf("test case %d :\n", i);

	if (getCardHolderName(&card_data) == CARD_OK)
	{

		printf("ok\n");
	}
	else printf("wrong name\n");

	i++;
}

}
void getCardExpiryDateTest(void)
{
	uint8_t i = 0;
	printf("tester name : basel nagy ahmed\nFunction Name: getCardExpiryDate \n");
	while (1)

	{
		printf("test case %d :\n", i);

		if (getCardExpiryDate(&card_data) == CARD_OK)
		{

			printf("ok\n");
		}
		else printf("wrong expiration date\n");

		i++;

	}

}

void getCardPANTest(void)
{
	uint8_t i = 0;
	printf("tester name : basel nagy ahmed\nFunction Name: getCardPAN  \n");
	while (1)

	{
		printf("test case %d :\n", i);

		if (getCardPAN(&card_data) == CARD_OK)
		{

			printf("ok\n");
		}
		else printf("wrong pan\n");

		i++;

	}
}

/*******************************CARD_TEST_CASES************************/


/*********************TERMIAL_TEST_CASES******************************/
void getTransactionDateTest(void)
{
	uint8_t i = 0;
	printf("tester name : Arafa Arafa\nFunction Name: getTransactionDate  \n");



		printf("test case %d :\n", i);

		if (getTransactionDate(&terminaldata)==TERMINAL_OK)
		{

			printf("ok\n");
		}
		else{

            printf("wrong date\n");
		}


		i++;


	printf("%s",terminaldata.transactionDate);
}


void isCardExpriedTest(void)
{
	uint8_t i = 0;
	printf("tester name : Arafa Arafa\nFunction Name: isCardExpriedTest  \n");
	while (1)

	{

		printf("test case %d :\n", i);
		if(getCardExpiryDate(&card_data)==CARD_OK)
		    if(getTransactionDate(&terminaldata)==TERMINAL_OK)
			{
				if (isCardExpired(&card_data, &terminaldata) == TERMINAL_OK)
				{

					printf("\nok\n");
				}
				else
                {

                    printf("card expired\n");

                }


			}
		i++;
	}
}
void getTransactionAmountTest(void)
{
	uint8_t i = 0;
	printf("tester name : Arafa Arafa\nFunction Name: getTransactionAmount\n");
	while (1)

	{
		printf("test case %d :\n", i);

		if (getTransactionAmount(&terminaldata) == TERMINAL_OK)
		{

			printf("ok\n");
		}
		else printf("wrong amount\n");

		i++;

	}
}
void setMaxAmountTest(void)
{
	uint8_t i = 0;
	float amount;
	printf("tester name : Arafa Arafa\nFunction Name: setMaxAmount\n");
	while (1)

	{
		printf("test case %d :\n", i);
		printf("Enter Maximum Allowed Amount : ");

		if (scanf("%f", &amount) == 0)
        {
            while (getchar() != '\n');
            printf("Wrong input for test case\n");
            continue;
        }
		if (setMaxAmount(&terminaldata,amount) == TERMINAL_OK)
		{

			printf("ok\n");
		}
		else printf("wrong amount\n");

		i++;

	}
}
void isBelowMaxAmountTest(void)
{
	uint8_t i = 0;
	float amount;
	printf("tester name : Arafa Arafa\nFunction Name: isBelowMaxAmount \n");
	while (1)

	{
		printf("test case %d :\n", i);

		getTransactionAmount(&terminaldata);
		printf("enter the maximam amount : ");
		scanf("%f", &amount);
		setMaxAmount(&terminaldata, amount);
		if(isBelowMaxAmount(&terminaldata) == TERMINAL_OK)
				printf("ok\n");
		else printf("exceed maximam amount\n");

		i++;


	}
}

void isValidCardPANTest(void)
{   uint8_t PAN_tmp[25]={0};
	uint8_t i = 0;
	printf("tester name : Arafa Arafa\nFunction Name: isValidCardPAN\n");
	while (1)

	{
		printf("test case %d :\n", i);
		getCardPAN(&card_data);
		if (isValidCardPAN(&card_data) == TERMINAL_OK)
		{

			printf("luhn number valid\n");
		}
		else
        {printf("invalid card\n");}

		i++;
    strcpy(( char *)card_data.primaryAccountNumber,(const char *) PAN_tmp);

	}
}
/*********************TERMIAL_TEST_CASES******************************/

/*********************SERVER_TEST_CASES******************************/
void isValidAccountTest(void)
{
	uint8_t i = 0;

	printf("tester name : basel nagy ahmed\nFunction Name: isValidAccount  \n");
	while (1)

	{
		printf("test case %d :\n", i);

		if (getCardPAN(&card_data) == CARD_OK)

		{

			if (isValidAccount(&card_data,&accountrefrence) == SERVER_OK)
			{
				printf("PAN found\n");




			}
			else printf("Account not found\n");
		}





		i++;

	}
}
void isBlockedAccountTest(void)
{
	uint8_t i = 0;

	printf("tester name : basel nagy ahmed\nFunction Name: isBlockedAccount function  \n");
	while (1)

	{
		printf("test case %d :\n", i);
		if (getCardPAN(&card_data) == CARD_OK){
			if (isValidAccount(&card_data, &accountrefrence) == SERVER_OK){
				if (isBlockedAccount( &accountrefrence) == SERVER_OK)
				{
					printf("runnung account\n");
				}
				else {printf("blocked account\n");
				}

			}else{

			}
		}else{

		}	
		i++;
     }
}
void isAmountAvailableTest(void)
{
	uint8_t i = 0;
	printf("tester name : basel nagy ahmed\nFunction Name: isAmountAvailable\n");
	while (1)

	{
		printf("test case %d :\n", i);
		getCardPAN(&card_data);
		isValidAccount(&card_data, &accountrefrence);

		if (getTransactionAmount(&terminaldata) == TERMINAL_OK)
		{

			if (isAmountAvailable(&terminaldata, &accountrefrence) == SERVER_OK)
				printf("balance ok\n");
			else printf("no balance\n");
		}
		else printf("wrong amount\n");

		i++;

	}
}
void saveTransactionTest(void)
{
	uint8_t i = 0,st;
	printf("tester name : basel nagy ahmed\nFunction Name:saveTransaction \n");

	while (1) {
		printf("test case %d :\n", i);
		getCardHolderName(&card_data);
		getCardExpiryDate(&card_data);
		getCardPAN(&card_data);
		getTransactionDate(&terminaldata);
		getTransactionAmount(&terminaldata);
		setMaxAmount(&terminaldata, 20000);
		recieveTransactionData(&trans);
		if (saveTransaction(&trans) == SERVER_OK)
		{printf("name:%s\n", trans.cardHolderData.cardHolderName);
		printf("card expiration date: %s\n", trans.cardHolderData.cardExpirationDate);
		printf("primary account number: %s\n", trans.cardHolderData.primaryAccountNumber);


		printf("currenr date: %s\n", trans.terminalData.transactionDate);
		printf("transamount: %f\n", trans.terminalData.transAmount);
		printf("maxamount of terminal: %f\n", trans.terminalData.maxTransAmount);
		printf("transaction sequence :%d\n", trans.transactionSequenceNumber);
		st = trans.transState;
		if (st == APPROVED)
			printf("state:approved \n");
		else if (st == DECLINED_INSUFFECIENT_FUND)
			printf("state:DECLINED_INSUFFECIENT_FUND \n");
		else if (st == DECLINED_STOLEN_CARD)
			printf("state: blocked \n");
		else if (st == FRAUD_CARD)
			printf("state: FRAUD CARD \n");
		else
			printf("state: INTERNAL_SERVER_ERROR \n");
		}
		else printf("exceed maximam transactions\n");
		while(getchar() != '\n');
		i++;
	}
}
void listSavedTransactionsTest(void)
{
	uint8_t i = 0;

	printf("tester name : basel nagy ahmed\nFunction Name: listsavetransactions \n");
	while (1)

	{
		printf("test case %d :\n", i);
		getCardHolderName(&card_data);
		getCardExpiryDate(&card_data);
		getCardPAN(&card_data);
		getTransactionDate(&terminaldata);
		getTransactionAmount(&terminaldata);
		setMaxAmount(&terminaldata, 20000);
		recieveTransactionData(&trans);	recieveTransactionData(&trans);
		if(saveTransaction(&trans)==SERVER_OK);
		listSavedTransactions();
		while(getchar() != '\n');
		i++;
	}
}
/*********************SERVER_TEST_CASES******************************/
