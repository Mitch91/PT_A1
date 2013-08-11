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
	
	clear_array(option_stats, NUM_OPTION_STATS);
	
	while(TRUE){
		dispOptions();
		printf("Select your option: ");
		
		/* get an integer from the user from the range 
		   of the first option to the last */
		option_number = getInt(PERFECT_SQUARES,EXIT);
		
		switch(option_number){
			case PERFECT_SQUARES: 
				printf("\nPerfect Squares\n---------------\n\n");
				printf("Enter a positive integer (%d - %d): ", 
					PERFECT_SQUARES_MIN, PERFECT_SQUARES_MAX);
					
				/* get a number within in the range from the user */
				cancel = getInt(PERFECT_SQUARES_MIN, PERFECT_SQUARES_MAX);
				
				DO_WE_RETURN_TO_MENU	

				/* conduct our analysis */
				perfect_squares(option_stats, cancel);
				break;
			
			case ASCII_TO_BINARY:
				printf("\nASCII to binary gernarator\n--------------------------\n\n");
				printf("Enter a string (%d - %d characters): ", ASCII_MIN, ASCII_MAX);
				
				/* get user's input */
				cancel = getString(ASCII_MAX, ascii);
				
				DO_WE_RETURN_TO_MENU
				
				/* convert input to binary */
				ascii_to_binary(option_stats, ascii);
				break;
				
			case MATCHING_BRACKETS:
				printf("\nMatching Brackets\n-----------------\n\n");
				printf("Enter a string (%d - %d characters): ",
					BRACKETS_MIN, BRACKETS_MAX);
				
				/* get user's input */
				cancel = getString(BRACKETS_MAX, brackets);
				
				DO_WE_RETURN_TO_MENU
				
				/* conduct our analysis */
				matching_brackets(option_stats, brackets);
				break;
			
			case FORMAT_TEXT:
				printf("\nFormatting Text\n---------------\n\n");
				printf("Enter an integer (maximal number of chars per line): ");
				
				cancel = getInt(FORMAT_TEXT_INT_MIN,
					FORMAT_TEXT_INT_MAX);
					
				char_per_line = cancel;
				
				DO_WE_RETURN_TO_MENU
				
				do{
				    printf("Enter some sentences (between %d - %d chars): ",
						FORMAT_TEXT_STR_MIN, FORMAT_TEXT_STR_MAX);
						
					cancel = getString(FORMAT_TEXT_STR_MAX, format);
					DO_WE_RETURN_TO_MENU
					
				} while(strlen(format) < FORMAT_TEXT_STR_MIN); 
				
				DO_WE_RETURN_TO_MENU
				
				format_text(option_stats, char_per_line, format);
				break;
				
			case SESSION_SUMMARY:
				session_summary(option_stats);
				break;
				
			case EXIT:
				return EXIT_SUCCESS;
				
			/*case RETURN_TO_MENU:
				break;*/
		}
	}
}
