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

#include "tm_utility.h"

/* add any 'helper' functions here that provide generic service to your 
 * application. read_rest_of_line() is provided here as an example of this
 */

/***************************************************************************
* read_rest_of_line() - reads characters from the input buffer until 
* all characters have been cleared. You will need to call this in 
* association with fgets().
***************************************************************************/
void read_rest_of_line(void)
{
    int ch;
    while(ch=getc(stdin), ch!=EOF && ch!='\n');
    clearerr(stdin);
}

/***************************************************************************
* system_init() - allocate memory if necessary and initialise the struct tm
* to safe initial values. 
*
* Allocate memory for the coin list array and alloc memory for the head 
* of the stock and a counter. If all goes well, return TRUE otherwise FALSE.
***************************************************************************/
BOOLEAN system_init(tm_type * tm)
{	
	/* allocate NUM_COINS blocks of the size of a coin struct. If calloc returns
	   NULL we can't allocate the memory and therefore can't proceed so we tell
	   main() that we failed by returning false.
	*/ 
	if((tm->coins = calloc(NUM_COINS, sizeof(struct coin))) == NULL) {
		fprintf(stderr,"Error: unable to allocate memory for coin list. Program exiting\n");
		return FALSE;
	}
	
	/* we allocate enough room for a stock node and an int. If it fails return FALSE*/
	if(!(tm->stock = malloc(sizeof(stock_node) + sizeof(int)))){
		printf("Unable to allocate memory for stock list. Program exiting\n");
		free(tm->coins);
		return FALSE;
	}
	
	/*since we have no tickets yet, init the head to NULL and the count to zero */
	tm->stock->head_stock = NULL;
	tm->stock->num_stock_items = 0;
	/* we initialised both our lists, so tell main we succeeded by returning true */
    return TRUE;
}

/***************************************************************************
* load_data() - load data from both the stock file and the coins file and 
* populate the datastructures keeping in mind data validation and sorting 
* requirements. This function implements the requirement 2 from the 
* assignment 2 specifications. 
*
* Opens both files, the calls load_coins to load the coins file, if every-
* thing went fine, load the stock file. If anything goes wrong at any point
* in time, return FALSE.
***************************************************************************/
BOOLEAN load_data(tm_type * tm, char * stockfile, char * coinsfile)
{
	FILE *stock_fp, *coins_fp;

	/* open the files, make sure everything went ok */
	if((stock_fp = fopen(stockfile, "r")) == NULL || 
		(coins_fp = fopen(coinsfile, "r")) == NULL){
		fprintf(stderr, "Error: unable to open the files\n");
		return FALSE;
	}

	/* load the coins file, if load_coins returns false, then something
	   went wrong */
	if(!load_coins(tm->coins, coins_fp)){
		fprintf(stderr, "Error: unable to load the coins file %s\n", coinsfile);
		fclose(coins_fp);
		fclose(stock_fp);
		return FALSE;
	}
	
	/* load the stock file, if load_stock returns false, then something
	   went wrong */
	if(!load_stock(tm->stock, stock_fp)){
		fprintf(stderr, "Error: unable to load the stock file %s\n", stockfile);
		fclose(coins_fp);
		fclose(stock_fp);
		return FALSE;
	}
	
	/* close the files */
	fclose(coins_fp);
	fclose(stock_fp);
	
	/* tell main everything went well */
	return TRUE;
}

/***************************************************************************
* print_dollar_format - prints the input cents in dollar format, 
* eg: cents = 350, $3.50 is printed. Where spaces is the number of spaces
* the value will take up, if the number is larger than needed, it pads the
* left hand side, between the dollar value and the dollar sign
***************************************************************************/

void print_dollar_format(int cents, int spaces){
	int whole_number, decimal;
	
	/* divide cents by number of cents in a dollar, since both numbers are integers,
	   we receive a whole integer number which corresponds to the number of dollars 
	   cents is equal to */
	whole_number = cents / CENTS_PER_DOLLAR;
	
	/* the number of cents left over is total number of cents minus the number of
       dollars (in cents). The print both values, 2 places for cents, a decimal then
       the rest of spaces (spaces - 3) is for the dollars and extra padding */
	decimal = cents - whole_number * CENTS_PER_DOLLAR;
	printf("$%*d.%02d",spaces - 3,whole_number,decimal);
}

