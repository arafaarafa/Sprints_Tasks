#include <conio.h>
#include "application.h"
#include "server.h"
#include "card.h"

extern ST_cardData_t card_data;
extern ST_terminalData_t terminaldata;
extern ST_accountsDB_t accountrefrence;
extern ST_transaction_t trans;

void appStart(void)
{
	uint8_t ch;
	while (getCardHolderName(&card_data) != CARD_OK)
		printf("wrong formatted or exceed maximum limit\n");
	while (getCardExpiryDate(&card_data) != CARD_OK)
		printf("wrong formatted it must be MM/YY ex: 01/23\n");
	while (getCardPAN(&card_data) != CARD_OK)
	printf("please write correct formatted of PAN \n");
	while (1)
	{
		getTransactionDate(&terminaldata);                //read current date from windows and put it in the terminaldata
		if (isCardExpired(&card_data, &terminaldata) == EXPIRED_CARD)
		{
			printf("Declined expired card "); break;
		}
		else
		{
			while (setMaxAmount(&terminaldata, 20000) != TERMINAL_OK)    //set max.amount is 20000
				printf("enter right maximam amount\n");
			loop1:
			while (getTransactionAmount(&terminaldata) != TERMINAL_OK)
				printf("enter right transaction amount \n");
			if (isBelowMaxAmount(&terminaldata) == EXCEED_MAX_AMOUNT)
			{
				printf("Declined Amount Exceeding Limit ");
				break;
			}
			else {
				EN_transState_t cases=recieveTransactionData(&trans);

				    if (cases== FRAUD_CARD)
				        {
						printf("Declined Invalid Account \n");
						saveTransaction(&trans);

						break;
					    }
					else if (cases == DECLINED_INSUFFECIENT_FUND)
					     {
						printf("Declined Insuffecient Funds\n");
						if (saveTransaction(&trans) == SERVER_OK)
						{
							printf("saved transaction\n");
							listSavedTransactions();
							break;
						}
						else { printf("exceed transaction limit\n");break; }

					     }
					else if (cases == DECLINED_STOLEN_CARD)
					{
						printf("blocked\n");
						if (saveTransaction(&trans) == SERVER_OK)
						{
							printf("saved transaction\n");
							listSavedTransactions();
							break;
						}
						else { printf("exceed transaction limit\n");break; }
					}
					else
					{

						printf("\nAPPROVED\n");
						if (saveTransaction(&trans) == SERVER_OK)
						{
							printf("saved transaction\n");


						}
						else { printf("exceed transaction limit\n");}
						printf("\n1-print the list save transactions\n2-make another transaction\n");
						ch = getch();
						switch (ch)
						{
						case '1':
						     listSavedTransactions();
						     break;
						case '2':
						    goto loop1;
                            break;
						}
					}
			    }
		}
    }

}
