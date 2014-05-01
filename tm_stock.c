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

#include "tm_stock.h"

/* add functions here to manipulate the stock list */
/***************************************************************************
* load_stock() - loads the contents of the file pointed to by fp into 
* file_contents, then makes a copy. Each line is then stored in a variable
* lines. Since the length of a line in the stock file can vary so much, we
* don't use calloc here so that we don't waste space also, we don't know 
* how many lines there are. 
***************************************************************************/

BOOLEAN load_stock(stock_list_ptr stock, FILE * fp){
	char * file_contents, * copy, ** lines, * token, * temp;
	char * name, type, * zone;
	unsigned int price, stock_level;
	int i, j, check, num_lines = NUM_LINES_GUESS;

	/* stores the contents of fp within file_contents */
	
	put_file_contents(file_contents,fp);
	if(!(copy = malloc((get_file_size(fp) + 1)))){
		free(file_contents);
		printf("Unable to allocate enough memory for copy variable\n");
		return FALSE;
	}
	/* since we're using strtok, we need a copy */
	strcpy(copy, file_contents);
	 
	if(!(lines = malloc(num_lines * sizeof(token)))){
		free(copy);
		free(file_contents);
		printf("Unable to allocate enough memory for lines variable\n");
		return FALSE;
	}
	/* initalise all values of lines to NULL */
	for(i = 0; i < num_lines; i++) lines[i] = NULL;
	
	/* if tokenise_stock_lines() returns false, then num_lines isn't large enough.
	   So copy file_contents to copy again (since copy was destroyed in 
	   tokenise_stock_lines(). Double the number of lines we allow for and allocate
	   a new bigger block of memory that is big enough to hold the number of lines */
	while(!(check = tokenise_stock_lines(lines, copy, num_lines))){
		strcpy(copy, file_contents);
		num_lines *= 2;
		lines = realloc(lines, num_lines * sizeof(token) );
		for(i = 0; i < num_lines; i++) lines[i] = NULL;
	}
	
	/* this is why all lines in lines need to be initialised, valgrind doesn't like
       it if you free uninitialized memory. In the event that when we malloc'd or 
	   realloc'd we reallocated too many lines, this frees the ones we don't need */
	for(i = check; i < num_lines; i++) free(lines[i]);
	
	/* tokenise_stock_lines() returns the number of lines in file_contents if FALSE
	   isn't returned */
	num_lines = check;
	for(i = 0; i < num_lines; i++){
		for(j = 0; j < NUM_STOCK_TOKENS; j++){
			
			if(!j) token = strtok(lines[i], TOKEN_DELIMS);
			else token = strtok(NULL, TOKEN_DELIMS);
						
			/* if token is NULL here something is wrong */
			if(!token) {
				printf("Too few variables on line %d\n",i);
				free(copy);
				incorrect_format("Stock");
			}
			
			/* depending on the value of j, depends if we are reading the first,
			   second, third, fourth or fifth token of the line. validate_<data field> 
			   are all macros to validate their respective variables. They 
			   compartmentalise the code and also helps with readability */
			switch(j){
				case 0:
					validate_ticket_name(token)
					name = token;
					break;
				case 1:
					validate_ticket_type(token)
					type = *token;
					break;
				case 2:
					validate_ticket_zone(token)
					zone = token;
					break;
				case 3:
					/* in cases 3 and 4, the assignment is done within the macro
    				   since we use strtol and then still need to do checks after the assignment */
					validate_ticket_price(token)
					break;
				case 4:
					if(strtok(NULL,TOKEN_DELIMS)){
						printf("Too many values on line %d\n",i);
						incorrect_format("Stock");
					}
					validate_stock_level(token)
					/* add_stock_node returns FALSE then we had some malloc issues */
					if(!add_stock_node(stock, name, type, zone, price, stock_level)){
						printf("Unable to add stock node, not enough memory."
							" Exiting program\n");
						free(lines);
						free(copy);
						free(file_contents);
						return FALSE;
					}
					break;
				
			}
		}
	}
	
	free(lines);
	free(copy);
	free(file_contents);
	
	return TRUE;
}

