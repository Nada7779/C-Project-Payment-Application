#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED
#include<stdio.h>
#include<string.h>
#include<conio.h>

typedef unsigned char uint8_t;

/**********************************************/


typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
} ST_cardData_t;

extern ST_cardData_t card_data;

typedef enum EN_cardError_t
{
    CARD_OK,
    WRONG_NAME,
    WRONG_EXP_DATE,
    WRONG_PAN
}EN_cardError_t;

/*******************************************************/
/* Description:
 * - This function takes a reference to a card data type
 * - ask the user to enter his name
 * - validate correctness of the name
 * Return:
 * - wrong name  in case of invalid name
 * - card ok  in case of valid name
 */

EN_cardError_t getCardHolderName(ST_cardData_t*cardData);
/*********************************************************/
/* Description:
 * - This function takes a reference to a card data type
 * - ask the user to enter his expiry date
 * - validate correctness of the date
 * Return:
 * - wrong date  in case of invalid expiry date
 * - card ok  in case of valid  expiry date
 */

EN_cardError_t getCardExpiryDate(ST_cardData_t*cardData);
/*********************************************************/
/* Description:
 * - This function takes a reference to a card data type
 * - ask the user to enter his PAN
 * - validate correctness of the PAN
 * Return:
 * - wrong PAN  in case of invalid PAN
 * - card ok  in case of valid  PAN
 */
EN_cardError_t getCardPAN(ST_cardData_t*cardData);
/********************************************************/
/* Description:
 * - This function takes void
 * - to test the card holder name function
 * Return:void
 */
void getCardHolderNameTst(void);
/********************************************************/
/* Description:
 * - This function takes void
 * - to test the card expiry date function
 * Return:void
 */
void getCardExpiryDateTest(void);
/*******************************************************/
/* Description:
 * - This function takes void
 * - to test the PAN function
 * Return:void
 */
void getCardPANTest(void);
/********************************************************/
/* Description:
 * - This function takes void
 * - to test the card module integration
 * Return:void
 */
void CardModuleTest(void);


#endif // CARD_H_INCLUDED

