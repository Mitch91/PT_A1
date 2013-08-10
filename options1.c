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
/***************************************************************************
* This source file contains important functions to be developed and
* used by various menu options, as indicated. Note that every
* function has as its first parameter the optionsStats array, which
* will be appropriately updated for later reporting of menu option 6.
* You may ignore this parameter and its relevance to each function
* until you develop the sessionSummary() function.
 **************************************************************************/

/**************************************************************************
* perfect_squares() - implements the "Perfect Squares" option (requirement 
* 2) from the main menu. You need to determine whether the number passed
* in is a perfect square and let the user know if it is or not. You also
* need to print the perfect square before and after this value. Finally
* you need to update the option_stats variable appropriately.
*
* function finds the square root of number, then tests to see if it is a 
* whole number or not. from there the lower and upper roots are calculated
* so that their respective perfect squares can be calculated.
**************************************************************************/

void perfect_squares(int * option_stats, unsigned number){
	float root = sqrt (number);
	unsigned lower_root, upper_root;
	
	/*if root is a whole number */
	if(root == (int) root){
		lower_root = root - 1;
		upper_root = root + 1;
		
		printf("%d is a perfect square.\n", number);
	} else{
		lower_root = (int) root;
		upper_root = lower_root + 1;
		
		printf("%d is not a perfect square.\n",number);
	}
	
	printf("Perfect square before: %d.\n",lower_root*lower_root);
	printf("Perfect square after: %d.\n", upper_root*upper_root);
	
	option_stats[PERFECT_SQUARES]++;
}

/**************************************************************************
* ascii_to_binary() - implements the "ASCII to Binary Generator" option
* (requirement 3) from the main menu. Essentially, you need to implement
* an algorithm for conversion of integers to binary and apply this to 
* every character in the input array (called 'ascii' here) and print out
* the result. Finally, you need to update the option_stats array 
* appropriately 
*
* function loops through each character, and passing their ascii value to 
* the function integer_to_binary(), which finds the binary representation
* of a integer and returns it in the char array of the second argument
**************************************************************************/
void ascii_to_binary(int * option_stats, char * ascii){
	int i, ascii_value, len = strlen(ascii);
	/* +1 for the \0 characters */
	char binary[8 + 1];
	
	printf("Binary representation: ");
	
	for(i = 0; i < len; i++){
		ascii_value = *ascii;
		integer_to_binary(ascii_value, binary);
		printf("%s ",binary);
		ascii++;
	}
	option_stats[ASCII_TO_BINARY]++;
	printf("\n");
}

/**************************************************************************
* matching_brackets() - implements the "Matching Brackets" option 
* (requirement 4) from the main menu. You need to implement an algorithm 
* which will parse a string passed in and determine whether the brackets 
* all match, including the type of brackets. You need to account for 
* {} [] () and you also need to allow for the nesting of brackets. 
* You need to tell the user whether the brackets match or not. Finally you
* need to update the option_stats array appropriately.
*
* function loops through all the characters of the test_string storing the
* open bracket types in open_brackets, then if the next closing bracket
* is the corresponding brackets for that set, then the array focuses on
* the next tier outside the just closed brackets. If the closing bracket 
* is not the corresponding bracket of the most recently opened brackets
* then the functions tells the user the brackets do not match. If the 
* function gets to the end of the string and there are no open brackets
* left in the array, then the user is informed that the brackets do match.
**************************************************************************/
void matching_brackets(int * option_stats, char * test_string){
	int j = 0, i, len = strlen(test_string);
	char open_brackets[BRACKETS_MAX], matching_bracket;
	
	/* we can update the session summary here because the are
	   no other chances for input from the user */
	option_stats[MATCHING_BRACKETS]++;

	/* open_brackets acts imilar to a stack, keeps track of the last open
	   bracket. If the next closing bracket is of the same type, the 
	   bracket is 'popped' off the stack. */
	   
	/* there's no way a string of 1 character can give a matching set of
	   brackets, therefore they are either unequal or there are no 
	   brackets */
	if(len == 1){
	  	printf("\nBrackets do not match or there are no brackets\n");
		return;
	}
	
	/* loop through each character in test_string, executing
	   the releveant case */
	for(i = 0; i < len; i++){
		switch(*test_string){
			/* the first 3 cases are functionally the same, 
			   just for different brackets */
			case '(':
			case '[':
			case '{':
			/* the if statement is so we make use of the 0th 
			   element of the array */
				if(i) j++;
				
				/* open bracket is 'pushed' on */
				open_brackets[j] = *test_string;
				test_string++;
				break;
				
				/* the next three cases are functionally the same, but
				   matching_bracket needs to take a different value
				   in each case */
			case ')':
				matching_bracket = '(';
			case ']':
				if(*test_string == ']') matching_bracket = '[';
			case '}':
				if(*test_string == '}') matching_bracket = '{';
				
				/* if the current bracket being analysed isn't the closing 
				   bracket of open_brackets[j] i.e. the top of our 'stack'
				   then the brackets do not match */
				   
				if(open_brackets[j] != matching_bracket){
					printf("\nBrackets do not match\n");
					return;
				}
				/* completed set of brackets is 'popped' off. Again, the if statement
				   is to make use of the 0th element of the array */
				if(j) j--;
				test_string++;
				break;
				
			/* this case will only occur if the character isn't one of
			   the three types of brackets being used. In this case we
			   wish to just go to the next character */
			default:
				test_string++;
				break;
		}
	}
	
	/* the brackets match if the 'stack' is empty, i.e. j == 0 */
	if(!j){
		printf("\nThe brackets match\n");
		return;
	}
	
	/* if there's any circumstance that isn't captured by the above
	   checks where the brackets don't match, they are covered by this */
	printf("\nBrackets do not match\n");
}

/**************************************************************************
* format_text() - implements the "Formatting Text" option (requirement 6)
* from the main menu. You will need to parse the text, adding newlines 
* so that no line is longer than "width" which means you will need to 
* replace the first white space character before this with the newline. You
* then need to insert extra spaces so that lines are spaced as evenly as 
* possible. Finally you want to update the option_stats array appropriately.
* 
* 
**************************************************************************/
void format_text(int * option_stats, unsigned width, char * text){
	int info[2], i;
	char copy[FORMAT_TEXT_STR_MAX + EXTRA_SPACES];
	char ** words;
	strcpy(copy, text);
	analyse_string(copy, info);
	words = (char**) calloc(info[1], info[0]); 
	
	tokenise_string(text, words, " ");
	for(i = 0; i < info[1]; i++){
		printf("%d %s\n", info[1], words[i]);
	}
	free (words);
}

/**************************************************************************
* session_summary() - implements the "Session Summary" option (requirement
* 7) from the main menu. In this option you need to display the number of 
* times that each option has been run and then update the count of how 
* many times this function has been run.
*
* Loops through all the values of enum options and prints out how many 
* each of them has been used in a formatted fashion.
**************************************************************************/
void session_summary(int * option_stats){
	int i;
	
	printf("Option Count\n------ -----\n");
	/* iterate through the enum. we don't want to print out exit
	   so we check if its less than not less than or equal to. 
	   'Option' is six letters long so we indent the option number
	   by 6 characters. We do the same thing for 'Count' where the
	   indentation is 5 characters long */
	for(i = PERFECT_SQUARES; i < EXIT; i++){
		printf("%*d %*d\n", 6, i, 5, option_stats[i]);
	}
	
	option_stats[SESSION_SUMMARY]++;
}