/***************************************************************************
* insert_coins() - iteratively asks the user to insert coins until the value
* of price is reached or exceeded. The coins inserted are stored in the 
* array coins_inserted. The value returned is then the amount of change
* owing to the user
***************************************************************************/

int insert_coins(int price, int * coins_inserted){
	
	int coin;
	printf("\n\n");
	
	/* the user still needs to insert more money */
	while(price > 0){
		printf("Enter a coin (");
		print_dollar_format(price, NO_FORMATTING);
		printf(" remaining): ");
		
		/* get an int value between the values of a five cent coin and a two dollar
		   coin, the check to make sure its a valid value for a coin, if not tell the
		   user to try again or press enter to return to the main menu */
		if((coin = get_int(FIVE_CENTS,TWO_DOLLARS)) == RETURN_TO_MENU) 
			return RETURN_TO_MENU;
		if(coin != FIVE_CENTS && coin != TEN_CENTS && coin != TWENTY_CENTS && 
			coin != FIFTY_CENTS && coin != ONE_DOLLAR && coin != TWO_DOLLARS){
			printf("Invalid coin value, try again.\n");
			continue;
		}
		
		price -= coin;
		
		/* add one to the number of coins inserted for the specific denomination */
		switch(coin){
			case FIVE_CENTS:
				coins_inserted[0]++;
				break;
			
			case TEN_CENTS:
				coins_inserted[1]++;
				break;
				
			case TWENTY_CENTS:
				coins_inserted[2]++;
				break;
				
			case FIFTY_CENTS:
				coins_inserted[3]++;
				break;
				
			case ONE_DOLLAR:
				coins_inserted[4]++;
				break;
				
			case TWO_DOLLARS:
				coins_inserted[5]++;
				break;
		}
	}
	
	/* price will be negative or zero, since we want to return the amount of change
       owing, we want a positive number, so we multiply price by -1 */
	return price * -1;
}

/***************************************************************************
* tokenise_stock_lines() - breaks file_contents up into lines and stores 
* them in the variable lines. If the number of lines within file_contents
* exceeds num_lines, the function returns FALSE, otherwise returns the 
* number of lines in file_contents. 
***************************************************************************/
int tokenise_stock_lines(char ** lines, char * file_contents, int num_lines){
	int i = 0;
	char * temp;
	
	/* tokenise the file contents and stores them in lines */
	lines[i] = strtok(file_contents, LINE_DELIMS);
	for(i = 1;; i++){
		temp = strtok(NULL, LINE_DELIMS);
		/* if temp equals NULL we're done */
		if(!temp) break;
		else if(num_lines == i){
			/* if we get here, there are too many lines for the amount of memory we
               have allocated. Return false so we can allocate more memory and try 
			   again */
			return FALSE;
		}
		lines[i] = temp;
	}
	/* return the number of lines in the file */
	return i;
}

/***************************************************************************
* get_file_size() - tells you the size of the file pointed to by fp in
* bytes. Is used to allocate memory for putting the file contents in a 
* variable.
***************************************************************************/

int get_file_size(FILE * fp){
	int filesize;
	/* go to the end of the file */
	fseek(fp, 0, SEEK_END);
	/* get the position, which in turn is the number of bytes in the file */
	filesize = ftell(fp);
	/* take the pointer back to the start of the file */
	rewind(fp);
	return filesize;
}

/***************************************************************************
* get_user_choice() - Displays the possible options to the user then asks
* for their input, returns the user's input. 
***************************************************************************/

int get_user_choice(void){
	OPTION option_number;
	disp_options();
	option_number = get_int(PURCHASE_TICKET, ABORT);
	return option_number;
}

/***************************************************************************
* disp_options - displays the possible options the user can choose from.
***************************************************************************/

void disp_options(void){
	printf("Main Menu:\n"
		"1) Purchase Ticket\n"
		"2) Display Ticket\n"
		"3) Save and Exit\n"
		"Administrator-Only Menu:\n"
		"4) Add Ticket\n"
		"5) Remove Ticket\n"
		"6) Display Coins\n"
		"7) Restock Tickets\n"
		"8) Restock Coins\n"
		"9) Abort\n\n"
		"Select your option (1-9): ");
}

