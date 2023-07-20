#include"Application.h"
void another_process(void);
uint8_t anotherprocess=1;

ST_cardData_t card_data;
void appStart()
{
    while (anotherprocess==1)
    {
        system("cls");

        ST_terminalData_t terminal_data;

        uint8_t status=WRONG_NAME;

        /***********************************************************/
        while(status==WRONG_NAME)
        {
            status=getCardHolderName(&card_data);
            system("cls");
            printf("INVALID NAME! \n");
        }
        if(status==CARD_OK)
        {
            system("cls");
        }

        /***************************************************************/
        status=WRONG_EXP_DATE;
        while(status==WRONG_EXP_DATE)
        {
            status=getCardExpiryDate(&card_data);
            if (status == WRONG_EXP_DATE)
            {
                system("cls");
                printf("\nWRONG EXPIRY DATE FORMAT!\n ");

            }

        }
        if(status==CARD_OK)
        {
            system("cls");
        }

        /***************************************************************/
        status=WRONG_PAN;
        while(status==WRONG_PAN)
        {
            status=getCardPAN(&card_data);
			if (status == WRONG_PAN)
            {
                system("cls");
                printf("\nWRONG CARD PAN!\n");

            }

        }
        if(status==CARD_OK)
        {
            system("cls");
        }

        /*****************************************************************/
        status=WRONG_DATE;
        while(status==WRONG_DATE)
        {
            printf("Please enter transaction date DD/MM/YYYY : \n \n ");
            status=getTransactionDate(&terminal_data);
             if (status == WRONG_DATE)
            {
                system("cls");
                printf("\nWRONG TRANSACTION DATE FORMAT!\n ");

            }



        }
        if(status==TERMINAL_OK)
        {
            system("cls");
        }
        /********************************************************************/
        status=isCardExpired(&card_data,&terminal_data);
        if(status==EXPIRED_CARD)
        {
            system("cls");
            printf("DECLIEND!\n");
            printf("EXPIRED CARD!\n");
            anotherprocess=0;
            break;
        }
        else
        {
            system("cls");
        }
        /*********************************************************************/
        status=INVALID_AMOUNT;
        printf("Please enter transaction amount : \n \n ");
        while(status==INVALID_AMOUNT)
        {
            status=getTransactionAmount(&terminal_data);
              if (status == INVALID_AMOUNT)
            {
                system("cls");
                printf("PLEASE ENTER A VALID TRANSACTION AMOUNT! : \n \n ");

            }

        }

        if(status==TERMINAL_OK)
        {
            status=isBelowMaxAmount(&terminal_data);
            if(status==EXCEED_MAX_AMOUNT)
            {
                system("cls");
                printf("DECLIEND..EXCEEDING MAX AMOUNT!\n");
                printf("Please enter transaction amount : \n \n ");
                status=getTransactionAmount(&terminal_data);

            }
            else
            {
                //system("cls");
            }
        }
        /***********************************************************************/

        setMaxAmount(&terminal_data,maxAmount);

        /***********************************************************************/

        //update transaction data

        ST_transaction_t *p_transaction_data;
        ST_transaction_t  transaction_data;
        p_transaction_data=&transaction_data;

        strcpy( transaction_data.cardHolderData.cardExpirationDate,card_data.cardExpirationDate);

        strcpy(transaction_data.terminalData.transactionDate, terminal_data.transactionDate);
        strcpy(transaction_data.cardHolderData.cardHolderName, card_data.cardHolderName);
        for (int i=0; i<18; i++)
        {
            transaction_data.cardHolderData.primaryAccountNumber[i]=card_data.primaryAccountNumber[i];
        }

        transaction_data.terminalData.maxTransAmount = terminal_data.maxTransAmount;
        transaction_data.terminalData.transAmount = terminal_data.transAmount;

        /***********************************************************************/

        //check account status

        _isValidAccount= isValidAccount(&card_data,p_account);
        _isBlockedAccount= isBlockedAccount(p_account);
        _isAmountAvailable= isAmountAvailable(&terminal_data,p_account);

        // Actions to take according to status
        printf("\n");

        status=recieveTransactionData(&transaction_data);
        if(status==FRAUD_CARD) printf("Fraud Card process failed");
        else if(status==DECLINED_STOLEN_CARD) printf("Blocked card process failed");
        else if(status==INTERNAL_SERVER_ERROR) printf("process failed");
        else if(status==DECLINED_INSUFFECIENT_FUND) printf("There is no enough Fund process failed");
        else
        {

        }
        printf("\n");
        system("cls");
        printf("\nplease wait while processing .... \n\n");
        saveTransaction(p_transaction_data);

        printf("IF you want to make another process press 1 : ");

        another_process();
    }
}
// Function declaration to continue another process
void another_process(void)
{
    scanf("%d",&anotherprocess);
    if(anotherprocess==1)
    {
        appStart();
    }
    else
    {

    }
}
