/***************************************************************************
* COSC1283/1284 - Programming Techniques
* Semester 2 2013 Assignment #1 
* Full Name        : Mitchell McGregor Elsbury
* Student Number   : s3286283
* Yallara Username : s3286283
* Course Code      : COSC1284
* Program Code     : BP094SEC8
* Start up code provided by Paul Miller and Lin Padgham
***************************************************************************/
#include "assign1.h"

int main(void)
{
	char ascii[ASCII_MAX + EXTRA_SPACES], brackets[BRACKETS_MAX + EXTRA_SPACES];
	char format[FORMAT_TEXT_STR_MAX + EXTRA_SPACES];
    int option_stats[NUM_OPTION_STATS], cancel, char_per_line;
	OPTION option_number;
	
	/* makes sure all the elements in the array are equal to zero */
	clear_array(option_stats, NUM_OPTION_STATS);
	
	while(TRUE){
	
	    /* displays the 6 options */
		dispOptions();
		
		printf("Select your option: ");
		
		/* get an integer from the user from the range 
		   of the first option to the last. We need the
		   +1 because of the offset, PERFECT_SQUARES actually
		   equals zero so that it corresponds to the first 
		   element of the array option_stats */
		option_number = getInt(PERFECT_SQUARES + 1,EXIT + 1);
		
		/* since the actual value of the options has an offset of 1
		   we have to fix our option number to be the same as them */
		   
		option_number--;
		switch(option_number){
			
			/* User has selected Perfect Squares functionality */
			case PERFECT_SQUARES: 
				printf("\nPerfect Squares\n---------------\n\n");
				printf("Enter a positive integer (%d - %d): ", 
					PERFECT_SQUARES_MIN, PERFECT_SQUARES_MAX);
					
				/* get a number within in the range from the user. 'cancel'
				   could be seen as a misleading variable name, but I needed
				   to call it something that would universally make sense
				   since I use it in the DO_WE_RETURN_TO_MENU constant. Also,
				   cancelling the current function and returning to main menu 
				   is one of its functionalities, so its not coming from no 
				   where */
				   
				cancel = getInt(PERFECT_SQUARES_MIN, PERFECT_SQUARES_MAX);
				
				/* check if the user wants to return to menu */
				DO_WE_RETURN_TO_MENU	

				/* conduct our analysis */
				perfect_squares(option_stats, cancel);
				break;
			
			/* User has selected ASCII to binary generator functionality */
			case ASCII_TO_BINARY:
				printf("\nASCII to binary generator\n--------------------------\n\n");
				printf("Enter a string (%d - %d characters): ", ASCII_MIN, ASCII_MAX);
				
				/* get user's input */
				cancel = getString(ASCII_MAX, ascii);
				
				/* check if the user wants to return to menu */
				DO_WE_RETURN_TO_MENU
				
				/* convert input to binary */
				ascii_to_binary(option_stats, ascii);
				break;
				
			/* User has selected Matching Brackets functionality */	
			case MATCHING_BRACKETS:
				printf("\nMatching Brackets\n-----------------\n\n");
				printf("Enter a string (%d - %d characters): ",
					BRACKETS_MIN, BRACKETS_MAX);
				
				/* get user's input */
				cancel = getString(BRACKETS_MAX, brackets);
				
				/* check if the user wants to return to menu */
				DO_WE_RETURN_TO_MENU
				
				/* conduct our analysis */
				matching_brackets(option_stats, brackets);
				break;
			
			/* User has selected Formatting Text functionality */
			case FORMAT_TEXT:
				printf("\nFormatting Text\n---------------\n\n");
				printf("Enter an integer (maximal number of chars per line): ");
				
				cancel = getInt(FORMAT_TEXT_INT_MIN,
					FORMAT_TEXT_INT_MAX);
					
				char_per_line = cancel;
				
				/* check if the user wants to return to menu */
				DO_WE_RETURN_TO_MENU
				
				do{
				    printf("Enter some sentences (between %d - %d chars): ",
						FORMAT_TEXT_STR_MIN, FORMAT_TEXT_STR_MAX);
						
					cancel = getString(FORMAT_TEXT_STR_MAX, format);
					
					/* check if the user wants to return to menu */
					DO_WE_RETURN_TO_MENU
					
				} while(strlen(format) < FORMAT_TEXT_STR_MIN); 
				
				/* check if the user wants to return to menu */
				DO_WE_RETURN_TO_MENU
				
				/* format the text */
				format_text(option_stats, char_per_line, format);
				break;
			
			/* User has selected Session summary functionality */
			case SESSION_SUMMARY:
				session_summary(option_stats);
				break;
			
			/* User wishes to exit */
			case EXIT:
				return EXIT_SUCCESS;
			
			/* if the user just hits enter, the program acts like
			   it has returned to the menu. i.e. it displays the
			   menu etc. */
			case RETURN_TO_MENU:
				break;
		}
	}
}
