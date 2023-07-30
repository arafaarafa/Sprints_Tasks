#ifndef TEST_CASES_H
#define TEST_CASES_H

#include "card.h"
#include "server.h"
#include "terminal.h"

/**************************CARD_TEST_CASES*****************************/

void getCardHolderNameTest(void);
void getCardExpiryDateTest(void);
void getCardPANTest(void);


/*******************************CARD_TEST_CASES************************/



/*********************TERMIAL_TEST_CASES******************************/
void getTransactionDateTest(void);
void isCardExpriedTest(void);
void getTransactionAmountTest(void);
void setMaxAmountTest(void);
void isBelowMaxAmountTest(void);
void isValidCardPANTest(void);
/*********************TERMIAL_TEST_CASES******************************/

/*********************SERVER_TEST_CASES******************************/
void isValidAccountTest(void);
void isBlockedAccountTest(void);
void isAmountAvailableTest(void);
void saveTransactionTest(void);
void listSavedTransactionsTest(void);
/*********************SERVER_TEST_CASES******************************/


#endif // TEST_CASES_H
