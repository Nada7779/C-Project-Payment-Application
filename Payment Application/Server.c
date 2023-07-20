
#include"database.h"

EN_serverError_t _isValidAccount ;
EN_serverError_t _isBlockedAccount ;
EN_serverError_t _isAmountAvailable ;
EN_serverError_t _saveTransaction ;
ST_accountsDB_t *p_account = accountsDB;
ST_transaction_t *p_trancNum = transaction;
uint8_t t = 0;
uint8_t trans_num=0;


/******************************************* EN_transState_t**********************************************/

/*Description:
This function will take all transaction data and validate its data, it contains all server logic.
It checks the account details and amount availability.*/
//calling data base
EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    uint8_t account_index;
    float new_balance;
// check for account existence
    if( _isValidAccount == ACCOUNT_NOT_FOUND) return FRAUD_CARD ;

// check for Blocked accounts
    else if (_isBlockedAccount == BLOCKED_ACCOUNT) return DECLINED_STOLEN_CARD;


//check for amount availability
    else if (_isAmountAvailable == LOW_BALANCE ) return DECLINED_INSUFFECIENT_FUND;
//update the database with the new balance

    else if (_saveTransaction!=SERVER_OK) return INTERNAL_SERVER_ERROR;

    else
    {

        new_balance= p_account->balance- transData->terminalData.transAmount;
        p_account->balance=new_balance;

        return APPROVED;
    }


}


// implement test function here
void recieveTransactionDataTest(void)
{
    EN_transState_t actualResult ;
    p_account=&accountsDB[0];
    ST_transaction_t *p_user1;

    ST_transaction_t user1 =
    {


        {
            "kareem magdy", "11111111112222222222","02/24"
        },

        {
            2500,1000,"02/23"
        },


    };

    p_user1=&user1;



    printf("Tester Name: NADA ABDELAZIM \n");
    printf( "Function Name: recieveTransactionData \n\n");


    printf("--------------------------------------------------------------\n");

    _isValidAccount    =  SERVER_OK;
    _isAmountAvailable =  SERVER_OK;
    _isBlockedAccount  =  SERVER_OK;
    actualResult = recieveTransactionData(p_user1);

    printf("Test Case 1: APPROVED \n");
    printf("Input Data:{kareem magdy, 11111111112222222222,02/24},{2500,1000,02/23} \n");
    printf("Expected Result: APPROVED ");

    if(actualResult==APPROVED)
        printf("    Actual Result:  APPROVED \n");

    printf("account updated balabce = %f ",p_account->balance);

    printf("\n--------------------------------------------------------------\n");





    _isValidAccount  =  ACCOUNT_NOT_FOUND;
    actualResult = recieveTransactionData(p_user1);

    printf("Test Case 2:FRAUD_CARD \n");
    printf("Input Data:{kareem magdy, 11111111112222222222,02/24},{2500,1000,02/23} ,  \n");
    printf("Expected Result: FRAUD_CARD ");

    if(actualResult==FRAUD_CARD)
        printf("    Actual Result:  FRAUD_CARD \n ");



    printf("\n--------------------------------------------------------------\n");



    _isValidAccount    =  SERVER_OK;
    _isBlockedAccount  =  BLOCKED_ACCOUNT;
    actualResult = recieveTransactionData(p_user1);


    printf("Test Case 3:DECLINED_STOLEN_CARD \n");
    printf("Input Data:{kareem magdy, 11111111112222222222,02/24},{2500,1000,02/23}  \n");
    printf("Expected Result: DECLINED_STOLEN_CARD ");

    if(actualResult==DECLINED_STOLEN_CARD)
        printf("    Actual Result:  DECLINED_STOLEN_CARD \n ");


    printf("\n--------------------------------------------------------------\n");



    _isValidAccount      =  SERVER_OK;
    _isBlockedAccount    =  SERVER_OK;
    _isAmountAvailable  = LOW_BALANCE;
    actualResult = recieveTransactionData(p_user1);

    printf("Test Case 4:DECLINED_INSUFFECIENT_FUND \n");
    printf("Input Data:{kareem magdy, 11111111112222222222,02/24},{2500,1000,02/23} \n");
    printf("Expected Result: DECLINED_INSUFFECIENT_FUND ");

    if(actualResult==DECLINED_INSUFFECIENT_FUND)
        printf("    Actual Result:  DECLINED_INSUFFECIENT_FUND \n ");

    printf("\n--------------------------------------------------------------\n");



}



