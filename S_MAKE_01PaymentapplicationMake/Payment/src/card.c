#include"card.h"


/*this function ask the user to input his card holder name*/
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	uint8_t name[35]={0};
	uint8_t i,lenght;
	printf("Enter The Card Holder Name : ");
	gets((char *)name);                    /* i used gets() instead of fgets and put the string in the buffer called name 
								      and then check about the lenght
	                                  if not exceed the lenght of member of struct and not less than 20 it ,
									  it will put in the memeber called cardholdername */
	lenght = strlen((const char *)name);		
	
	if ( lenght< 20 || lenght >24)
		return WRONG_NAME;
	for (i = 0;i < lenght;i++)
	{
		
		if ((name[i] < 'A' && name[i] != ' ') || (name[i] > 'Z' && name[i] < 'a') || (name[i] > 'z' ))
			return WRONG_NAME;
	}
			strcpy((char *)cardData->cardHolderName, (const char *)name);
			
			return  CARD_OK;		
}

/*this function ask the user to input the expiration date of his card*/
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	uint8_t exp_date[10]={0};
	uint8_t i,lenght;	
	printf("Enter The Expirartion  Date : ");
	gets((char *)exp_date);                                /* i used gets() instead of fgets and put the string in the buffer called exp_date 
								                    and then check about the lenght
	                                                if not exceed the lenght of member of struct and not less than 5 it ,
									                 it will put in the memeber called cardExpirationDate */
	lenght = strlen((const char *)exp_date);
	if (lenght < 5 || lenght >5)
		return WRONG_EXP_DATE;
	for (i = 0;i < lenght;i++)
	{
		if ((exp_date[i] < '0' || exp_date[i] > '9') && i < 2)
			return WRONG_EXP_DATE;
		else if (exp_date[1] == '0' && exp_date[0] == '0')
			return WRONG_EXP_DATE;		
		else if (i == 2 && exp_date[2] != '/')
			return WRONG_EXP_DATE;
		else if (i >2 && exp_date[i] == '0')
			return WRONG_EXP_DATE;				
	}
	strcpy((char *)cardData->cardExpirationDate, (const char *)exp_date);
	return  CARD_OK;
}

/*this function ask the user to input the primary accpunt number of his card*/
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	uint8_t PAN[25]={0};
	uint8_t lenght, i;
	printf("Enter The Primary Account Number of The Card : ");
	gets((char *)PAN);
	lenght= strlen((const char *)PAN);
	if (lenght < 16 || lenght >19)
		return WRONG_PAN;
	for (i = 0;i < lenght;i++)
	{
		if (PAN[i] < '0' || PAN[i] >'9')
			return WRONG_PAN;
	}
	strcpy((char *)cardData->primaryAccountNumber, (const char *)PAN);
	return  CARD_OK;
}