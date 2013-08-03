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
**************************************************************************/
void perfect_squares(int * option_stats, unsigned number)
{
}

/**************************************************************************
* ascii_to_binary() - implements the "ASCII to Binary Generator" option
* (requirement 3) from the main menu. Essentially, you need to implement
* an algorithm for conversion of integers to binary and apply this to 
* every character in the input array (called 'ascii' here) and print out
* the result. Finally, you need to update the option_stats array 
* appropriately 
**************************************************************************/
void ascii_to_binary(int * option_stats, char * ascii)
{
}

/**************************************************************************
* matching_brackets() - implements the "Matching Brackets" option 
* (requirement 4) from the main menu. You need to implement an algorithm 
* which will parse a string passed in and determine whether the brackets 
* all match, including the type of brackets. You need to account for 
* {} [] () and you also need to allow for the nesting of brackets. 
* You need to tell the user whether the brackets match or not. Finally you
* need to update the option_stats array appropriately.
**************************************************************************/
void matching_brackets(int * option_stats, char * test_string)
{
}

/**************************************************************************
* format_text() - implements the "Formatting Text" option (requirement 6)
* from the main menu. You will need to parse the text, adding newlines 
* so that no line is longer than "width" which means you will need to 
* replace the first white space character before this with the newline. You
* then need to insert extra spaces so that lines are spaced as evenly as 
* possible. Finally you want to update the option_stats array appropriately.
* 
**************************************************************************/
void format_text(int * option_stats, unsigned width, char * text)
{
}

/**************************************************************************
* session_summary() - implements the "Session Summary" option (requirement
* 7) from the main menu. In this option you need to display the number of 
* times that each option has been run and then update the count of how 
* many times this function has been run.
**************************************************************************/
void session_summary(int * option_stats)
{
}