/************************************** END OF EN_transState_t ***********************************************/








/** REQUIRMENTS :-
 1- check pan given with pan in database   --- (done)
 2- if exists  --> SEREVER_OK           ----> return reference to this account in the DB    --- (done)
 3- if not     --> ACCOUNT_NOT_FOUND    ----> return ACCOUNT_NOT_FOUND
                                        ----> account reference will be NULL


/******************************************* isValidAccount **********************************************/
//calling database and card data

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence)
{

    uint8_t exist_flag = 0 ;
    EN_serverError_t server_status ;

    for(uint8_t account_num= 0 ; account_num< 10 ; account_num++)
    {
        for(uint8_t counter = 0 ; counter < 18 ; counter++)
        {
            if( cardData->primaryAccountNumber[counter] == (accountRefrence)->primaryAccountNumber[counter] )
            {
                exist_flag =1 ;
            }
            else
            {
                accountRefrence++;
                exist_flag =0;
                break ;
            }
        }
    }

    if(exist_flag)
    {
        server_status = SERVER_OK ;
    }
    else
    {
        server_status =ACCOUNT_NOT_FOUND  ;
        accountRefrence = NULL ;

    }
    p_account = accountRefrence;


    /*/*
     for (int i = 0; i < 10; i++)
    {
        // Note: check this--- transData->cardHolderData.primaryAccountNumber!
        if (strcmp((char *) accountRefrence[i].primaryAccountNumber, (char *) transData->cardHolderData.primaryAccountNumber) == 0)
            account_index=i;
        else  return FRAUD_CARD;
    }
     */

    return server_status ;
}

// implement test function here


void isValidAccountTest(void)
{
    uint8_t  actualResult ;
    ST_cardData_t user1 =
    {
        "kareem magdy","77777777777777777777", "02/22"
    };


    printf("Tester : Kareem Magdy \n");
    printf( "Function Name: isValidAccount \n\n");

    printf("--------------------------------------------------------------\n");
    printf("Test Case 1: \n");
    printf("    Input Data:   \n");
    printf("        - pointer to ST_cardData_t has the following data ( kareem magdy , 77777777777777777777 , 02/22 ) \n");
    printf("        - DataBase for ST_accountsDB_t \n");
    printf("    Expected Result: ACCOUNT_NOT_FOUND \n");


    actualResult =isValidAccount(&user1,p_account);
    if(actualResult== ACCOUNT_NOT_FOUND)
        printf("    Actual Result:  ACCOUNT_NOT_FOUND \n ");

    printf("--------------------------------------------------------------\n");

    ST_cardData_t user2 =
    {
        "Nada abdelazim", "55555555558888888888", "02/22"
    };

    printf("Test Case 2: \n");
    printf("    Input Data:   \n");
    printf("        - pointer to ST_cardData_t has the following data ( Nada abdelazim , 55555555558888888888 , 02/22 ) \n");
    printf("        - DataBase for ST_accountsDB_t \n");
    printf("    Expected Result: SERVER_OK \n");


    actualResult =isValidAccount(&user2,p_account);
    if(actualResult== SERVER_OK)
        printf("    Actual Result:  SERVER_OK \n ");

    printf("--------------------------------------------------------------\n");






}

/*************************************** END OF isValidAccount ***********************************************/












/******************************************* isBlockedAccount **********************************************/
//calling pointer to account
/*
EN_serverError_t isBlockedAccount(ST_accountsDB_t * accountRefrence)
{
    if (accountRefrence[account_index].state == BLOCKED)
    {
        printf(" DECLINED_STOLEN_CARD\n");
        return DECLINED_STOLEN_CARD;
    }
    else
    {
        printf("SERVER_OK\n");
    }
    return SERVER_OK;
}
}*/

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{

    if(_isValidAccount== SERVER_OK)
    {
        if (accountRefrence->state==BLOCKED)
        {


            return BLOCKED_ACCOUNT ;

        }
        else
        {

            return SERVER_OK;

        }

    }

}


