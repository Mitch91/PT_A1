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

#include "tm_options.h"

/* add functions here for the implementation of each of the options
 * required to fulfil the requirements of the assignment
 */

/**************************************************************************
* purchase_ticket() - get input from the user about the ticket they wish 
* to purchase, retrieve that ticket from the list and adjust levels of the
* stock and the coins upon payment of the ticket. This function implements
* requirement 4 from the assignment 2 specification.
*
* Asks the user to choose their ticket, then insert coins, then gives 
* change if necessary.
**************************************************************************/
void purchase_ticket(tm_type * tm)
{
	stock_node * ticket;
	int i, price, change, coins_inserted[NUM_COINS];
	
	/* initialise coins_inserted to zeros because the user is yet to enter any 
	   coins and the values need to be zero */
	for(i = 0; i < NUM_COINS; i++) coins_inserted[i] = 0;
	
	printf("\n\nPurchase a Ticket\n----------------\n");
	
	/* get the user's choice of ticket, if choose_ticket returns FALSE 
	   return to menu */
	if(!(ticket = choose_ticket(tm->stock,'p'))) return;
	
	price = ticket->data->ticket_price;
	
	printf("\nThe price is ");
	print_dollar_format(price, NO_FORMATTING);
	
	/* get the user to insert coins, store the coins they inserted in coins_inserted
	   array and return the amount of change we need to give them. If its equal
	   to the constant RETURN_TO_MENU (which is negative) return to menu */
	if((change = insert_coins(price, coins_inserted)) == RETURN_TO_MENU) return;
	
	/* based on the coins we have in the machine and the coins they just inserted,
	   give the user the change they require */
	give_change(tm->coins, ticket, coins_inserted, change);
	
	ticket->data->stock_level--;
}

/**************************************************************************
* display_tickets() - iterate over the stock list and display a list of 
* tickets in the system according to the format specified in the assignment
* 2 specifications. This option implements requirement 5 from the assignment
* specifications.
*
* Displays the tickets stored in the machine in a similar fashion to 
* tester.o
**************************************************************************/
void display_tickets(tm_type * tm)
{
	stock_node * node = tm->stock->head_stock;
	int i;
	
	/* print the heading in a nicely formatted way */
	printf("%-*s %-*s %-*s %-*s Qty\n",TICKET_NAME_LEN,"Ticket",10,
		"Type",TICKET_ZONE_LEN,"Zone",9,"Price");
	
	/* print dashes under the headings and have spaces at the 41st, 52nd, 63rd
       and 73rd chars. Doesn't really make sense to have constants here since 
	   formatting can present you with such weird number, so I don't think there's
	   much of a choice other than to have magic numbers */
	for(i = 0; i < 76; i++){
		if(i == 40 || i == 51 || i == 62 || i == 72) fputs(" ",stdout);
		else fputs("-",stdout);
	}
	
	printf("\n");
	
	/* while node doesn't equal NULL */
	while(node){
		printf("%-*s ",TICKET_NAME_LEN,node->data->ticket_name);
		/* print the ticket name, left aligned */
		
		/* depending on whether ticket_type is F or C depends on what is printed */
		if(node->data->ticket_type == 'F') printf("Full fare  ");
		else printf("Concession ");
		
		/* print ticket zone, left aligned */
		printf("%-*s ",TICKET_ZONE_LEN,node->data->ticket_zone);
		
		/* print the price out in dollar format, with enough space for 7 digits 
		  (and 1 decimal) */
		print_dollar_format(node->data->ticket_price, 8);
		
		/* print the quantity, left algined */
		printf("% -3d\n",node->data->stock_level);
		
		/* go to the next node */
		node = node->next_node;
	}
	
	printf("\n\n");
}

/***************************************************************************
* add_ticket() - Request user input about creating a new ticket type in 
* the system. You need to validate this input and then create and insert 
* a new ticket into the system, sorted by ticket name. this option 
* implements requirement 6 in the assignment 2 specifications.
*
* Asks user to input info about the ticket, then adds it if all info is 
* valid
**************************************************************************/
void add_ticket(tm_type * tm)
{
	/* print the heading and go to choose_ticket with the mode 'a' for add */
	printf("\n\nAdd Ticket\n----------\n\n");
	choose_ticket(tm->stock, 'a');
}