/***************************************************************************
* get_ticket_type() - iteratively asks the user for input until they enter
* 'F' or 'C'. This value is the returned.
***************************************************************************/

char get_ticket_type(void){
	char type;
	BOOLEAN valid = FALSE;
	
	/* while invalid type, get a string of length 1 char, store it in type, if it
       equals F or C we're done, otherwise try again. Return \n if the user wants to
	   return to menu, since this is what character would be read by get_string */
	while(!valid){
		if(get_string(1,&type) == RETURN_TO_MENU) return '\n';
		if(type == 'F' || type == 'C') valid = TRUE;
		else printf("Invalid ticket type, try again: ");
	}
	
	return type;
}

/**************************************************************************
* getInt() - calls the getString function, upon returning to from the 
* function, the function attempts to convert the string to the variable
* integer. The result is then validated using the endPtr variable. It is
* then tested to be within the range of min and max inclusive. The input is
* then returned to the user. This function is based on the function
* getInteger() from Blackboard in: Course Docs -> Function Examples ->
* Input Validation Examples -> getInteger-basic.c
**************************************************************************/
int get_int(int min, int max){
	char tempStr[MAX_NUM_DIGITS + EXTRA_SPACES];
	int integer, cancel;
	char* endPtr;
	BOOLEAN finished = FALSE;
	
	while(!finished){
		
		/* get a string from getString, the check if the user wants
		   to return to the main menu */
		cancel = get_string(MAX_NUM_DIGITS + EXTRA_SPACES, tempStr);
		DO_WE_RETURN_TO_MENU RETURN_TO_MENU;
		
		/* try to convert the string to an integer of base 10*/
		integer = (int) strtol(tempStr, &endPtr, 10);
		
		/* check to see if the next character after the integer is the \0 */
		if(strcmp(endPtr, "") != 0){
		/* if this block is executed, it means there was a least
		   one character that was not an integer within our string */
			printf("Input was not numeric.\nTry Again: ");
		} 
		/* check to make sure the value is inside the values of max and min */
		else if(integer < min || integer > max){
			printf("Input outside of range %d - %d.\nTry Again: ", min, max);
		} 
		/* if none of the other statements were true, we're done here */
		else{
			finished = TRUE;
		}	

	}
	return integer;
}

/**************************************************************************
* getString() - prompts the user for a string of text up to max characters
* in length. Then checks to see if the user wishes to return to the menu,
* if they do, the function returns the RETURN_TO_MENU constant to its 
* caller. If not, the last character is checked to see if it is the newline
* character, if it isn't, the string is too long. If it isn't too long, the 
* newline character is replaced with the null character to show that this 
* is a C style string. The function then returns TRUE to its caller to show 
* that the function was successful. This function is based on the function 
* getInteger() from Blackboard in: Course Docs -> Function Examples 
* -> Input Validation Examples -> getInteger-basic.c
**************************************************************************/

int get_string(int max, char * string){
    char * cancel;	
	
	while(TRUE){
		cancel = fgets(string, max + EXTRA_SPACES, stdin);
		
		/* if the user presses Ctrl+d or <enter> return the constant
           RETURN_TO_MENU to the caller function until we get to main() */
		if(cancel == NULL|| *string == '\n'){
			return RETURN_TO_MENU;
		} 
		/* otherwise, check to see if the last character is a \n, 
		   if it isn't, the string is longer than the array and
		   therefore outside of the range of characters we're 
		   allowing. So clear the buffer using read_rest_of_line */
		else if(string[strlen(string) - 1] != '\n'){
			printf("Input was too long.\nTry Again: ");
			read_rest_of_line();
		} else {
		/* if the input isn't too long, change the \n for a \0 */
			string[strlen(string) - 1] = '\0';
			return TRUE;
		}
	}
}

/**************************************************************************
* system_free() - free all memory allocated for the tm datastructure.
*
* frees the coin array, then calls free_stock to free up the linked list.
**************************************************************************/
void system_free(tm_type_ptr tm){
	/* free the coins array and call free_stock() because the linked list is a 
       little more complicated to free up */
	free(tm->coins);
	free_stock(tm->stock);
}

