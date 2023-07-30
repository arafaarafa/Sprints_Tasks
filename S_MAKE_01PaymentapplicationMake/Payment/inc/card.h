#ifndef _CARD_H_
#define _CARD_H_
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include "std_types.h"
/*
*
*
* -ST_cardData_t datatye hold the transaction data
*   -Members-
* -1-  (uint8_t cardHolderName[25])  card holder name
* -2-  (uint8_t primaryAccountNumber[20]) holds PAN of card
* -3-  (uint8_t cardExpirationDate[6]) holds EXP date
*
*/
typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;


/*
*
*
* -EN_cardError_t datatype enum has all return states of interface functions
*   -Members-
*
* -1-CARD_OK
* -2-WRONG_NAME  ****if get wrong name format****
* -3-WRONG_EXP_DATE ****if get wrong date format****
* -4-WRONG_PAN  ****if get wrong PAN format****
*
*/
typedef enum EN_cardError_t
{
    CARD_OK,
    WRONG_NAME,
    WRONG_EXP_DATE,
    WRONG_PAN
}EN_cardError_t;



/*
*   -Description-
*-this function get card holder name
*
*   -Input Output parameters -
*-1-it holds the card data  (ST_cardData_t* cardData)
*
*   -Return-
*
*   -Return cases-
*-1- (WRONG_NAME) if get wrong name format
*-2- (CARD_OK) otherwise
*/
EN_cardError_t getCardHolderName(ST_cardData_t* cardData);

/*
*   -Description-
*-this function get Card Expiry Date
*
*   -Input Output parameters -
*-1-it holds the card data  (ST_cardData_t* cardData)
*
*   -Return-
*
*   -Return cases-
*-1- (WRONG_EXP_DATE) if get wrong date format
*-2- (CARD_OK) otherwise
*/
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);


/*
*   -Description-
*-this function get Card PAN
*
*   -Input Output parameters -
*-1-it holds the card data  (ST_cardData_t* cardData)
*
*   -Return-
*
*   -Return cases-
*-1- (WRONG_PAN) if get wrong PAN format
*-2- (CARD_OK) otherwise
*/
EN_cardError_t getCardPAN(ST_cardData_t* cardData);
#endif 