// implement test function here
void isBlockedAccountTest(void)
{
    uint8_t  actualResult ;
    ST_cardData_t user1 =
    {
        "kareem magdy","55555555558888888888", "02/22"
    };


    printf("Tester :   \n");
    printf( "Function Name: isBlockedAccount \n\n");

    printf("--------------------------------------------------------------\n");
    printf("Test Case 1: \n");
    printf("    Input Data:   \n");
    printf("        - pointer to ST_cardData_t has the following data ( kareem magdy , 55555555558888888888 , 02/22 ) \n");
    printf("    Expected Result: BLOCKED_ACCOUNT \n");

    _isValidAccount = isValidAccount(&user1,p_account);
    actualResult =isBlockedAccount(p_account);
    if(actualResult== BLOCKED_ACCOUNT)
        printf("    Actual Result:   BLOCKED_ACCOUNT \n ");

    printf("--------------------------------------------------------------\n");

    ST_cardData_t user2 =
    {
        "Nada abdelazim", "11111111112222222222", "02/22"
    };

    printf("Test Case 2: \n");
    printf("    Input Data:   \n");
    printf("        - pointer to ST_cardData_t has the following data ( Nada abdelazim , 11111111112222222222 , 02/22 ) \n");
    printf("    Expected Result: SERVER_OK \n");

    _isValidAccount = isValidAccount(&user2,p_account);
    actualResult = isBlockedAccount(p_account);
    if(actualResult== SERVER_OK)
        printf("    Actual Result:   SERVER_OK \n ");

    printf("--------------------------------------------------------------\n");

}
/*************************************** END OF isBlockedAccount ***********************************************/










/******************************************* isAmountAvailable **********************************************/
// calling terminal data and database
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence)
{

    if(_isValidAccount==SERVER_OK && _isBlockedAccount == SERVER_OK)
    {
        if ((accountRefrence->balance)<(termData->transAmount))
        {
            return LOW_BALANCE;
        }
        else
        {
            return SERVER_OK;
        }

    }
}


// implement test function here

void isAmountAvailableTest(void)
{
    uint8_t  actualResult ;
    ST_terminalData_t t_user1 =
    {
        1000.0,5000,"07/24"
    };



    ST_cardData_t c_user1 =
    {
        "kareem magdy","89893746154368511234", "02/22"
    };


    printf("Tester :   \n");
    printf( "Function Name: isAmountAvailableTest \n\n");

    printf("--------------------------------------------------------------\n");
    printf("Test Case 1: \n");
    printf("    Input Data:   \n");
    printf("        - pointer to ST_terminalData_t has the following data { 2000.0,5000,02/24 } \n");
    printf("        - pointer to the account in DataBase ST_accountsDB_t \n");
    printf("    Expected Result: SERVER_OK \n");

    _isValidAccount = isValidAccount(&c_user1,p_account);
    _isBlockedAccount =isBlockedAccount(p_account);
    actualResult = isAmountAvailable(&t_user1,p_account);
    if(actualResult== SERVER_OK)
        printf("    Actual Result:   SERVER_OK \n ");

    printf("--------------------------------------------------------------\n");

    ST_terminalData_t t_user2 =
    {
        11000.0,1000,"02/24"
    };

    ST_cardData_t c_user2 =
    {
        "Nada abdelazim", "33333333334444444444", "02/22"
    };

    printf("Test Case 2: \n");
    printf("    Input Data:   \n");
    printf("        - pointer to ST_terminalData_t has the following data { 9000.0,1000,02/24 } \n");
    printf("        - pointer to the account in DataBase ST_accountsDB_t \n");
    printf("    Expected Result: LOW_BALANCE \n");

    _isValidAccount = isValidAccount(&c_user2,p_account);
    _isBlockedAccount =isBlockedAccount(p_account);
    actualResult = isAmountAvailable(&t_user2,p_account);

    if(actualResult== LOW_BALANCE)
        printf("    Actual Result:   LOW_BALANCE \n ");

    printf("--------------------------------------------------------------\n");

}

