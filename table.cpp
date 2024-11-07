/*
Ian Leuty CS163 July 25 2024 ileuty@pdx.edu

This file contains the implementation for the hash table
recursive and utility functions are at the bottom half of the file
*/

#include "table.h"

//contsructor
table::table(int user_size, int hash_choice){
    BAD_SIZE error; 
    if(user_size > 3000000 || user_size < 10) throw error;
    int i{0};
    table_size = user_size;
    hash = hash_choice;
    items = 0;
    chain_table = new node* [table_size];
    for(i = 0; i < table_size; ++i)
        chain_table[i] = nullptr;
}

//destructor
table::~table(){
    int p{0};
    int deleted{0};
    while(p < table_size){
        deleted += clear_chain(chain_table[p]);
        ++p;
    }
    delete [] chain_table;
    //std::cout << std::endl << deleted << " cities destructed" << std::endl;
}


//checks if the list is empty
bool table::empty(){
    if(!items) return true;
    return false;
}

//display_all with index positions marked in red
int table::display_all(){
    if(!chain_table) return 0;
    int z{0};
    int displayed{0};
    for(z = 0; z < table_size; ++z){
        if(chain_table[z])
            std::cout << "\033[0;31m\033" << "o" //ANSII escape codes and keys for red text
                      << std::endl << "##########Table Index: " 
                      << z << "###########" << "\033[0m" << std::endl;
        displayed += display_all(chain_table[z]);
    }
    return displayed;
}

//display cities based on search key of city_ascii
int table::display(char *key){
    int index{0};
    index = pick_hash(key);
    if(index > table_size || index < 0) return 0;
    return search_chain(key, chain_table[index], 1);
}

//display 1 city based on search key of city_ascii and country name
int table::display_with_id(char *key, int ident){
    int index{0};
    index = pick_hash(key);
    if(index > table_size || index < 0) return 0;
    return search_chain_with_id(key, chain_table[index], 1, ident);
}

//display all the items at a given index of the table
int table::display_index(int index){
    int count{0};
    if(index < 0 || index > table_size - 1) return 0;
    node *current{chain_table[index]};
    while(current){
        current -> a_city.display();
        current = current -> next;
        ++count;
    }
    return count;
}


/*
display all the cities in a particular county
create new table object, rehash data using copy function and 
passing country as the key in constructor set hash function
change hash argument here if experimenting with different 
h(x) for country
if rehash is successful, display all matching countries
catch number displayed and return it
better approach: 
data within table nodes is city_data pointers,
rehash the same data without having to copy. 
*/
int table::display_country_matches(char *key){
    if(!key || !chain_table) return 0;
    int i{0}, count{0};
    table rehash_countries(table_size, hash);
    for(i = 0; i < table_size; ++i)
    if(!rehash(rehash_countries, chain_table[i])) return 0;
    count = rehash_countries.display_countries(key);
    return count; 
}

/*
file interaction, create ifstream variable, manage reading at the file scope
store each line (city) into city_io struct, build city_data object, pass that to 
table's add function. Loop until eof to populate the entire table
*/
int table::file(char *filename){
    std::ifstream filein;
    int city_count{0};
    filein.open(filename);
    if(!filein) //error if not able to open
        return -1;
    else{
        filein.peek();
        bool file_check{!filein.eof()}; //this seems silly but it is a way to use return value of load
                                        //to check of eof

        if(!file_check) //error if file was opened but is empty
            return -2;
        while(file_check){ //while !eof
            //city_io new_city; //create a new menu object
            city_data to_add;
            file_check = to_add.load(filein); //read into it from the file 
            ++city_count;
            if(!add(to_add)){ //if new_city cannot be added via table, return code
                file_check = 0;
                return -3;
            }
        }
    }
    //end filein procedure
    return city_count;
}


//add a city object to the hash table
int table::add(city_data &to_add){
    char *name{nullptr};
    to_add.lower_name(name);
    int index{pick_hash(name)};
    delete [] name;
    if(index < 0 || index > table_size) return 0;
    node *temp{chain_table[index]};
    chain_table[index] = new node;
    if(!chain_table[index] -> a_city.copy(to_add)){
        delete chain_table[index];
        return 0;
    }
    chain_table[index] -> next = temp;
    ++items;
    return 1;
}

//add a city object to a new hash table by country
int table::add_by_country(city_data &to_add){
    char *name{nullptr};
    to_add.lower_country(name);
    int index{pick_hash(name)};
    delete [] name;
    if(index < 0 || index > table_size) return 0;
    node *temp{chain_table[index]};
    chain_table[index] = new node;
    if(!chain_table[index] -> a_city.copy(to_add)){
        delete chain_table[index];
        return 0;
    }
    chain_table[index] -> next = temp;
    ++items;
    return 1;
}

//retrieve a city using a search key and city data object as args
int table::retrieve(char *key, city_data &to_retrieve){
    int index{0};
    index = pick_hash(key);
    if(index > table_size || index < 0) return 0;
    if(!retrieve(key, to_retrieve, chain_table[index])) 
        return 0;
    return 1;
}

//retrieve a city using city_ascii and country
int table::retrieve_with_id(char *key, city_data &to_retrieve, int ident){
    int index{0};
    index = pick_hash(key);
    if(index > table_size || index < 0) return 0;
    if(!retrieve_with_id(key, to_retrieve, chain_table[index], ident))
        return 0;
    return 1;
}

//retrieve into an array of city_data, return number found
int table::retrieve_all(char *key, city_data *&to_retrieve){
    int index{0};
    int matches{0};
    index = pick_hash(key);
    if(index > table_size || index < 0) return 0;
    return retrieve_all(key, matches, to_retrieve, chain_table[index]);
}

