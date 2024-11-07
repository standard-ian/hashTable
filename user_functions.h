/*
Ian Leuty CS163 July 25 2024 ileuty@pdx.edu

This file contains interface for the modules of the client ui
*/

#include "table.h"

//menu, organize options, call hash table member functions to interact w/ ADT
void test_menu(table &cities);


//set table properties, prompt user for table siez and choice of hash function
int set_table(int &user_size, int &hash_choice);

//dynamically get char* and error check for length
void dynamic_read(char *&field, const int TEMP);
