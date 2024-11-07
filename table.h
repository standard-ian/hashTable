/*
Ian Leuty CS163 July 25 2024 ileuty@pdx.edu

This file contains the hash table interface

testing should allow for:
    1. [x] display all (testing only)
    2. [x] display matching by keyword
    3. [x] retrieve matching by keyword
    4. [x] remove a city by name
    5. [x] display all cities with a matching country
    6. [x] creating different table sizes
    7. [x] different hash functions
    8. [x] analysis (not reqd.)
    9. [x] enter a new city
    10.[x] load in from a specified file name
    11.[x] meaningful return values indicating count, succcess, or faliure where applicable 
*/

#include "city_data.h"

#ifndef TABLE
#define TABLE

//BAD_SIZE struct 
struct BAD_SIZE{
    int error;
};

//node struct 
struct node{
    city_data a_city;
    node * next;
}; 

//class interface for the hash table
class table{
    public:
        //constuctor sets size and hash
        table(int user_size, int hash_choice); 
        //destructor 
        ~table();
        //returns true if nothing in the list
        bool empty();

        //display all cities & mark indexes in output, return number displayed
        int display_all(); 
        //displays cities with matching city_ascii
        int display(char *key); 
        //display the only city with matching city_ascii and id
        int display_with_id(char *key, int ident); 
        //display all cities at matching index of table
        int display_index(int index); 
        //rehash by country using:
        //add_by_country, search_chain, rehash 
        int display_country_matches(char *key); 

        //load in from the file
        int file(char *filename);
        //add city, key == city_ascii, uses constructor set hash
        int add(city_data &to_add); 
        //add city, key == country, uses constructor set hash
        int add_by_country(city_data &to_add); 

        //retrieve first city with matching city_ascii
        int retrieve(char *key, city_data &to_retrieve); 
        //retrieve the only city with matching city_ascii and id
        int retrieve_with_id(char *key, city_data &to_retrieve, int ident); 
        //retrieve all matches to the client w/ a pointer(dynamic array)
        int retrieve_all(char *key, city_data *&to_retrieve);

        //delete first city with matching city_ascii
        int remove(char *key); 
        //delete the only city with matching city_ascii and id
        int remove_with_id(char *key, int ident); 

        /*
        perform efficiency calculations, pass variables for results, 
        could be several functions w/ seperate returns
        */
        int analyze(float &percent, float &ideal, float &actual, int &size, int &items_read);

    private:
        //////////data members
        int items; //items stored
        int table_size; //indexes of chain_table, set by constructor
        int hash; //hash function to use, set by constructor
        node **chain_table; //table structure
        
        /////////non recursive utility functions:
        //set hash function using constructor set hash
        int pick_hash(char *key); 
        //make a lowercase copy of key
        int to_lower(char *key, char *&copy); 
        
        //display all cities matching country key
        int display_countries(char *key); 
        
        ///////////recursive utility functions:
        //deconstruct a chain at index node recursively, return nodes removed 
        int clear_chain(node *&head); 

        //display all at a chain recursively, return nodes displayed
        int display_all(node *head); 

        //traverse chain, retrieve
        //copy into city_data object, return success/faliure
        int retrieve(char *key, city_data &item, node *head); 

        //traverse chain, retrieve
        //copy into city_data object if is_match(ident), return success/faliure
        int retrieve_with_id(char *key, city_data &item, node *head, int ident); 

        //recursive traverse and retrieve into array
        int retrieve_all(char *key, int &matches, city_data *&items, node *head);

        //traverse a chain and perform op_code on is_match(key)
        //0 = remove first match, key is city_ascii, return success/faliure
        //1 = display all matches, key is city_ascii, return number displayed 
        //2 = display all matches, key is country, return number displayed
        int search_chain(char *key, node *&head, int op_code);

        //traverse a chain and perform op_code if is_match(city_ascii) && ident
        //0 = remove, then return success/faliure
        //1 = display then return success/faliue
        int search_chain_with_id(char *key, node *&head, int op_code, int ident);

        //rehash into a new table 
        int rehash(table &a_table, node *head);
};
#endif
