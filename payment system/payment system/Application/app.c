#include "app.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/sever.h"
#include<stdbool.h>




void appStart(void)
{
	ST_cardData_t  cardData;
	ST_terminalData_t termData;
	bool l1 = true;
	int x;
	bool loop = true;
	while (loop) {	
		while ( l1== true) {
			if ((x = getCardHolderName(&cardData)) == 0) {
				l1 = false;
			}
			else continue;
		}
		l1 = true;
		while (l1 == true) {
			if ((x = getCardExpiryDate(&cardData)) == 0) {
				l1 = false;
			}
			else continue;
		}
		l1 = true;
		while (l1 == true) {
			if ((x = getCardPAN(&cardData)) == 0) {
				l1 = false;
			}
			else continue;
		}
		getTransactionDate(&termData);
		if ((x = isCardExpired(cardData,termData)) == 0) {
		}
		else
		{ printf("Deslined Expired Card"); break;}
		l1 = true;
		while (l1 == true) {
			if ((x = getTransactionAmount(&termData.transAmount)) == 0) {
				l1 = false;
			}
			else continue;
		}
		l1 = true;
		while (l1 == true) {
			if ((x = setMaxAmount(&termData)) == 0) {
				l1 = false;
			}
			else continue;
		}
		if ((x = isBelowMaxAmount( &termData)) == 0) {
		}
		else
		{
			printf("Deslined Amount Exceeding limit"); break;
		}
		ST_transaction_t transData = {
			.cardHolderData=cardData,
			.terminalData=termData,
			.transState=refrence.state,
		};
		recieveTransactionData(&transData);
		loop = false;
		break;
	}
	}

int main() {
	appStart();
}
//  ahmed abdelaziz ali 
// 
//{ 10000,RUNNING,"1234567897894561" }, approved
//{ 80560,RUNNING,"9638527411478523" }, exceeds limit
//{ 10,RUNNING,"9876543211234567" },    insufficient fund
//{50000, BLOCKED, "1234567891234569"},  user blocked
                                        // invalid PAN

//{ 16040,RUNNING,"9512634872365198" },