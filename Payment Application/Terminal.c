#include "Terminal.h"

float maxAmount = 15000.0 ;

/*********************************************************************************************************************************************************
This function will ask for the transaction date and store it in terminal data.
*********************************************************************************************************************************************************/

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	int day, month, year;
	scanf("%s", termData->transactionDate);

	if ((strlen(termData->transactionDate) < 10) || (termData->transactionDate == NULL))
	{
		return WRONG_DATE;
	}
	if (sscanf(termData->transactionDate, "%2d/%2d/%4d", &day, &month, &year) != 3) {
		return WRONG_DATE;
	}
	if (day < 1 || day > 31 || month < 1 || month > 12 || year < 0) {
		return WRONG_DATE;
	}

	return TERMINAL_OK;
}

/*********************************************************************************************************************************************************
This function compares the card expiry date with the transaction date.
*********************************************************************************************************************************************************/

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) {
	int monthExp, yearExp;
	int monthTra, yearTra;
	int ignore1;

	sscanf(cardData->cardExpirationDate, "%2d/%2d", &monthExp, &yearExp);
	sscanf(termData->transactionDate, "%2d/%2d/%4d", &ignore1, &monthTra, &yearTra);
	if ((yearTra-2000) > yearExp) {
		return EXPIRED_CARD;
	}
	else if ((yearTra-2000) == yearExp && monthTra > monthExp) {
		return EXPIRED_CARD;
	}
	return TERMINAL_OK;
}

/*********************************************************************************************************************************************************
This function asks for the transaction amount and saves it into terminal data.
*********************************************************************************************************************************************************/

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	scanf("%f", &termData->transAmount);

	if (termData->transAmount <= 0.0) {
		return INVALID_AMOUNT;
	}

	return TERMINAL_OK;
}

/*********************************************************************************************************************************************************
This function compares the transaction amount with the terminal max allowed amount.
*********************************************************************************************************************************************************/

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	if (termData->transAmount > maxAmount) {
		return EXCEED_MAX_AMOUNT;
	}
	return TERMINAL_OK;
}

/*********************************************************************************************************************************************************
This function takes the maximum allowed amount and stores it into terminal data.
*********************************************************************************************************************************************************/

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount) {

	if (maxAmount <= 0) {
		return INVALID_MAX_AMOUNT;
	}
	termData->maxTransAmount = maxAmount;
	return TERMINAL_OK;
}




/*********************************************************************************************************************************************************
																			TESTS
*********************************************************************************************************************************************************/

void getTransactionDateTest(void) {
	ST_terminalData_t TestData;
	EN_terminalError_t state = WRONG_DATE;

	printf("Please enter the transaction date DD/MM/YYYY \n");
	while (state == WRONG_DATE) {
		state = getTransactionDate(&TestData);
		if (state == TERMINAL_OK) {
			break;
		}
		printf("The Date you entered is WRONG!\n");
	}
	system("cls");
}

/*********************************************************************************************************************************************************/

void isCardExpriedTest(void) {


	ST_terminalData_t termTest;
	ST_cardData_t CardTest;
	EN_terminalError_t state ;
	strcpy(CardTest.cardExpirationDate, "10/25");
	strcpy(termTest.transactionDate, "10/11/2025");
	printf("Please wait while checking card expiration... \n");
		state = isCardExpired(&CardTest,&termTest);
		if (state == EXPIRED_CARD) {
		printf("\nyour card is EXPIRED!\n");
		}
		else if (state == TERMINAL_OK) {
		printf("\nyour card is VALID!\n");
		}
}

/*********************************************************************************************************************************************************/

void getTransactionAmountTest (void) {

	ST_terminalData_t TestData;
	EN_terminalError_t state = INVALID_AMOUNT;
	printf("Please enter the transaction amount\n");
	while (state == INVALID_AMOUNT) {
		state = getTransactionAmount(&TestData);
		if (state == INVALID_AMOUNT) {
		printf("The amount you entered is INVALID!\n");
		}
	}
	system("cls");
}

/*********************************************************************************************************************************************************/

void isBelowMaxAmountTest (void){

	ST_terminalData_t TestData;
	TestData.transAmount = 16000;
	EN_terminalError_t state = EXCEED_MAX_AMOUNT;
	while (state == EXCEED_MAX_AMOUNT) {
		state = isBelowMaxAmount(&TestData);
		if (state == EXCEED_MAX_AMOUNT) {
			printf("The amount you entered exceeds the maximum amount\n");
			getTransactionAmountTest();
		}

	}
	system("cls");
	printf("\nSuccessfull transaction! \n");
}

/*********************************************************************************************************************************************************/

void setMaxAmountTest(void) {

	ST_terminalData_t TestData;
	EN_terminalError_t state = INVALID_MAX_AMOUNT;
	while (state == INVALID_MAX_AMOUNT) {
		scanf("%f", &maxAmount);
		state = setMaxAmount(&TestData, maxAmount);
		if (state == INVALID_MAX_AMOUNT) {
			printf("INVALID Maximum amount!\n");

		}
	}
	system("cls");
	printf("\nMaximum transaction amount is set!\n");
}


