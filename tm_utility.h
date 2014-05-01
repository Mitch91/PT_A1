/***************************************************************************
* COSC1283/1284 - Programming Techniques
* Semester 2 2013 Assignment #2 - SCSIT Program Management System
* Full Name        : Mitchell Elsbury
* Student Number   : 3286283
* Yallara Username : s3286283
* Course Code      : COSC1284
* Program Code     : BP094SEC8
* Start up code provided by Paul Miller and Lin Padgham
***************************************************************************/

#ifndef TM_UTILITY_H
#define TM_UTILITY_H
#include "tm.h"

#define EXTRA_SPACES 2

/* this is used a lot, so it made sense to #define it */
#define DO_WE_RETURN_TO_MENU if(cancel == RETURN_TO_MENU) return

/* defines the maximum number of digits that an integer gotten by get_int() can be.
   While doesn't have much significance within this assignment, get_int is from my
   first assignment and for it to work properly MAX_NUM_DIGITS needs to be defined */
#define MAX_NUM_DIGITS 6

/* defines the constant to return when the user wishes to return to the menu. Its
   defined to be a value that wouldn't conflict with other constants (EOF, NULL etc.)
   and negative so that it isnt a valid return value for any of the functions used */
#define RETURN_TO_MENU -2

/* when 3 is used for the spaces variable in print_dollar_format() there's no
   formatting to the string because the minimum number is 4 chars. 
   For example 3.50 */
#define NO_FORMATTING 3

/* defines the delimiters that separate each line and token respectively */
#define LINE_DELIMS "\n\0"
#define TOKEN_DELIMS ","

/* since eres is a 64 bit system, allocating memory less than 8
   bytes will cause problems */
#define MIN_ALLOC_SIZE 8

/* My initial guess for how many lines there are within the stock file, for most
   cases it will be too small, but thats the idea; this way we won't malloc 
   (or realloc) more than we need */
#define NUM_LINES_GUESS 2

#define BASE_TEN 10

/* allocates enough space to store the contents of a file pointed to by fp.
   The space gets allocated to the variable file_contents plus null char*/
#define alloc_file_contents(file_contents, fp) \
	if((file_contents = malloc(get_file_size(fp) + 1)) == NULL){\
	fprintf(stderr,"Unable to allocate memory for file contents\n"); \
	return FALSE;}
	
/* stores the contents of the file pointed to by fp within in the string 
   contents then sends the point back to the start of the block of memory
   allocated to contents */	
#define get_file_contents(contents,fp) \
	for(*contents = getc(fp); *contents != EOF; contents++, *contents = getc(fp));\
	*contents = '\0'; contents = contents - get_file_size(fp)

 /* combines the alloc macro with the get macro, for storing a file's contents */
#define put_file_contents(contents,fp) alloc_file_contents(contents,fp);\
	get_file_contents(contents,fp)

/* in the event that something goes wrong with the loading of a file, this macro
   is called. Its called quite a few times so its mainly here to avoid repetitious 
   code */
#define incorrect_format(file) fprintf(stderr,"%s file has incorrect\
 format\n",file); free(file_contents); free(lines); return FALSE



/* function prototypes for functions implemented in tm_utility.c
 * These are generic helper functions that provide support to the rest
 * of your application.
 *
 * Remember that we will assess the level to which you provide some level
 * of functional abstraction here.
 */
 
void read_rest_of_line(void);
BOOLEAN system_init(tm_type_ptr tm);
BOOLEAN load_data(tm_type_ptr tm, char * stockfile, char * coinsfile);

int get_file_size(FILE * fp);
int get_user_choice(void);
void disp_options(void);
int get_int(int min, int max);
int get_string(int max, char * string);
int tokenise_stock_lines(char ** lines, char * file_contents, int num_lines);
void system_free(tm_type_ptr);
char get_ticket_type(void);
void print_dollar_format(int cents, int spaces);
int insert_coins(int price, int * coins_inserted);
#endif