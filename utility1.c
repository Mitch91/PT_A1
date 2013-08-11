/***************************************************************************
* COSC1283/1284 - Programming Techniques
* Semester 2 2013 Assignment #1 
* Full Name        : Mitchell McGregor Elsbury
* Student Number   : s3286283
* Yallara Username : s3286283
* Course Code      : COSC1284
* Program Code     : BP094SEC8
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
* integer_to_binary() - converts an integer to its binary representation
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
* clear_array() - changes all the elements of the array to zero, where size
* is the size of the array
**************************************************************************/

void clear_array(int * array, unsigned size){
	int i;
	for(i = 0; i < size; i++){
		array[i] = 0;
	}
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
        char * cancel;	
	while(TRUE){
		cancel = fgets(string, max + EXTRA_SPACES, stdin);
		/* if the user presses Ctrl+d or <enter> return the constant
           RETURN_TO_MENU to the caller function until we get to main() */
		if(cancel == NULL|| *string == '\n'){
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
/**************************************************************************
* analyse_string() - this function is used to find the number of words in
* string as well as the number of characters in the largest word. These 
* results are passed back the the caller through an int pointer, which 
* point to an array containing the information needed.
**************************************************************************/

void analyse_string(char * text, int * info){
	char * ptr = strtok(text, " ");
	
	info[0] = 0; /* info[0] contains the length of the longest word */
	info[1] = 0; /* info[1] contains the number of words in the string */
	while(ptr != NULL){
		info[1]++; 
		if(strlen(ptr) > info[0]) info[0] = strlen(ptr);
		ptr = strtok(NULL, " ");
	}
	
}

/**************************************************************************
* tokenise_string() - takes in three parameters, a char array, an array
* char arrays and the delimeter. It then toknises text around the delimeter
* and stores each token in the array words. 
**************************************************************************/

void tokenise_string(char * text, char ** words, char * delims){
	int i = 0;
	words[i] = strtok(text, delims);
	i++;
	
	
	while(words[i - 1] != NULL){
		words[i] = strtok(NULL, delims);
		i++;
	}
}

/**************************************************************************
* format_line() - takes in two parameters, the line to be formatted and the
* width which that line should be. The function then adds spaces to make
* the line the width it needs to be.
**************************************************************************/

void format_line(char * line, int width, int words_in_line){
	int i, j, left_over_space, even_spacing, uneven_spacing;
	char * word, * formatted_line, *head;
	
	/*printf("Line: %s", line); 
	printf("words in line: %d\n",words_in_line);
	printf("width: %d\n",width);*/
	
	formatted_line = malloc(width + EXTRA_SPACES);
	head = formatted_line;
	
	left_over_space = width - strlen(line);
	
	/* if there's only 1 word on the line, we need a special case. 
	   The main reason why is because we would be trying to divide
	   by zero when we use the % operand which gives a floating 
	   exception */
	if(words_in_line == 1){
		strcpy(formatted_line, line);
		formatted_line += strlen(line);
		
		for(i = 0; i < left_over_space; i++){
			*formatted_line = SPACE;
			formatted_line++;
		}
	} else {
		/* even_spacing is how many spaces there are between each word */
		even_spacing = left_over_space / (words_in_line - 1);
		
		/* uneven_spacing is the amount of spaces left over when each word
		   is spaced evenly */
		uneven_spacing = left_over_space % (words_in_line - 1);
		
		
		word = strtok(line, " ");
		for(j = 0; j < words_in_line; j++){
			
			strcpy(formatted_line, word);
			
			if(j == words_in_line - 1) break;
			
			formatted_line += strlen(word);
			*formatted_line = SPACE;
			formatted_line++;
				
			for(i = 0; i < even_spacing; i++){
				*formatted_line = SPACE;
				formatted_line++;
			}
			
			if(uneven_spacing){
				*formatted_line = SPACE;
				formatted_line++;
				uneven_spacing--;
			} 
			
			word = strtok(NULL, " ");
			
		}
	}
	printf("%s\n", head);
	formatted_line = head;
	free(formatted_line);
}










