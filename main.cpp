/*
Ian Leuty CS163 July 25 2024 ileuty@pdx.edu

This file contains the main calling routine.
Contains exception handling to check table size
*/

#include "table.h"
#include "user_functions.h" 

using namespace std;


int main(){
    int user_size{0}, hash_choice{0};

    //create ifstream object and check file, load from file using a menu object member.
    ifstream filein;

    cout << endl << "Shell for testing.\n" << endl;

    //set parameters for the table constructor 
    set_table(user_size, hash_choice);

    try{
        //create the table for cities
        table cities(user_size, hash_choice);
        test_menu(cities); //pass the ADTs to the menu function for further interaction
    }
    catch(BAD_SIZE){
        cerr << endl << "Operation Failed: Could not create table. Invalid size." << endl;
    }
    
    return 0;
}