/*****************************************************************************
* add_stock_node() - allocates memory for a new node, assigns the parameters
* of the function to the data members of the new node and places the stock 
* within the stock list alphabetically (case sensitive, dependent on the value 
* returned by strcmp())
*****************************************************************************/

BOOLEAN add_stock_node(stock_list_ptr stock, char * name, char type, char * zone, 
	unsigned int price, unsigned int stock_level){
	
	/* Allocate memory for the new node */
	stock_node * new_node = malloc(sizeof(stock_node)), * comparing_node, * node_infront;
	/* memory checks */
	if(!new_node){
		printf("Unable to allocate memory for a new stock node\n");
		return FALSE;
	}
	if(!(new_node->data = malloc(sizeof(struct stock_data)))){
		free(new_node);
		printf("Unable to allocate memory for stock node's data\n");
		return FALSE;
	}
	
	/* transfer data into the node's members */
	strcpy(new_node->data->ticket_name, name);
	new_node->data->ticket_type = type;
	strcpy(new_node->data->ticket_zone, zone);
	new_node->data->ticket_price = price;
	new_node->data->stock_level = stock_level;
	
	/* The first node we want to compare is the head of the stock */
	comparing_node = stock->head_stock;
	
	/* If the head of the stock is NULL, i.e. new_node is the first node to be 
	   added */
	if(!comparing_node){
		stock->head_stock = new_node;
		stock->head_stock->next_node = NULL;
	} else if(strcmp(comparing_node->data->ticket_name,new_node->data->ticket_name) > 0){
			/* If the second node comes first alphabetically */
			new_node->next_node = stock->head_stock;
			stock->head_stock = new_node;
	} else {
		while(comparing_node){
			/* node_infront is the node that's 'infront' of the node we
			   are currently comparing to new_node. We will need it because 
			   new_node will be node_infront's next_node */
			   
			node_infront = comparing_node;
			comparing_node = comparing_node->next_node;
			
			/* If comparing_node is NULL, then node_infornt was the last node in 
			   the list and we just have to assign new_node as its next_node 
			   we don't need a break here because comparing_node is equal to 
			   NULL to the while condition will take care of that */
			   
			if(!comparing_node){
				new_node->next_node = node_infront->next_node;
				node_infront->next_node = new_node;
			} else if(strcmp(comparing_node->data->ticket_name,new_node->data->ticket_name) > 0){
				/* If new_node comes first alphabetically and none of the other cases
				   apply */
				
				new_node->next_node = comparing_node;
				node_infront->next_node = new_node;
				break;
			}
		}
	}
	
	stock->num_stock_items++;
	return TRUE;
}

/***************************************************************************
* delete_stock_node() - deletes a node from the stock list and links the
* nodes surrounding the node to be deleted to together so that we still
* have a working linked list
***************************************************************************/

void delete_stock_node(stock_list_ptr stock, stock_node * ticket){
	
	stock_node * node = stock->head_stock;
	/* if the ticket we want to delete is head_stock our job is a lot easier */
	if(ticket == node){
		stock->head_stock = node->next_node;
		return;
	}
	
	/* otherwise loop through the list to find the node we want and free it */
	while(node){ 
		if(node->next_node == ticket){
			node->next_node = node->next_node->next_node;
			free(ticket->data);
			free(ticket);
			return;
		}
		node = node->next_node;
	}
}

/***************************************************************************
* choose_ticket() - the entry point for the 3 functions that require 
* the user to enter information about a ticket. Gets the info, then
* on the variable mode, depends what function is called or what value is 
* returned 
***************************************************************************/

