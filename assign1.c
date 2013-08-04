/***************************************************************************
* COSC1283/1284 - Programming Techniques
* Semester 2 2013 Assignment #1 
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Yallara Username : EDIT HERE
* Course Code      : EDIT HERE
* Program Code     : EDIT HERE
* Start up code provided by Paul Miller and Lin Padgham
***************************************************************************/
#include "assign1.h"

int main(void)
{
    int option_stats[NUM_OPTION_STATS];
	unsigned number;
	OPTION option_number;
	while(TRUE){
		dispOptions();
		printf("Select your option: ");
		
		/* get an integer from the user from the range 
		   of the first option to the last */
		option_number = getInt(PERFECT_SQUARES,EXIT);
		
		switch(option_number){
			case PERFECT_SQUARES: 
				printf("Enter a positive integer (%d - %d): ", 
					PERFECT_SQUARES_MIN, PERFECT_SQUARES_MAX);
					
				/* get a number within in the range from the user */
				number = getInt(PERFECT_SQUARES_MIN, PERFECT_SQUARES_MAX);
				if(number == RETURN_TO_MENU) break;
				/* conduct our analysis */
				perfect_squares(option_stats, number);
				break;
			
			case ASCII_TO_BINARY:
				printf("Ascii\n");
				break;
				
			case MATCHING_BRACKETS:
				printf("brackets\n");
				break;
			
			case FORMATTED_TEXT:
				printf("formatted text\n");
				break;
				
			case SESSION_SUMMARY:
				printf("summary\n");
				break;
				
			case EXIT:
				return EXIT_SUCCESS;
				
			default:
				printf("invalid\n");
		}
	}
}
