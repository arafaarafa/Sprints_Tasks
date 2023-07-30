#ifndef _SERVER_H_
#define _SERVER_H_
#include"terminal.h"
#include"card.h"


/*
*
*
* -EN_transState_t datatype enum has all return states of interface functions
*   -Members-
*
* -1-APPROVED
* -2-DECLINED_INSUFFECIENT_FUND  ****not enough amount****
* -3-DECLINED_STOLEN_CARD ****the account blocked****
* -4-FRAUD_CARD  ****account not exite****
* -5-INTERNAL_SERVER_ERROR ****error in server****
*
*/
typedef enum EN_transState_t
{
    APPROVED,
    DECLINED_INSUFFECIENT_FUND,
    DECLINED_STOLEN_CARD,
    FRAUD_CARD,
    INTERNAL_SERVER_ERROR
}EN_transState_t;


/*
*
*
* -ST_transaction_t datatye hold the transaction data
*   -Members-
* -1-  (ST_cardData_t cardHolderData)  card information
* -2-  (ST_terminalData_t terminalData) terminal data
* -3-  (EN_transState_t transState) transaction state
* -4-  (uint32_t transactionSequenceNumber) ID of transaction
*/

typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    uint32_t transactionSequenceNumber;
}ST_transaction_t;




/*
*
*
* -EN_serverError_t datatype enum has all return states of interface functions
*   -Members-
*
* -1-SERVER_OK
* -2-SAVING_FAILED  ****could not save the transaction****
* -3-TRANSACTION_NOT_FOUND
* -4-ACCOUNT_NOT_FOUND  ****account not exite****
* -5-LOW_BALANCE ****not enough amount****
* -6-BLOCKED_ACCOUNT ****the account blocked****
*
*/
typedef enum EN_serverError_t
{
    SERVER_OK,
    SAVING_FAILED,
    TRANSACTION_NOT_FOUND,
    ACCOUNT_NOT_FOUND,
    LOW_BALANCE,
    BLOCKED_ACCOUNT
}EN_serverError_t;



/*
*
*
* -EN_accountState_t datatype enum has all return states of interface functions
*   -Members-
*
* -1-RUNNING
* -2-BLOCKED
*
*/
typedef enum EN_accountState_t
{
    RUNNING,
    BLOCKED
}EN_accountState_t;



/*
*
*
* -ST_transaction_t datatye hold the account object data
*   -Members-
* -1-  (float balance)  balance of account
* -2-  (EN_accountState_t state) account state
* -3-  (uint8_t primaryAccountNumber[20]) card PAN
*/
typedef struct ST_accountsDB_t
{
    float balance;
    EN_accountState_t state;
    uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;



/*
*   -Description-
*-this function check the validity of transaction data
*
*   -Input Output parameters -
*-1-it holds the card data, terminal data, transaction state and transaction sequence number  (ST_transaction_t* transData)
*
*   -Return-
*
*   -Return cases-
*-1- (FRAUD_CARD) not valid account
*-2- (DECLINED_STOLEN_CARD) account blocked
*-3- (DECLINED_INSUFFECIENT_FUND) required amount greater than exit account amount
*-4- (APPROVED) otherwise
*/
EN_transState_t recieveTransactionData(ST_transaction_t* transData);

/*
*   -Description-
*-this function check the validity of account
*
*   -Input parameters -
*-1-it holds the balance, account state and PAN  (ST_accountsDB_t* accountRefrence)
*-2-it holds the card data  (ST_cardData_t* cardData)
*
*   -Return-
*   EN_serverError_t datatype
*   -Return cases-
*-1- (ACCOUNT_NOT_FOUND) account not found in database
*-2- (SERVER_OK) otherwise
*/
EN_serverError_t isValidAccount(ST_cardData_t* cardData,  ST_accountsDB_t* accountRefrence);



/*
*   -Description-
*-this function check the validity of account state
*
*   -Input parameters -
*-1-it holds the balance, account state and PAN  (ST_accountsDB_t* accountRefrence)
*
*   -Return-
*   EN_serverError_t datatype
*   -Return cases-
*-1- (BLOCKED_ACCOUNT) account blocked
*-2- (SERVER_OK) otherwise
*/
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence);

/*
*   -Description-
*-this function check the account amount
*
*   -Input parameters -
*-1-it holds the balance, account state and PAN  (ST_accountsDB_t* accountRefrence)
*-2-it holds the terminal data  (ST_terminalData_t* termData)
*
*   -Return-
*   EN_serverError_t datatype
*   -Return cases-
*-1- (LOW_BALANCE) account balance below the required amount
*-2- (SERVER_OK) otherwise
*/
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence);

/*
*   -Description-
*-this function save the transaction data
*
*   -Input parameters -
*-1-it holds the card data, terminal data, transaction state and transaction sequence number  (ST_transaction_t* transData)
*
*   -Return-
*   EN_serverError_t datatype
*   -Return cases-
*-1- (SAVING_FAILED) saving transaction failed
*-2- (SERVER_OK) otherwise
*/
EN_serverError_t saveTransaction(ST_transaction_t* transData);


/*
*   -Description-
*-this function list all saved transaction
*
*
*/
void listSavedTransactions(void);


#endif
