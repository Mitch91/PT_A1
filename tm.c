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
/**************************************************************************
* main() - this is the entry point into your program. You need to follow 
* the steps in the comments provided as these are the steps required to 
* run your program. Please ensure that you use all function prototypes and 
* datatype declarations provided as not doing so will result in a 
* substantial mark penalty as well as missing out on some important learning
* opportunities.
**************************************************************************/
#include "tm.h"

int main(int argc, char** argv)
{
    tm_type tm;
	OPTION option_number;
    BOOLEAN quit = FALSE;

    /* check command line arguments */
	if(argc != NUM_ARGS){
		fprintf(stderr,
		"Error: incorrect number of input arguments. Program is exiting\n");
		return EXIT_FAILURE;
	}

    /* initialise data structures */
	if(!system_init(&tm))
		return EXIT_FAILURE;
	
    /* load data. If it fails, free the data that was allocated and quit.*/
	if(!load_data(&tm,argv[1],argv[2])){
		system_free(&tm);
		return EXIT_FAILURE;
	}
    /* test that everything has gone in initialisation and loading */
		
    while(!quit)
    {
		/* display menu and get user's choice*/
		option_number = get_user_choice();
		
		/* perform menu choice */
		switch(option_number){
			case PURCHASE_TICKET:
				purchase_ticket(&tm);
				break;
				
			case DISPLAY_TICKET:
				display_tickets(&tm);
				break;
				
			case ADD_TICKET:
				add_ticket(&tm);
				break;
				
			case REMOVE_TICKET:
				delete_ticket(&tm);
				break;
				
			case DISPLAY_COINS:
				display_coins(&tm);
				break;
				
			case RESTOCK_TICKETS:
				restock_tickets(&tm);
				break;
				
			case RESTOCK_COINS:
				restock_coins(&tm);
				break;
			
			/* In the cases of SAVE_EXIT and ABORT, we want to set quit to TRUE
			   so SAVE_EXIT doesn't get a break */
			case SAVE_EXIT:
				save_data(&tm,argv[1],argv[2]);
			case ABORT:
				quit = TRUE;
				break;
				
			default:
				break;
		}
        

    }

    /* free memory */
	system_free(&tm);
	
    /* leave program */
	return EXIT_SUCCESS;
}