stock_node * choose_ticket(stock_list_ptr stock, char mode){
	stock_node * ticket;
	char name[TICKET_NAME_LEN], type, zone[TICKET_ZONE_LEN];
	int cancel, price;
	
	/* get all the info we need from the user, depending on the mode depends on what
	   variables we actually need */
	do{
		printf("Enter a ticket name (1-%d characters): ",TICKET_NAME_LEN);
		cancel = get_string(TICKET_NAME_LEN,name);
		DO_WE_RETURN_TO_MENU NULL;
		
		printf("Ticket type (1 character): ");
		type = get_ticket_type();
		if(type == '\n') return NULL;
		
		printf("Ticket zone (1-3): ");
		cancel = get_string(TICKET_ZONE_LEN,zone);
		DO_WE_RETURN_TO_MENU NULL;
		
		/* if we're in mode a for add, the ticket wont exist so get_ticket will
		   always return FALSE so we break here */
		if(mode == 'a') break;
		
		/* otherwise, check to see if the ticket exists, if not loop again */
	} while(!(ticket = get_ticket(stock,name,type,zone)));
	
	/* if we're purchasing a ticket, we're done here */
	if(mode == 'p') return ticket;
	else if(mode == 'a'){
	
		/* if we're adding a ticket, get the ticket price, do the necessary checks
		   pass it to add_stock_node */
		printf("\nPrice (in cents): ");
		price = get_int(1, MAX_TICKET_PRICE);
		if(price == RETURN_TO_MENU) return NULL;
		add_stock_node(stock, name, type, zone, price, DEFAULT_STOCK_LEVEL);
		
		/* print the info about the ticket that was just added */
		print_ticket_info("added");
		
		/* choose_ticket requires a return type but we don't care about that 
		   unless we're in 'p' mode, so we just return NULL */
		return NULL;
		
	} else{
		/* delete the chosen ticket, print the info and return NULL */ 
		delete_stock_node(stock,ticket);
		print_ticket_info("removed");
		return NULL;
	}
}

/***************************************************************************
* get_ticket() - gets the ticket with the name, type and zone specified in 
* the parameters. If the ticket doesn't exist, the user is notified and 
* NULL is returned
***************************************************************************/

stock_node * get_ticket(stock_list_ptr stock, char * name, char type, char * zone){
	stock_node * comparing_node = stock->head_stock;
	
	/* loops through all the nodes, searching for the node with the correct name, 
	   type and zone */
	while(comparing_node){
		if(!strcmp(comparing_node->data->ticket_name,name) &&
			comparing_node->data->ticket_type == type &&
			!strcmp(comparing_node->data->ticket_zone,zone)){
				return comparing_node;
		}
		
		comparing_node = comparing_node->next_node;
	}
	/* if we reach here we've gone through the whole list without a match so it
	   mustn't exist */
	printf("Ticket does not exist, try again. Press Enter to quit\n");
	return NULL;
}

/***************************************************************************
* free_stock() - this function is called by system_free to free up the 
* linked list of tickets.
***************************************************************************/

void free_stock(stock_list_ptr stock){
	stock_node * head = stock->head_stock, * freeing_node;
	
	/* while there's more nodes, assign freeing node to the current node and assign
       the head to the next node, free the current node and repeat */
	while(head){
		freeing_node = head;
		head = head->next_node;
		free(freeing_node->data);
		free(freeing_node);
	}
	free(stock);
}

/***************************************************************************
* save_stock() - this function is called by save_exit() and is used to write
* the data to the file pointed to by fp (the stockfile)
***************************************************************************/

BOOLEAN save_stock(struct stock_list * stock, FILE * fp){
	char * line = malloc(STOCK_FILE_MAX_LINE_LENGTH);
	stock_node * node = stock->head_stock;
	
	/* test if malloc worked, also test if the file was opened properly */
	if(!line) return FALSE;
	else if(!fp){
		free(line);
		return FALSE;
	}
	
	/* put the node in a string in the required format then write that string to the
       file. Then go to the next node and start again */
	while(node){
		sprintf(line,"%s,%c,%s,%d,%d\n",node->data->ticket_name,
		node->data->ticket_type,node->data->ticket_zone,node->data->ticket_price,
		node->data->stock_level);
		fputs(line, fp);
		node = node->next_node;
	}
	fclose(fp);
	free(line);
	return TRUE;
}