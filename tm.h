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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#ifndef TM_H
#define TM_H

typedef struct tm * tm_type_ptr;

typedef enum truefalse
{
    FALSE, TRUE
} BOOLEAN;

#define NUM_COINS 6
#define TICKET_NAME_LEN 40
#define TICKET_ZONE_LEN 10
#define DEFAULT_STOCK_LEVEL 10
#define DEFAULT_COINS_COUNT 50
#define NUM_ARGS 3

/* Defines the number of cents in a dollar, while its more than obvious,
   helps to avoid magic numbers */
#define CENTS_PER_DOLLAR 100

#include "tm_stock.h"
#include "tm_coins.h"
#include "tm_utility.h"
#include "tm_options.h"

/* global type definitions */
typedef struct stock_list * stock_list_ptr;
typedef struct coin * coin_list_ptr;

typedef struct tm
{
    coin_list_ptr coins;
    stock_list_ptr stock;
} tm_type;

typedef enum options{
	PURCHASE_TICKET = 1, DISPLAY_TICKET, SAVE_EXIT, ADD_TICKET, REMOVE_TICKET,
	DISPLAY_COINS, RESTOCK_TICKETS, RESTOCK_COINS, ABORT
} OPTION;
/* global constants for the program */

#define TM_H_END
#endif
