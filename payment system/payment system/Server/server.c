#include "sever.h"


ST_accountsDB_t refrence;
ST_transaction_t transactionDB[255] = {0};    // trans database
ST_accountsDB_t accountsDB[255] = {
	{50000,BLOCKED,"1234567891234569"},
	{10000,RUNNING,"1234567897894561"},
	{10,RUNNING,"9876543211234567"},
	{80560,RUNNING,"9638527411478523"},
	{16040,RUNNING,"9512634872365198"},
};                                             // acounts database


EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence) {
	int i;
	for (i = 0; i < 255; i++) {
		if (strcmp(cardData->primaryAccountNumber, accountsDB[i].primaryAccountNumber) != 0) {
			if (i == 254) return ACCOUNT_NOT_FOUND;
		}
		else if(strcmp(cardData->primaryAccountNumber, accountsDB[i].primaryAccountNumber) == 0) {
			*accountRefrence = accountsDB[i];
			return SERVER_OK;
	}
	}
}
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData) {
	if (termData->transAmount > refrence.balance)return LOW_BALANCE;
	else return SERVER_OK;
}
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {
	if (refrence.state == BLOCKED) return BLOCKED_ACCOUNT;
	else return SERVER_OK;
}
EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	int i;
	for (i = 0;i < 255; i++) {
		if (transactionDB[i].transactionSequenceNumber == 0) {
			transactionDB[i].transactionSequenceNumber = (i + 1) * 5;
			transactionDB[i] = *transData;
			return SERVER_OK;
		}
		else if (i == 254) return SAVING_FAILED;
	}
}
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData) {
	printf("Enter transection sequence number: ");
	fgets(transactionSequenceNumber,20,stdin);
	int i;
	for (i = 0; i < 255; i++) {
		if (strcmp(transactionSequenceNumber , transactionDB[i].transactionSequenceNumber)==0) {
			*transData= transactionDB[i];
			return SERVER_OK;
		}
		else if (i == 254) return TRANSACTION_NOT_FOUND;
	}
}
EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	int x;
	if((x = isValidAccount(&transData->cardHolderData, &refrence)) == 0) {
		if ((x = isAmountAvailable(&transData->terminalData)) == 0) {
			if ((x = isBlockedAccount(&refrence)) == 0) {
				if((x= saveTransaction(transData))==0){ 
					printf("Approved\n");
					return APPROVED; 
				}
				else {
					printf("save failed");
					return INTERNAL_SERVER_ERROR;
				}
			}
			else {
				printf("user Blocked");
				return DECLINED_STOLEN_CARD;
			}
		}
		else {
			printf("DECLINED_INSUFFECIENT_FUND");
			return DECLINED_INSUFFECIENT_FUND;
		}
	}
	else {
		printf("Declined invalid card");
		return FRAUD_CARD;
	}
	

}