//delete a city from the table using a search key of city_ascii
int table::remove(char *key){
    int index{0};
    index = pick_hash(key);
    if(index > table_size || index < 0) return 0;
    return search_chain(key, chain_table[index], 0);
}

//delete a city from the table using a search key of city_ascii and a country name
int table::remove_with_id(char *key, int ident){
    int index{0};
    index = pick_hash(key);
    if(index > table_size || index < 0) return 0;
    return search_chain_with_id(key, chain_table[index], 0, ident);
}

//stats about hash success
int table::analyze(float &percent, float &ideal, float &actual, int &size, int &items_read){
    if(!chain_table) return 0;
    int empty{0};
    float per_index{0.00};
    size = table_size;
    items_read = items;
    ideal = static_cast<float>(items) / static_cast<float>(table_size);
    for(int i = 0; i < table_size; ++i){
        node *current{chain_table[i]};
        while(current){
            ++per_index;
            current = current -> next;
        }
        if(per_index == 0)
            ++empty;
        actual = (actual + per_index) / 2;
        per_index = 0;
    }
    percent = static_cast<float>(empty) / static_cast<float>(table_size) * 100;
    return 1;
}

/////////////////// RECURSIVE & UTILITY FUNCTIONS ////////////////////////

//select the correct hash based on user set variable
int table::pick_hash(char *key){
    if(!key) return -1;
    char *copy{nullptr};
    to_lower(key, copy);
    int index{0};
    //first hash function, good one
    if(hash == 1){
        int keylength{0}, i{0};
        index = copy[i];
        keylength = strlen(copy);
        for(i = 1; i < keylength; ++i)
            index = ((index* 1000) + copy[i]) % table_size;
        delete [] copy;
        return index;
    }
    //bad hash function to play around
    index = 0; 
    char *ptr{copy};
    for(; *ptr != '\0'; ptr++)
        index = (index+ *ptr) % table_size;
    delete [] copy;
    return index;
}

//copy a char* to another char* and lowecase it
int table::to_lower(char *key, char *&copy){
    if(!key) return 0;
    int i{0}, length{0};
    copy = new char[strlen(key) + 1];
    strcpy(copy, key);
    length = strlen(copy);
    for(i = 0; i < length; ++i)
        if(isupper(copy[i]))
            copy[i] = tolower(copy[i]);
    return 1;
}

//display cities based on search key of country
int table::display_countries(char *key){
    int index{0};
    index = pick_hash(key);
    if(index > table_size || index < 0) return 0;
    return search_chain(key, chain_table[index], 2);
}

//recursively clear a chain
int table::clear_chain(node *&head){
    if(!head) return 0; 
    node *temp{head -> next};
    delete head;
    head = temp;
    return clear_chain(head) + 1;
}

//recursively display all
int table::display_all(node *head){
    if(!head) return 0;
    if(!head -> a_city.display()) return 0;
    return display_all(head -> next) + 1;
}

//recursively traverse the chain for retrieval
int table::retrieve(char *key, city_data &item, node *head){
    if(!head) return 0;
    if(head -> a_city.is_match_city(key)){
        item.copy(head -> a_city);
        return 1;
    }
    return retrieve(key, item, head -> next);
}

//retrieve only match using city_ascii and id
int table::retrieve_with_id(char *key, city_data &item, node *head, int ident){
    if(!head) return 0;
    if(head -> a_city.is_match_city(key) && head -> a_city.is_match_id(ident)){
        item.copy(head -> a_city);
        return 1;
    }
    return retrieve_with_id(key, item, head -> next, ident);
}

//recursively traverse chain for retrieval into an array
int table::retrieve_all(char *key, int &matches, city_data *&items, node *head){
    if(!head) return 0;
    if(head -> a_city.is_match_city(key)){
        items[matches].copy(head -> a_city);
        ++matches;
        return retrieve_all(key, matches, items, head -> next) + 1;
    }
    return retrieve_all(key, matches, items, head -> next);
}

//recursively search the chain and perform action based on op code
int table::search_chain(char *key, node *&head, int op_code){
    if(!head) return 0;
    if(head -> a_city.is_match_city(key) && op_code == 1){
        head -> a_city.display();
        return search_chain(key, head -> next, op_code) + 1;
    }
    if(head -> a_city.is_match_country(key) && op_code == 2){
        head -> a_city.display();
        return search_chain(key, head -> next, op_code) + 1;
    }
    if(head -> a_city.is_match_city(key) && op_code == 0){
        head -> a_city.delete_city();
        node *hold{head -> next};
        delete head;
        --items;
        head = hold;
        return 1;
    }
    return search_chain(key, head -> next, op_code);
}

//recursively search the chain with country name and perform action based on op code
int table::search_chain_with_id(char *key, node *&head, int op_code, int ident){
    if(!head) return 0;
    if(head -> a_city.is_match_city(key) 
        && head -> a_city.is_match_id(ident) 
        && op_code == 1){
        head -> a_city.display();
        return 1;
    }
    if(head -> a_city.is_match_city(key) 
        && head -> a_city.is_match_id(ident) 
        && op_code == 0){
        head -> a_city.delete_city();
        node *hold{head -> next};
        delete head;
        --items;
        head = hold;
        return 1;
    }
    return search_chain_with_id(key, head -> next, op_code, ident);
}

//recursively copy using add country function
int table::rehash(table &a_table, node *head){
    if(!head) return 0;
    if(a_table.add_by_country(head -> a_city))
        return rehash(a_table, head -> next) + 1;
    return 0;
}
