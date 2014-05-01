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

If selected, do you grant permission for your assignment
to be released as an anonymous student sample solution?
--------------------------------------------------------
Yes


Known bugs:
-----------
None


Incomplete functionality:
-------------------------
None


Assumptions:
------------
Maximum number of coins of any denomination in the machine is 99
Maximum stock level for a ticket is 99
Maximum price of a ticket is $99.99 (ticket_price = 9999)


Any other notes for the marker:
-------------------------------
If any of my assumptions conflict with any of your test cases the values can be
changed in the following places

Max coin count: tm_coins.h: line 20. (Read the comment)
Max stock level: tm_stock.h: line 74
Max ticket price: tm_stock.h: line 75

If you need to change either of the last 2 to have more digits, you'll also need to 
change STOCK_FILE_MAX_LINE_LENGTH (tm_stock.h: line 70) accordingly to avoid any
possible seg faults.