/**************************************************************************
* delete_ticket() - Request user input from the administrator specifying
* the name, type and zone of the ticket. You will then search the stock
* list to delete this ticket. All three fields entered must match for the
* ticket to be deleted. Please ensure that you free any memory that was 
* dynamically allocated. This function implements requirement 7 from the 
* assignment 2 specifications.
*
* Asks user to input info about the ticket, the deletes it if it exists
**************************************************************************/
void delete_ticket(tm_type * tm)
{
	/* print the heading and go to choose_ticket with the mode 'd' for delete */
	printf("\n\nDelete Ticket\n-------------\n\n");
	choose_ticket(tm->stock,'d');
}

/**************************************************************************
* display_coins() - display a list of each of the coin types in the system
* and the count of each coin type according to the format specified in the
* assignment 2 specification. This function implements requirement 8 from
* the assignment 2 specification.
*
* Displays the coins in the machine in a similar fashion to the assignment
* specs
**************************************************************************/
void display_coins(tm_type * tm)
{
	coin_list_ptr coins = tm->coins;
	int i, coin_value, total_value = 0;
	
	/* print the headings and borders */
	printf("Coin  Quantity Value\n----- -------- ---------\n");
	
	/* loop through each denomination */
	for(i = 0; i < NUM_COINS; i++){
		
		/* Print each coins denomination with the same amount of space as 
		   its heading, Coin */
		print_dollar_format(coins[i].denomination,strlen("Coin"));
		
		/* Print each coins quantity (or count) with the same amount of space
		   as its heading, Quantity */
		printf(" %*d ",(int) strlen("Quantity"),coins[i].count);
		
		/* calculate the value of the specific denomination and print it with the
		   same amount of space as Quantity, to keep things constant and nicely 
		   formatted */
		coin_value = coins[i].count * coins[i].denomination;
		print_dollar_format(coin_value,strlen("Quantity"));
		
		printf("\n");
		
		/* as we go through keep track of the total coin value */
		total_value += coin_value;
	}
	
	/* print out the total value */
	printf("%24s\nTotal Value:   ","---------");
	print_dollar_format(total_value,strlen("Quantity"));
	printf("\n\n");

}

/**************************************************************************
* restock_tickets() - iterate over the list and set all ticket products
* to the default level specified in tm.h. This function implements the 
* requirement 9 in the assignment 2 specifications.
* 
* Iterates through all the tickets in the machine, setting their 
* stock_level to DEFAULT_STOCK_LEVEL. Unless it is already greater than
* DEFAULT_STOCK_LEVEL, because then you'd be taking tickets out of the 
* machine, which doesn't really make sense to do.
**************************************************************************/
void restock_tickets(tm_type * tm)
{
	stock_node * node = tm->stock->head_stock;
	printf("Restock Tickets\n---------------\n\n");
	while(node){
		/* if the stock level is greater than or equal to the stock level it doesn't
           make sense to restock it */
		if(node->data->stock_level >= DEFAULT_STOCK_LEVEL) {
			node = node->next_node;
			continue;
		}
		node->data->stock_level = DEFAULT_STOCK_LEVEL;
		node = node->next_node;
	}
	printf("All ticket products have been restocked to the default level\n\n");
}

/**************************************************************************
* restock_coins() - set the total number of coins of each denomination to
* the default number specified in tm.h. This function implements the 
* requirement 10 from the assignment 2 specifications.
*
* Same as above, loops through the array restocking the coins unless the 
* count of the coin is higher than the DEFAULT_COINS_COUNT.
**************************************************************************/
void restock_coins(tm_type * tm)
{
	int i;
	printf("Restock Coins\n-------------\n\n");
	for(i = 0; i < NUM_COINS; i++){
		/* same as with restock_tickets skip the certain denomination if its
		   already at or above the default level */
		if(tm->coins[i].count >= DEFAULT_COINS_COUNT) continue;
		tm->coins[i].count = DEFAULT_COINS_COUNT;
	}
	printf("All coins have been restocked to the default level\n\n");
}

/**************************************************************************
* save_data() - open the stockfile and the coinsfile for writing and 
* save all the data to these files. You need to ensure that you save data
* to these files in the same format as specified for loading this data in 
* so that your program or any alternate but correct implementation could
* load the resultant data files. This function implements requirement 11
* from the assignment 2 specifications.
*
* Opens the files, saves the data and exits. If anything gees wrong, 
* function acts like abort and just exits. 
**************************************************************************/
void save_data(tm_type * tm, char * stockfile, char * coinsfile)
{	
	/* open the files, pass them to save_coins and save_stock repsectively, if either
	   return false let the user know */
	if(!save_coins(tm->coins,fopen(coinsfile, "w")) || 
		!save_stock(tm->stock,fopen(stockfile, "w"))){
		fprintf(stderr, "Error: unable to save the files. Quitting.\n");
	}
}