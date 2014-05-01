/***************************************************************************
* COSC1283/1284 - Programming Techniques
* Semester 2 2013 Assignment #2 - SCSIT Program Management System
* Full Name        : Mitchell Elsbury
* Student Number   : 3286283
* Yallara Username : s3286283
* Course Code      : COSC1284
* Program Code     : BP094SEC8
* Start up code provided by Paul Miller and Lin Padgham
***************************************************************************/
#ifndef TM_COINS_H
#define TM_COINS_H
#include "tm.h"

/* Defines the max length of a line within the coins file.
   Defined as 8 because the longest denomination is 3 chars,
   plus a comma, then using the assumption that coin counter
   can't be above 9999 thats another 4 characters which gives
   us 8 in total. */
#define COINS_FILE_MAX_LINE_LENGTH 8

/* defines the number of tokens in a line in the coinsfile */
#define NUM_COIN_TOKENS 2

/* specifies the various coin types in the system and their values */
enum coin_types
{
    FIVE_CENTS = 5,
    TEN_CENTS = 10,
    TWENTY_CENTS = 20,
    FIFTY_CENTS = 50,
    ONE_DOLLAR = 100,
    TWO_DOLLARS = 200
};

/* defines a 'coin' in the system. the coinslist is actually an array of 
 * this type
 */
struct coin
{
    enum coin_types denomination;
    unsigned count;
};

BOOLEAN load_coins(struct coin * coins, FILE * fp);

/* in tm_stock.h, because of the way the #includes are ordered, this function is 
   defined before the stock_node datatype is defined. So to avoid this, we #define
   STOCK_NODE in tm_stock.h after defining the stock_node datatype. Only problem
   with this is that this function isn't defined in tm_stock.c, so any calls will
   cause an error. But in this case, because of the nature of the function this 
   won't happen. */   
#ifdef STOCK_NODE
void give_change(struct coin * coins, stock_node * ticket, int * coins_inserted, 
	int change); 
#endif

BOOLEAN save_coins(struct coin * coins, FILE * fp);

#endif
