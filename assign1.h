/***************************************************************************
* COSC1283/1284 - Programming Techniques
* Semester 1 2013 Assignment #1 
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Yallara Username : EDIT HERE
* Course Code      : EDIT HERE
* Program Code     : EDIT HERE
* Start up code provided by Paul Miller and Xiaodong Li
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* constants go here */
#define NUM_OPTION_STATS 5

/* This is used to compensate for the extra character spaces taken up by
   the '\n' and '\0' when user is asked for input through fgets(). */
#define EXTRA_SPACES 2

/* Specifies the maximum input length a user can enter for the options
   menu. */
#define MAX_OPTION_INPUT 1

/* Specifies the maximum number of characters an input of an integer 
   can be. i.e. 7 = 7 digits */
#define MAX_NUM_DIGITS 7   

/* Specifies the minimum and maximum values allowed for the perfect
   squares option */
#define PERFECT_SQUARES_MIN 1
#define PERFECT_SQUARES_MAX 1000000 

/* Specifies the minimum and maximum amount of characters allowed to be
   input into the ascii_to_binary function */

#define ASCII_MIN 1
#define ASCII_MAX 5   

/* Specifies the minimum and maxiumum amount of characters allowed to be 
   input into the matching_brackets function */
   
#define BRACKETS_MIN 1
#define BRACKETS_MAX 20

/* Specifies the value that symbolises that the user wishes to return to 
   the main menu. It has to be a value that no ASCII character has */ 
#define RETURN_TO_MENU -2 

/* Specifies the value of the most significant bit (MSB) */
#define MSB 128   


/* provides us with a BOOLEAN type for using TRUE and FALSE */
typedef enum true_false
{
    FALSE=0,TRUE
} BOOLEAN;

/* Provides us with variables corresponding to each option for more 
   readable code */
typedef enum options{
	PERFECT_SQUARES = 1, ASCII_TO_BINARY, MATCHING_BRACKETS, 
	FORMATTED_TEXT, SESSION_SUMMARY, EXIT
} OPTION;

/* function prototypes for each option to be implemented */
void perfect_squares(int * option_stats, unsigned number);
void ascii_to_binary(int * option_stats, char * ascii);
void matching_brackets(int * option_stats, char * test_string);
void format_text(int * option_stats, unsigned width, char * text);
void session_summary(int * option_stats);

/* function prototypes for additional functions contained in utility1.c */
void read_rest_of_line(void);
void dispOptions(void);
int getInt(int min, int max);
int getString(int max, char * string);
void integer_to_binary(int integer,char* binary);