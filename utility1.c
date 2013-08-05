/***************************************************************************
* COSC1283/1284 - Programming Techniques
* Semester 2 2013 Assignment #1 
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Yallara Username : EDIT HERE
* Course Code      : EDIT HERE
* Program Code     : EDIT HERE
* Start up code provided by Paul Miller and Padgham
***************************************************************************/
#include "assign1.h"

/**************************************************************************
* read_rest_of_line() - clear the buffer of any leftover input. Call this 
* function whenever you detect leftover input in the buffer.
**************************************************************************/
void read_rest_of_line(void)
{
    int ch;
    /* read characters one at a time from standard input until there are
     * no characters left to read
     */
    while (ch=getc(stdin), ch!=EOF && ch!='\n');
    /* reset the error status of the input FILE pointer */
    clearerr(stdin);
}

/**************************************************************************
* integer_to_biunary() - converts an integer to its binary representation
* then stores the value in a C style string. The algorithm tests if integer
* is larger than the current_bit, if it is, the value of current_bit is 
* subtracted from integer and a 1 is placed at the position of the bit 
* value. If integer is not larger than current_bit, a 0 placed at that 
* position. The current bit is then divided by 2 and the pointer moves to
* the next bit position
**************************************************************************/  
void integer_to_binary(int integer, char* binary){
	int current_bit = MSB;
	char *ptr;
	ptr = binary;
		
	/* lsb is equal to 1, if we then divide 1 by 2 where 1 is an
       integer, we get zero. Making the statement false */
	while(current_bit){
		if(integer >= current_bit){
			*ptr = '1';
			integer -= current_bit;
		} else{
			*ptr = '0';
		}
		current_bit /= 2;
		ptr++;
	}
	*ptr = '\0';
}

void dispOptions(void){
	printf("\nMain Menu\n---------\n1) Perfect Squares\n2) ASCII to Binary Generator\n");
	printf("3) Matching Brackets\n4) Formatting Text\n5) Session Summary\n6) Exit\n\n");
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
int getInt(int min, int max){
	char tempStr[MAX_NUM_DIGITS + EXTRA_SPACES];
	int integer = 0, cancel;
	char* endPtr;
	BOOLEAN finished = FALSE;
	while(!finished){
		cancel = getString(MAX_NUM_DIGITS + EXTRA_SPACES, tempStr);
		if(cancel == RETURN_TO_MENU) return RETURN_TO_MENU;
		/* try to convert the string to an integer of base 10*/
		integer = (int) strtol(tempStr, &endPtr, 10);
		
		/* check to see if the next character after the integer is the \0 */
		if(strcmp(endPtr, "") != 0){
			printf("Input was not numeric.\nTry Again: ");
		} 
		/* check to make sure the value is inside the values of max and min */
		else if(integer < min || integer > max){
			printf("Input outside of range %d - %d.\nTry Again: ", min, max);
		} else{
			finished = TRUE;
		}		
	}
	return integer;
}

/**************************************************************************
* getString() - prompts the user for a string of text up to max characters
* in length. Then checks to see if the user wishes to return to the menu,
* if they do, the function returns the RETURN_TO_MENU constant to its 
* caller. If not, the last character is check if it is the newline
* character, if it isn't, the string is too long. Then the newline 
* character is replaced with the null character to show that this is a C 
* style string. The function then returns 1 to its caller to show that the 
* function was successful. This function is based on the function 
* getInteger() from Blackboard in: Course Docs -> Function Examples 
* -> Input Validation Examples -> getInteger-basic.c
**************************************************************************/

int getString(int max, char * string){	
	while(TRUE){
		fgets(string, max + EXTRA_SPACES, stdin);
		/* if the user presses Ctrl+d or <enter> return to the menu */
		if(*string == EOF || *string == '\n'){
			return RETURN_TO_MENU;
		/* otherwise, check to see if the last character is a \n 
		   if it isn't, the string is longer than the array and
		   therefore outside of the range of characters we're 
		   allowing */
		} else if(string[strlen(string) - 1] != '\n'){
			printf("Input was too long.\nTry Again: ");
			read_rest_of_line();
		} else {
		/* if the input isn't too long, change the \n for a \0 */
			string[strlen(string) - 1] = '\0';
			return 1;
		}
	}
}
