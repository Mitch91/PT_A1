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

/*char * integer_to_binary(int integer){}*/

void dispOptions(void){
	printf("\nMain Menu\n---------\n1) Perfect Squares\n2) ASCII to Binary Generator\n");
	printf("3) Matching Brackets\n4) Formatting Text\n5) Session Summary\n6) Exit\n\n");
}

/*********************************************************************************
* getInt() - prompts the user for an integer of len input. Removes the newline 
* character \n and replaces it with the null character \0 then attempting to 
* convert the string to the variable integer. The result is then validated using
* the endPtr variable. It is then tested to be within the range of min and max 
* inclusive. The input is then returned to the user. This function is based on the
* function getInteger() from Blackboard in: Course Docs -> Function Examples -> 
* Input Validation Examples -> getInteger-basic.c
**********************************************************************************/
int getInt(int min, int max){
	char tempStr[MAX_NUM_DIGITS + EXTRA_SPACES];
	int integer = 0;
	char* endPtr;
	BOOLEAN finished = FALSE;
	while(!finished){
		fgets(tempStr, MAX_NUM_DIGITS + EXTRA_SPACES, stdin);
		
		/* if the user presses Ctrl+d or <enter> return to the menu */
		if(*tempStr == EOF || *tempStr == '\n'){
			return RETURN_TO_MENU;
		} 
		/* otherwise, check to see if the last character is a \n 
		   if it isn't, the string is longer than the array and
		   therefore outside of the range of characters we're 
		   allowing */
		else if(tempStr[strlen(tempStr) - 1] != '\n'){
			printf("Input was too long.\nTry Again: ");
			read_rest_of_line();
		} else{
			/* if the input isn't too long, change the \n for a \0 */
			tempStr[strlen(tempStr) - 1] = '\0';
			
			/* try to convert the string to an integer */
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
	}
	return integer;
}
