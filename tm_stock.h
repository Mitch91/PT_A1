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
#ifndef TM_STOCK_H
#define TM_STOCK_H
#include "tm.h"

#define print_ticket_info(action) printf("Ticket '%s ",name); \
		if(type == 'F') printf("full fare "); \
		else printf("concession "); \
		printf("zone %s' has been %s from the ticketing machine\n\n",zone,action)

/* A sequence of macros that validate each field of the stock data 
   (incorrect_format() is another macro, located in tm_utility.h)
	incorrect_format() frees file_contents and lines but not copy so
	we must free that before calling it. This is because incorrect_fromat()
	is also called by load_coins(), which doesn't use a variable copy */

/* Tests to see if name is largest than the max length allowed, if so, tells
   the user, frees copy and calls incorrect_format() */		
#define validate_ticket_name(name) if(strlen(name) > TICKET_NAME_LEN){\
		printf("Ticket field is too long, must be less than or "\
			"equal %d\n",TICKET_NAME_LEN);\
		free(copy); incorrect_format("Stock");}

/* Tests if the string is only 1 character and if that character is a F or C.
   If not, do the same as above */		
#define validate_ticket_type(type) \
	if(strlen(type) > 1 || (*type != 'F' && *type != 'C')){\
		free(copy); incorrect_format("Stock");}

/* Tests to see if zone is larger than the max length, if so, does the same as 
   above */		
#define validate_ticket_zone(zone) \
	if(strcmp(zone,"1") && strcmp(zone,"2") && strcmp(zone,"1+2")){\
		printf("Zone must be '1', '2' or '1+2'"); free(copy); \
		incorrect_format("Stock");}

/* Tries to convert price_string to price, if the value of token was
   not completely numeric, then the strcmp will return non-zero (true).
   Statement will also be true if the price is numeric but larger than
   MAX_TICKET_PRICE ($99.99)*/
			
#define validate_ticket_price(price_string) \
	price = strtol(price_string, &temp, 10);\
	if(strcmp(temp,"") || price > MAX_TICKET_PRICE){\
		printf("Price is either not numeric or is larger than %d\n",\
		MAX_TICKET_PRICE); free(copy); incorrect_format("Stock");}
		
/* similarly as stated above */	
	
#define validate_stock_level(stock_level_string) \
	stock_level = strtol(stock_level_string, &temp, 10);\
	if(strcmp(temp,"") || stock_level > MAX_STOCK_LEVEL){\
		printf("Stock level is either not numeric or is larger than"\
			" %d\n",MAX_STOCK_LEVEL); free(copy); incorrect_format("Stock");}
		
/* Defines the max length of a line within the stock file.
   Uses the assumptions that ticketName is <= 40 chars,
   type is 1 char, zone is <= 3 chars, price is <= $99.99 (4 chars)
   and quantity is <= 99 (2 chars). 
   40 + 1 + 10 + 4 + 2 = 57 + 4 commas + \0 = 62   */
#define STOCK_FILE_MAX_LINE_LENGTH 62

/* Defines the maximum price of a ticket as 9999 ($99.99) and maximum
   number of tickets there can be of a particular ticket as 99 */
#define MAX_TICKET_PRICE 9999
#define MAX_STOCK_LEVEL 99

#define NUM_STOCK_TOKENS 5

struct stock_data 
{
    char ticket_name[TICKET_NAME_LEN+1];
    char ticket_type;
    char ticket_zone[TICKET_ZONE_LEN+1];
    unsigned int ticket_price;
    unsigned int stock_level;
};

typedef struct stock_node 
{
    struct stock_data * data;
    struct stock_node * next_node;
} stock_node;

#define STOCK_NODE

struct stock_list
{
    stock_node * head_stock;
    unsigned int num_stock_items;
};

BOOLEAN load_stock(struct stock_list * stock, FILE * fp);
BOOLEAN add_stock_node(struct stock_list * stock, char * name, char type, char * zone, 
	unsigned int price, unsigned int stock_level); 
void delete_stock_node(struct stock_list * stock, stock_node * ticket);
stock_node * choose_ticket(struct stock_list * stock, char mode);
stock_node * get_ticket(struct stock_list * stock, char * name, char type,
	char * zone);
void free_stock(struct stock_list * stock);
BOOLEAN save_stock(struct stock_list * stock, FILE * fp);
#endif