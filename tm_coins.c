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

#include "tm_coins.h"

/* add functions here for the manipulation of the coins list (array) */

/***************************************************************************
* load_coins() - loads the contents of the file pointed to by fp into 
* file_contents, then seperates the contents in to lines which is stored in
* the variable lines. Each line is then tokenised into tokens, and store 
* them in the coins array. If anything goes wrong, return FALSE
***************************************************************************/

BOOLEAN load_coins(coin_list_ptr coins, FILE * fp){
	char * file_contents, ** lines, * temp, * token;
	int denom, i = 0, j, k;
	
	/* stores the contents of fp within file_contents */
	put_file_contents(file_contents,fp);
		
	/* separate the file into lines */
	if(!(lines = calloc(NUM_COINS, sizeof(token)))){
		printf("Unable to allocate memory for lines variable in function "
			"load_coins\n");
		return FALSE;
	}
	
	/* start tokenising file contents into separate lines */
	lines[i] = strtok(file_contents, LINE_DELIMS);
	for(i = 1;; i++){
		temp = strtok(NULL, LINE_DELIMS);
		/*if there are no more tokens and i equals 6, i.e. we have read
		  in 6 lines, break */
		if(!temp && i == NUM_COINS) break;
		else if((!temp && i != NUM_COINS) || (temp != NULL && i == NUM_COINS)){
			/* if either of these conditions are satisfied, the file is not formatted
			   correctly */
			incorrect_format("Coins");
		}
		lines[i] = temp;
	}
		
	/* separate each line into tokens and pass the values to the coin struct */
	for(i = 0; i < NUM_COINS; i++){
	
		/* the loop caters for 2 different scenarios within the one loop.
		   The two scenarios are where strtok's first arg is the string
		   and we want to store the token within coins->denomination and
		   the second scenario is where strtok's first arg is NULL and
		   we want to store the token in coins->count. */
		for(j = 0; j < NUM_COIN_TOKENS; j++){
			if(!j) temp = lines[i];
			else temp = NULL;
			
			token = strtok(temp,TOKEN_DELIMS);
			
			/* if token is null here there are too few tokens */
			if(!token){
				incorrect_format("Coins");
			}
			
			/* if the first character after the comma is a space, or the first
		       character of this token is a space the file is formatted incorrectly */
			if(*(token + strlen(token) + 1) == ' ' || *token == ' '){
				incorrect_format("Coins");
			}
			
			/* first iteration, our token is the denomination, second iteration its
			   the count. Note that we can use k from our previous iteration in the 
			   else statement */
			if(!j) denom = strtol(token, &temp, BASE_TEN);
			else coins[k].count = strtol(token, &temp, BASE_TEN);
			
			/* check to make sure that the value of token was numeric */
			if(strcmp(temp,"")){
				incorrect_format("Coins");
			}
			
			/* based on the value we read, assign a value to k. This way five cents 
			   will always be in tm->coins[5] rather than being dependent on the
			   order the coins were read in */
			switch(denom){
				case FIVE_CENTS:
					k = 5;
					break;
				case TEN_CENTS:
					k = 4;
					break;
				case TWENTY_CENTS:
					k = 3;
					break;
				case FIFTY_CENTS:
					k = 2;
					break;
				case ONE_DOLLAR:
					k = 1;
					break;
				case TWO_DOLLARS:
					k = 0;
					break;
			}
			
			coins[k].denomination = denom;
			
			/* if this is our second iteration, check to make sure there 
			   is no third token */
			if(j){
				if((token = strtok(NULL,TOKEN_DELIMS))){
					incorrect_format("Coins");
				}
			}
		}
	}
	free(lines);
	free(file_contents);
	return TRUE;
}

/***************************************************************************
* give_change() - depending on the coins in the machine and the coins the 
* user just inserted give them the change they require in the order of 
* highest denomination first. If no change required, notify the user.
***************************************************************************/

