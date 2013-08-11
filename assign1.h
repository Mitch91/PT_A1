/***************************************************************************
* COSC1283/1284 - Programming Techniques
* Semester 1 2013 Assignment #1 
* Full Name        : Mitchell McGregor Elsbury
* Student Number   : s3286283
* Yallara Username : s3286283
* Course Code      : COSC1284
* Program Code     : BP094SEC8
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

/* Specifies the minimum and maximum values for chars per line and the 
   total number of chars for the formatted text function. Robbie stated
   on blackboard that we can assume the chars per line will between 20 
   and 50. */
   
#define FORMAT_TEXT_INT_MIN 20
#define FORMAT_TEXT_INT_MAX 50 

#define FORMAT_TEXT_STR_MIN 150
#define FORMAT_TEXT_STR_MAX 200 

/* Specifies the value that symbolises that the user wishes to return to 
   the main menu. It has to be a value that no ASCII character has */ 
   
#define RETURN_TO_MENU -2 

/* Checks to see if we are meant to return to menu. */

#define DO_WE_RETURN_TO_MENU if(cancel == RETURN_TO_MENU) break;

/* Specifies the value of the most significant bit (MSB) */

#define MSB 128  

/* Specifies the ASCII value for a space */

#define SPACE 32 

/* provides us with a BOOLEAN type for using TRUE and FALSE */
typedef enum true_false
{
    FALSE=0,TRUE
} BOOLEAN;

/* Provides us with variables corresponding to each option for more 
   readable code */
typedef enum options{
	PERFECT_SQUARES = 1, ASCII_TO_BINARY, MATCHING_BRACKETS, 
	FORMAT_TEXT, SESSION_SUMMARY, EXIT
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
void clear_array(int * array, unsigned size);
void analyse_string(char * text, int * info);
void tokenise_string(char * text, char ** words, char * delims);
void format_line(char * line, int width, int words_in_line);