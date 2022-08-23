#include "terminal.h"


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	time_t seconds = time(NULL);
	struct tm time;

	localtime_s(&time, &seconds);
	sprintf_s(termData->transactionDate, 11, "%d/0%d/%d", time.tm_mday, time.tm_mon + 1, time.tm_year + 1900);
}
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData) {
	// exp -> 05/22     tran-> 06/10/2022
	if ((cardData.cardExpirationDate[3] == termData.transactionDate[8]) && (cardData.cardExpirationDate[4] == termData.transactionDate[9])) {
		if ((cardData.cardExpirationDate[0] == '0' && termData.transactionDate[3] == '0') && (cardData.cardExpirationDate[1] < termData.transactionDate[4])) {

			return  EXPIRED_CARD;
		}
		else if ((cardData.cardExpirationDate[0] == '0' && termData.transactionDate[3] == '0') && (cardData.cardExpirationDate[1] > termData.transactionDate[4])) {
			return  oK;
		}
		else if ((cardData.cardExpirationDate[0] == '0' && termData.transactionDate[3] == '1')) {
			return  EXPIRED_CARD;
		}
		else if ((cardData.cardExpirationDate[0] == '1' && termData.transactionDate[3] == '0')) {
			return oK;
		}
		else if ((cardData.cardExpirationDate[0] == '1' && termData.transactionDate[3] == '1')) {
			if ((cardData.cardExpirationDate[1] < termData.transactionDate[4])) {
				return  EXPIRED_CARD;
			}
			else
			{
				return oK;
			}
		}
	}
	else if (cardData.cardExpirationDate[3] < termData.transactionDate[8]) {
		return EXPIRED_CARD;
	}
	else if (cardData.cardExpirationDate[3] == termData.transactionDate[8]) {
		if (cardData.cardExpirationDate[4] > termData.transactionDate[9]) {
			return oK;
		}
		else {
			return EXPIRED_CARD;
		}
	}
	else { return oK; }


}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	printf("Enter the transection amount: ");
	scanf_s("%f", &termData->transAmount);
	if (termData->transAmount <= 0) {
		return INVALID_AMOUNT;
	}
	else {
		return oK;
	}
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
	printf("Enter the max amount: ");
	scanf_s("%f", &termData->maxTransAmount);
	if (termData->maxTransAmount <= 0) {
		return INVALID_MAX_AMOUNT;
	}
	else {
		return oK;
	}
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	if (termData->transAmount > termData->maxTransAmount) {
		return INVALID_MAX_AMOUNT;
	}
	else {
		return oK;
	}

}