/*************************************** END OF isAmountAvailable ***********************************************/










/******************************************* saveTransaction **********************************************/



EN_serverError_t saveTransaction(ST_transaction_t *transData)
{

//Card data
    for(uint8_t cardHolderName = 0 ; cardHolderName<25 ; cardHolderName++)
    {
        p_trancNum->cardHolderData.cardHolderName[cardHolderName] = transData->cardHolderData.cardHolderName[cardHolderName];

    }


    for(uint8_t C_PrimaryNum = 0 ; C_PrimaryNum <20 ; C_PrimaryNum++)
    {
        p_trancNum->cardHolderData.primaryAccountNumber[C_PrimaryNum] = transData->cardHolderData.primaryAccountNumber[C_PrimaryNum];

    }


    for(uint8_t C_ExpireDate = 0 ; C_ExpireDate <6 ; C_ExpireDate++)
    {
        p_trancNum->cardHolderData.cardExpirationDate[C_ExpireDate] = transData->cardHolderData.cardExpirationDate[C_ExpireDate];

    }


//terminal data
    p_trancNum->terminalData.maxTransAmount = transData->terminalData.maxTransAmount;
    p_trancNum->terminalData.transAmount = transData->terminalData.transAmount;

    for(uint8_t C_transDate=0 ; C_transDate<11 ; C_transDate++)
    {
        p_trancNum->terminalData.transactionDate[C_transDate] = transData->terminalData.transactionDate[C_transDate];
    }



    if(_isValidAccount == ACCOUNT_NOT_FOUND)
    {
        p_trancNum->transState=FRAUD_CARD;

    }
    else if (_isBlockedAccount==BLOCKED_ACCOUNT)
    {

        p_trancNum->transState=DECLINED_STOLEN_CARD;
    }
    else if(_isAmountAvailable == LOW_BALANCE)
    {

        p_trancNum->transState=DECLINED_INSUFFECIENT_FUND;
    }

    else
    {
        p_trancNum->transState=APPROVED;
    }


    if(p_trancNum == &transaction[0])
    {
        p_trancNum->transactionSequenceNumber = 1;
    }
    else
    {
        p_trancNum->transactionSequenceNumber = p_trancNum->transactionSequenceNumber=((p_trancNum-1)->transactionSequenceNumber)+1;

    }
    listSavedTransactions();
    t++;
    p_trancNum=transaction+t;
    return SERVER_OK ;
}

// implement test function here
void saveTransactionTesr(void)
{
    uint8_t  actualResult ;


    ST_transaction_t *p_user1;
    ST_transaction_t user1=
    {

        {
            "kareem magdy", "11111111112222222222","02/24"
        },

        {
            2500,1000,"02/23"
        },

    };
    p_user1=&user1;
    _isValidAccount = ACCOUNT_NOT_FOUND;
    saveTransaction(p_user1);
    /*
        printf("Tester :   \n");
        printf( "Function Name: isAmountAvailableTest \n\n");

        printf("--------------------------------------------------------------\n");
        printf("Test Case 1: \n");
        printf("    Input Data:   \n");
        printf("        - pointer to ST_transaction_t has the following data { {kareem magdy, 11111111112222222222,02/24},{2500,1000,02/23},APPROVED,5 } \n");
        printf("    Expected Result: SERVER_OK and user transaction data saved in database\n");
        _isValidAccount = ACCOUNT_NOT_FOUND;
        actualResult= saveTransaction(p_user1);
        if(actualResult == SERVER_OK)  printf("\n    Actual Result:   SERVER_OK \n ");

    */

    ST_transaction_t *p_user2;
    ST_transaction_t user2=
    {

        {
            "nada", "55555555558888888888","02/24"
        },

        {
            9000,1000,"07/21"
        },


    };
    p_user2=&user2;

    /*
        printf("--------------------------------------------------------------\n");
        printf("Test Case 2: \n");
        printf("    Input Data:   \n");
        printf("        - pointer to ST_transaction_t has the following data { {kareem magdy, 11111111112222222222,02/24},{2500,1000,02/23},APPROVED,5 } \n");
        printf("    Expected Result: SERVER_OK and user transaction data saved in database\n");
        _isValidAccount = APPROVED;
        */
    _isValidAccount = APPROVED;

    _isBlockedAccount=BLOCKED_ACCOUNT;
    actualResult= saveTransaction(p_user2);


    ST_transaction_t *p_user3;
    ST_transaction_t user3=
    {

        {
            "Amr", "11111111112222222222","02/24"
        },

        {
            90004,1000,"08/23"
        },


    };
    p_user3=&user3;


    _isValidAccount = APPROVED;

    _isBlockedAccount=RUNNING;
    actualResult= saveTransaction(p_user3);



    ST_transaction_t *p_user4;
    ST_transaction_t user4=
    {

        {
            "Moustafa", "9876546639026543","03/24"
        },

        {
            90004,1000,"08/23"
        },


    };
    p_user4=&user4;


    _isValidAccount = APPROVED;
    _isBlockedAccount=RUNNING;
    p_trancNum->transState ==INTERNAL_SERVER_ERROR;
    actualResult= saveTransaction(p_user4);



    ST_transaction_t *p_user5;
    ST_transaction_t user5=
    {

        {
            "Mohamed", "4785169874521369","09/23"
        },

        {
            90004,1000,"08/23"
        },


    };
    p_user5=&user5;


    _isValidAccount = APPROVED;
    _isBlockedAccount=RUNNING;
    _isAmountAvailable == LOW_BALANCE;
    actualResult= saveTransaction(p_user5);
    /*
    if(actualResult == SERVER_OK)  printf("\n    Actual Result:   SERVER_OK \n ");
    printf("--------------------------------------------------------------\n");
    */
}





