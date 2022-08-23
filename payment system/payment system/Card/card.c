#include "card.h"




EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	printf("Enter card holder name: ");
	if (!scanf_s("%[^\n]%*c", cardData->cardHolderName, 25)||strlen(cardData->cardHolderName)>24||strlen(cardData->cardHolderName)<20) {
		return WRONG_NAME;
	}
	else { return OK; }
}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	printf("Enter card expiry date: ");
	if (!scanf_s("%s", cardData->cardExpirationDate, 6) || strlen(cardData->cardExpirationDate) >5 || strlen(cardData->cardExpirationDate) < 5) {
		return WRONG_EXP_DATE;
	}
	else if (cardData->cardExpirationDate[0] >= '2' || (cardData->cardExpirationDate[0] >= '1' && cardData->cardExpirationDate[1] > '2') || (cardData->cardExpirationDate[0] <= '0' && cardData->cardExpirationDate[1] <= '0') || cardData->cardExpirationDate[0] < '0' || cardData->cardExpirationDate[1] < '0') {
		return WRONG_EXP_DATE;
	}
	else if ((cardData->cardExpirationDate[3] < '0' || cardData->cardExpirationDate[4] < 0) || cardData->cardExpirationDate[4] > '9' || cardData->cardExpirationDate[3] > '9') {
		return WRONG_EXP_DATE;
	}
	else if (cardData->cardExpirationDate[2] != '/') {
		return	WRONG_EXP_DATE;
	}
	else {
		return OK;
	}
}
EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	printf("Enter card PAN: ");

	if (!scanf_s("%s", cardData->primaryAccountNumber, 20) || strlen(cardData->primaryAccountNumber) > 19 || strlen(cardData->primaryAccountNumber) < 16) {
		return WRONG_PAN;
	}
	else {
		return OK;
	}

}

