#include "terminal.h"

#include<time.h>

EN_terminalError_t getTransactionDate(ST_terminalData_t * termData){
    EN_terminalError_t ret_state = TERMINAL_OK;
    time_t t;
     t = time(NULL);
     struct tm tm = *localtime(&t);
     termData->transactionDate[0] = '0'+((uint8_t)tm.tm_mday/10);
     termData->transactionDate[1] = '0'+((uint8_t)tm.tm_mday%10);
     termData->transactionDate[2] = '/';
     termData->transactionDate[3] = '0'+((uint8_t)(tm.tm_mon+1)/10);
     termData->transactionDate[4] = '0'+((uint8_t)(tm.tm_mon+1)%10);
     termData->transactionDate[5] = '/';
     uint32_t year_tmp = tm.tm_year+1902;
     termData->transactionDate[9] = '0'+((uint8_t)(year_tmp)%10);
     year_tmp /=10;
     termData->transactionDate[8] = '0'+((uint8_t)(year_tmp)%10);
     year_tmp /=10;
     termData->transactionDate[7] = '0'+((uint8_t)(year_tmp)%10);
     year_tmp /=10;
     termData->transactionDate[6] = '0'+((uint8_t)(year_tmp)%10);
     termData->transactionDate[10] = '\n';
     return ret_state;
}
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t * termData){
         EN_terminalError_t ret_state = EXPIRED_CARD;
         uint32_t card_exp_date = ((cardData->cardExpirationDate[3]-'0')*10+(cardData->cardExpirationDate[4]-'0'));


         uint32_t trans_date = ((termData->transactionDate[8]-'0')*10+(termData->transactionDate[9]-'0'));

         if(trans_date<card_exp_date){
            ret_state = TERMINAL_OK;

         }else if(trans_date == card_exp_date){
            card_exp_date = (cardData->cardExpirationDate[0]-'0')*10+(cardData->cardExpirationDate[1]-'0');
            trans_date = (termData->transactionDate[2]-'0')*10+(termData->transactionDate[3]-'0');
            if(trans_date< card_exp_date){
                ret_state = TERMINAL_OK;
            }
         }else{
         }
         return ret_state;
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t * termData){
    EN_terminalError_t ret_state = INVALID_AMOUNT;
    float amount;
    printf("Enter the amount : ");
    if (scanf("%f", &amount) == 0)
	{
		while (getchar() != '\n');
		return INVALID_AMOUNT;
	}
    if(amount >0){
        termData->transAmount = amount;
        ret_state = TERMINAL_OK;
    }

    return ret_state;

}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t * termData){
    EN_terminalError_t ret_state = EXCEED_MAX_AMOUNT;
    if(termData->transAmount<= termData->maxTransAmount){
        ret_state = TERMINAL_OK;
    }
    return ret_state;
}
EN_terminalError_t setMaxAmount(ST_terminalData_t * termData,float maxAmount){
        EN_terminalError_t ret_state = INVALID_MAX_AMOUNT;
        if(maxAmount > 0){
            termData->maxTransAmount = maxAmount;
            ret_state = TERMINAL_OK;
        }

       return ret_state;

}
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData){
    EN_terminalError_t ret_state = INVALID_CARD;
    int32_t sum=0, multipler = 1,multi_res =0, len=0;
    len=strlen((const char *)cardData->primaryAccountNumber);
    int32_t i = len;
    if (len < 16 || len >19)
		return INVALID_CARD;
    for( ;i >= 1;i--){
        if((16-i+1)%2 == 0){
            multipler = 2;
        }else{
            multipler = 1;

        }
        multi_res = multipler * (cardData->primaryAccountNumber[i-1] - '0');
        sum+= (multi_res/10) + (multi_res%10);

    }
    if(sum%10==0){
        ret_state = TERMINAL_OK;
    }
    return ret_state;

}