/*************************************** END OF saveTransaction ***********************************************/




/******************************************* listSavedTransactions **********************************************/


void listSavedTransactions(void)
{

    printf("-------------------------------------\n");
    printf("Card Holder Name : ");

    p_trancNum=transaction+trans_num;

    for(uint8_t cardHolderName = 0 ; cardHolderName<24 ; cardHolderName++)
    {
        printf("%c",p_trancNum->cardHolderData.cardHolderName[cardHolderName]) ;

    }
    printf("\t ");

    printf("PAN: ");

    for(uint8_t C_PrimaryNum = 0 ; C_PrimaryNum <18 ; C_PrimaryNum++)
    {
        printf("%c", p_trancNum->cardHolderData.primaryAccountNumber[C_PrimaryNum] );

    }
    printf("\t");

    printf("ExpireDate : ");

    for(uint8_t C_ExpireDate = 0 ; C_ExpireDate <6 ; C_ExpireDate++)
    {
        printf("%c", p_trancNum->cardHolderData.cardExpirationDate[C_ExpireDate]);

    }

    printf("\n");
    printf("MaxTransAmount : ");
    printf("%.2f", p_trancNum->terminalData.maxTransAmount) ;

    printf("\t\t\t ");
    printf("TransAmount : ");
    printf("%.2f",p_trancNum->terminalData.transAmount );

    printf("\t\t");
    printf("TransactionDate : ");
    for(uint8_t C_transDate=0 ; C_transDate<11 ; C_transDate++)
    {
        printf("%c",p_trancNum->terminalData.transactionDate[C_transDate] );
    }
    printf("\n");
    printf("TransState : ");

    if(p_trancNum->transState == APPROVED) printf("APPROVED");
    else if(p_trancNum->transState == DECLINED_INSUFFECIENT_FUND) printf("DECLINED_INSUFFECIENT_FUND");
    else if(p_trancNum->transState == DECLINED_STOLEN_CARD) printf("DECLINED_STOLEN_CARD");
    else if(p_trancNum->transState == FRAUD_CARD) printf("FRAUD_CARD");
    else  printf("INTERNAL_SERVER_ERROR");


    printf("\n");
    printf("Current balance  : ");
    if(p_account!=NULL)
    printf("%.2f",p_account->balance);

    printf("\n");
    printf("Sequence Number : ");
    printf("%d",p_trancNum->transactionSequenceNumber);


    printf("\n-------------------------------------\n");

    trans_num++;




}



/******************************************* End of listSavedTransactions **********************************************/