void give_change(struct coin * coins, stock_node * ticket, int * coins_inserted,
	int change){
	
	int i, j, whole_change_amount = change, change_given[NUM_COINS];
	int total_coins[NUM_COINS];
	
	/* calculate the total number of coins we have at our dispense */
	for(i = 0; i < NUM_COINS; i++) {
		total_coins[i]=coins[i].count + coins_inserted[i];
		change_given[i] = 0;
	}
	
	/* there is more change, find the coin of the highest denomination that is lower
	   than change then check if we have any left. Then minus one from the coins we 
	   have and plus one to the coins we are to give the user. Finally, minus the 
	   value of the coin from change */
	while(change){
		if(change >= TWO_DOLLARS && total_coins[0] > 0) {
			total_coins[0]--;
			change_given[0]++;
			change -= TWO_DOLLARS;
		} else if(change >= ONE_DOLLAR && total_coins[1] > 0){
			total_coins[1]--;
			change_given[1]++;
			change -= ONE_DOLLAR;
		} else if(change >= FIFTY_CENTS && total_coins[2] > 0){
			total_coins[2]--;
			change_given[2]++;
			change -= FIFTY_CENTS;
		} else if(change >= TWENTY_CENTS && total_coins[3] > 0){
			total_coins[3]--;
			change_given[3]++;
			change -= TWENTY_CENTS;
		} else if(change >= TEN_CENTS && total_coins[4] > 0){
			total_coins[4]--;
			change_given[4]++;
			change -= TEN_CENTS;
		} else if(change >= FIVE_CENTS && total_coins[5] > 0){
			total_coins[5]--;
			change_given[5]++;
			change -= FIVE_CENTS;
		} else{
			/* we reach here, we've run out of coins of the right denominations */
			printf("Do not have enough or the right coins to give change."
					"Unable to sell ticket, sorry for the inconvenience."
					"Try again with the correct change, or press enter to return "
					"to the main menu.");
					return;
			
		}
	}
	
	/* print out the ticket info */
	printf("Thankyou for purchasing a %s ", ticket->data->ticket_name);
	if(ticket->data->ticket_type == 'F') printf("full fare");
	else printf("concession");
	printf(" zone %s ticket.\n",ticket->data->ticket_zone);
	
	/* change now equals zero, so we need a copy if change wasn't zero, print the 
	   change we're giving them. If there is no change to give, tell the user no
       is needed. */
	if(whole_change_amount){
		/* print the total amount of the change */
		printf("Your change is: ");
		print_dollar_format(whole_change_amount,3);
		printf(".\nYour change coins are: ");
	
		/* iterate through all the coins and print out a coin of that denomination
           was given according to change_given */
		for(i = 0; i < NUM_COINS; i++){
			j = change_given[i];
			coins[i].count = total_coins[i];
			
			for(; j > 0; j--){
				/* if the denomination is larger or equal to a dollar print the
				   value in dollar format, otherwise print it in cent format */
				if(coins[i].denomination >= 100) 
					printf("$%d ",coins[i].denomination/100);
				else printf("%dc ",coins[i].denomination);
			}
		}

	} else 
		printf("Correct amount given, no change needed.");
	printf("\n\n");
	return;
}

/***************************************************************************
* save_coins() - writes the coin data from the array to the file pointed to
* by fp (coinsfile).
***************************************************************************/

BOOLEAN save_coins(struct coin * coins, FILE * fp){
	int i;
	char * line = malloc(COINS_FILE_MAX_LINE_LENGTH + 1);
	/* check line was malloc'd properly and the file was opened properly */
	if(!line) return FALSE;
	else if(!fp){
		free(line);
		return FALSE;
	}
	
	/* store the values for the particular coin in the line in the correct format
       then write the line to the file */
	for(i = NUM_COINS - 1; i >= 0; i--){
		sprintf(line, "%d,%d\n",coins[i].denomination,coins[i].count);
		fputs(line, fp);
	}
	fclose(fp);
	free(line);
	return TRUE;
}