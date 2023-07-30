#ifndef TERMINAL_H
#define TERMINAL_H
#include "card.h"
#include "std_types.h"


/*
*
*
* -ST_terminalData_t datatye hold the transaction data
*   -Members-
* -1-  (float transAmount) amount of transaction
* -2-  (float maxtransAmount) max amount of transaction
* -3-  (uint8_t transactionDate[11]) array of char to hold the date
*
*/
typedef struct ST_terminalData_t{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];

}ST_terminalData_t;


/*
*
*
* -EN_terminalError_t datatype enum has all return states of interface functions
*   -Members-
*
* -1-TERMINAL_OK
* -2-WRONG_DATE
* -3-EXPIRED_CARD
* -4-INVALID_CARD
* -5-INVALID_AMOUNT
* -6-EXCEED_MAX_AMOUNT
* -7-INVALID_MAX_AMOUNT
*
*/
typedef enum EN_terminalError_t{
    TERMINAL_OK,
    WRONG_DATE,
    EXPIRED_CARD,
    INVALID_CARD,
    INVALID_AMOUNT,
    EXCEED_MAX_AMOUNT,
    INVALID_MAX_AMOUNT
}EN_terminalError_t;


/*
*   -Description-
*-this function get date form system
*
*   -Input Output parameters -
*-1-it holds the transaction data  (ST_terminalData_t * termData)
*
*   -Return-
*   -Return cases-
*-1- (WRONG_DATE) if get wrong date
*-2- (TERMINAL_OK) otherwise
*/
EN_terminalError_t getTransactionDate(ST_terminalData_t * termData);


/*
*   -Description-
*-this function get date form system
*
*   -Input parameters -
*-1-it holds the transaction data  (ST_terminalData_t * termData)
*-2-it holds the card data  (ST_cardData_t *cardData)
*
*   -Return-
*   -Return cases-
*-1- (EXPIRED_CARD) if EXPIRED CARD
*-2- (TERMINAL_OK) otherwise
*/
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t * termData);

/*
*   -Description-
*-this function get transaction amount
*
*   -Input Output parameters -
*-1-it holds the transaction data  (ST_terminalData_t * termData)
*
*
*   -Return-
*   -Return cases-
*-1- (INVALID_AMOUNT) if transaction amount valid like (values less or equal 0 / character)
*-2- (TERMINAL_OK) otherwise
*/
EN_terminalError_t getTransactionAmount(ST_terminalData_t * termData);


/*
*   -Description-
*-this function check if amount below max amount
*
*   -Input parameters -
*-1-it holds the transaction data  (ST_terminalData_t * termData)
*
*
*   -Return-
*   -Return cases-
*-1- (EXCEED_MAX_AMOUNT) if transaction amount greater than max mount
*-2- (TERMINAL_OK) otherwise
*/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t * termData);



/*
*   -Description-
*-this function set max amount in termData
*
*   -Input Output parameters -
*-1-it holds the transaction data  (ST_terminalData_t * termData)


*   -Input parameters -
*-1-it holds the max amount  (float maxAmount)
*
*
*   -Return-
*   -Return cases-
*-1- (INVALID_MAX_AMOUNT) if max mount not valid
*-2- (TERMINAL_OK) otherwise
*/
EN_terminalError_t setMaxAmount(ST_terminalData_t * termData,float maxAmount);


/*
*   -Description-
*-this function checks if card PAN valid or not
*
*   -Input parameters -
*-1-it holds the transaction data  (ST_terminalData_t * termData)
*
*
*
*   -Return-
*   -Return cases-
*-1- (INVALID_CARD) if card PAN not valid
*-2- (TERMINAL_OK) otherwise
*/
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData);

#endif // TERMINAL_H
