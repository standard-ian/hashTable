/*
Ian Leuty CS163 July 25 2024 ileuty@pdx.edu

This file contains implementation for the modules of the client ui
This is where the menu is implemented, and where all the client calls to the 
table ADT take place

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

#include "user_functions.h"

using namespace std;

//set hash table properties
int set_table(int &user_size, int &hash_choice){
    cout << "What size hash table would you like for this data?\n>";
    cin >> user_size;
    while(cin.fail() || user_size > 2147483640 || user_size < 0){
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Enter a number between one and the maximum integer size. Try again.\n>";
        cin >> user_size;
    }
    cin.ignore(100, '\n');
    if(user_size > 2147483640 || user_size < 0) return 0;

    cout << "Which hash function? [1/2]\n>";
    cin >> hash_choice;
    while(cin.fail() || hash_choice < 1 || hash_choice > 2){
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Enter [1/2]. Try again.\n>";
        cin >> hash_choice;
    }
    cin.ignore(100, '\n');
    if(hash_choice < 1 || hash_choice > 2) return 0;
    return 1;
}

//implementation of the menu function
void test_menu(table &cities){
    int choice{-1};
    char again{'\0'};

    while(choice != 0){ //7 will quit, no switch case needed
        cout << endl << "Choose from one of the following options:\n\n"
             << "1. Add a city" << endl
             << "2. Display all cities" << endl
             << "3. Retrieve a matching city" << endl
             << "4. Retrieve all cities that match a key" << endl
             << "5. Display all cities that match a key" << endl
             << "6. Delete a city" << endl
             << "7. Display all cites in a country" << endl
             << "8. Run analysis" << endl
             << "9. Load from a data file" << endl
             << "0. Quit" << endl
             << '>';
        cin >> choice;

        while(cin.fail() || 
              choice < 0 || 
              choice > 9){ //error check menu selection
            cin.clear();
            cin.ignore(100, '\n');
            cout << endl << "Please make a numeric selection between 0 and 9.\n>";
            cin >> choice;
        }
        cin.ignore(100, '\n');

        switch(choice){
            case 1:{
                do{
                    cout << endl << "Enter a city's data" << endl;
                    city_io new_city;
                    new_city.read();
                    city_data to_add;
                    to_add.build(new_city);
                    cities.add(to_add);
                    cout << endl << "Add another city? [y/n]\n>";
                    cin >> again;
                    cin.ignore(100, '\n');
                }while(toupper(again) == 'Y');
                again = '\0';
            }
            break;
            
            case 2:{
                if(cities.empty()) 
                    cout << endl << "Operation Failed: No cities in the table." 
                         << endl << "Add some using menu options 1 or 9." << endl;
                else{
                    int displayed{0};
                    displayed = cities.display_all();
                    cout << endl << displayed << " cities displayed." << endl 
                         << "\033[0;31m\033"
                         << "IIndex positions highlighted in red." 
                         << "\033[0m" << endl;
                }
            }
            break;
            
            /*
            retrieve a matching city
            search for city to retrieve using display
            get number displayed
            if more than 1, narrow down with id, then perform retrieval
            else retrieve it into local city_data object, display it or do other things
            or error if no matches
            */
            case 3:{
                if(cities.empty()) 
                    cout << endl << "Operation Failed: No cities in the table." 
                         << endl << "Add some using menu options 1 or 9." << endl;
                else{
                    city_io io;
                    int ident{0};
                    char *city_name{nullptr};
                    int results{0};
                    do{
                        city_data found;
                        cout << endl << "Enter a city name to retrieve it.\n>";
                        if(!io.dynamic_read(city_name, SIZE)) 
                            cout << endl << "Error!" << endl;
                        cout << endl;
                        results = cities.display(city_name); //get the number of matches

                        if(results == 1 && cities.retrieve(city_name, found)){ //if it's just one...
                            cout << endl << "The city was found, retrieved, the client's copy contains:" << endl << endl;
                            found.display(); //display the local city_data object with the retrieved city
                        }

                        else if(results > 1){ //if it's more than one...
                            cout << endl << results << " cities with matching names were found." << endl
                                 << "Enter the id (last field) name of the specific city you want to retrieve.\n>";
                            cin >> ident;
                            while(cin.fail() || ident < 0){
                                cin.clear();
                                cin.ignore(100, '\n');
                                cout << "Enter an id number greater than 0\n>";
                                cin >> ident;
                            }
                            cin.ignore(100, '\n');
                            cout << endl;
                            if(cities.retrieve_with_id(city_name, found, ident)){ //if city was retrieved successfully
                                cout << endl << "The city was found, retrieved, the client's copy contains:" << endl << endl;
                                found.display(); //display the local city_data object with the retrieved city
                            }
                            else //if no match with id...
                                cout << endl << "Operation failed: No cities in the table match that info." << endl;
                        }

                        else //if no matches...
                            cout << endl << "Operation failed: No cities in the table match that name." << endl;

                        cout << endl << "Retrieve again? [y/n] \n>";
                        cin >> again;
                        cin.ignore(100, '\n');
                        delete [] city_name;
                        city_name = nullptr;
                    }while(toupper(again) == 'Y');
                    again = '\0';
                }
            }
            break;
           
            //retrieve all matching cities 
            case 4:{
                if(cities.empty()) 
                    cout << endl << "Operation Failed: No cities in the table." 
                         << endl << "Add some using menu options 1 or 9." << endl;
                else{
                    city_io io;
                    int ident{0};
                    char *city_name{nullptr};
                    int results{0};
                    do{
                        city_data *found;
                        found = new city_data[20];
                        cout << endl << "Enter a city name to retrieve all matches.\n>";
                        if(!io.dynamic_read(city_name, SIZE)) 
                            cout << endl << "Error!" << endl;
                        cout << endl;
                        results = cities.retrieve_all(city_name, found);
                        if(results > 0){
                            cout << endl << "These cities were found and retrieved by the client:" << endl << endl;
                            for(int i = 0; i < results; ++i)
                                found[i].display();
                        }
                        else 
                            cout << endl << "Operation failed: No cities in the table match that name." << endl;

                        cout << endl << "Retrieve again? [y/n] \n>";
                        cin >> again;
                        cin.ignore(100, '\n');
                        delete [] city_name;
                        city_name = nullptr;
                        delete [] found;
                        found = nullptr;
                    }while(toupper(again) == 'Y');
                    again = '\0';
                }
            }
            break;

            //display cities with matching name (city_ascii)
            case 5:{
                if(cities.empty()) 
                    cout << endl << "Operation Failed: No cities in the table." 
                         << endl << "Add some using menu options 1 or 9." << endl;
                else{
                    city_io io;
                    char *city_name{nullptr};
                    int results{0};
                    do{
                        cout << endl << "Enter a city name to display it.\n>";
                        if(!io.dynamic_read(city_name, SIZE)) 
                            cout << endl << "Error!" << endl;
                        cout << endl;
                        results = cities.display(city_name);

                        if(!results)
                            cout << endl << "Operation failed: No cities in the table match that name." << endl;

                        else
                            cout << endl << results << " cities with matching names were found." << endl;

                        cout << endl << "Search and display again? [y/n] \n>";
                        cin >> again;
                        cin.ignore(100, '\n');
                        delete [] city_name;
                        city_name = nullptr;
                    }while(toupper(again) == 'Y');
                    again = '\0';
                }
            }
            break;
            
            /*
            search for city to delete using display
            get number displayed
            if more than 1, narrow down with id, then confirm before deleting
            else if 1 confirm before deletion
            or error if no matches
            */
            case 6:{
                if(cities.empty()) 
                    cout << endl << "Operation Failed: No cities in the table." 
                         << endl << "Add some using menu options 1 or 9." << endl;
                else{
                    city_io io; char *city_name{nullptr};
                    int ident{0};
                    char delete_it{'\0'};
                    int results{0};
                    do{
                        cout << endl << "Enter a city name to delete it.\n>";
                        if(!io.dynamic_read(city_name, SIZE)) 
                            cout << endl << "Error!" << endl;
                        cout << endl;
                        results = (cities.display(city_name));

                        if(results == 1){
                            cout << endl << "Do you want to delete this city from the table?\n>";
                            cin >> delete_it;
                            cin.ignore(100, '\n');
                            if(toupper(delete_it) == 'Y' && cities.remove(city_name))
                                cout << endl << "The city was deleted." << endl;
                            else
                                cout << endl << "No cities were removed from the table." << endl;
                        }

                        else if(results > 1){
                            cout << endl << results << " cities with matching names were found." << endl
                                 << "Enter the id (last field) of the city you want to delete.\n>";
                            cin >> ident;
                            while(cin.fail() || ident < 0){
                                cin.clear();
                                cin.ignore(100, '\n');
                                cout << "Enter an id number greater than 0\n>";
                                cin >> ident;
                            }
                            cin.ignore(100, '\n');
                            cout << endl;
                            if(cities.display_with_id(city_name, ident)){
                                cout << endl << "Do you want to delete this city from the table?\n>";
                                cin >> delete_it;
                                cin.ignore(100, '\n');
                                if(toupper(delete_it) == 'Y' && cities.remove_with_id(city_name, ident))
                                    cout << endl << "The city was deleted." << endl;
                                else
                                    cout << endl << "No cities were removed from the table." << endl;
                            }
                            else
                                cout << endl 
                                     << "Operation failed: None of the listed cities match that info." 
                                     << endl;
                        }                            

                        else
                            cout << endl << "Operation failed: No cities in the table match that name." << endl;

                        cout << endl << "Delete again? [y/n] \n>";
                        cin >> again;
                        cin.ignore(100, '\n');
                        delete [] city_name;
                        city_name = nullptr;
                    }while(toupper(again) == 'Y');
                    again = '\0';
                }
            }
            break;
            
            //call display_country_matches and get the number of items displayed
            case 7:{
                if(cities.empty()) 
                    cout << endl << "Operation Failed: No cities in the table." 
                         << endl << "Add some using menu options 1 or 9." << endl;
                else{
                    do{
                        city_io io;
                        int moved{0};
                        char *country_name{nullptr};
                        cout << endl << "Enter a country name to view all cities sharing that name.\n>";
                        if(!io.dynamic_read(country_name, SIZE))
                            cout << endl << "Error!" << endl;
                        cout << endl;
                        moved = cities.display_country_matches(country_name);
                        if(!moved)
                            cout << endl << "Operation failed: No matching countries could be found." << endl;

                        else 
                            cout << endl << moved 
                                 << " matches displayed above." << endl;

                        cout << endl << "Search again? [y/n] \n>";
                        cin >> again;
                        cin.ignore(100, '\n');
                        delete [] country_name;
                    }while(toupper(again) == 'Y');
                    again = '\0';
                }
            }
            break;
            
            //call analyze to get metrics about the table
            case 8:{
                if(cities.empty()) 
                    cout << endl << "Operation Failed: No cities in the table." 
                         << endl << "Add some using menu options 1 or 9." << endl;
                else{
                    int stored{0};
                    float percent{0.00}, ideal{0.00}, actual{0.00};
                    int size{0}, items_read{0} ,index{0};
                    cities.analyze(percent, ideal, actual, size, items_read);
                    cout << endl << items_read << " Items were read in, and the table contained "
                         << size << " indexes." << endl
                         << "The ideal average cites per index would be: " 
                         << ideal << endl << "The actual was: "
                         << actual << endl << percent << "% of index position were empty."
                         << endl;
                    do{
                        cout << endl << "Enter an index to view the items stored there.\n>";
                        cin >> index;
                        cin.ignore(100,'\n');
                        std::cout << "\033[0;31m\033" << "\033[2J\033[1;1H" 
                                  << std::endl << "##########Table Index: " 
                                  << index << "##########" << "\033[0m" << endl;
                        stored = cities.display_index(index);
                        cout << endl << stored << " cities stored at index " << index << '.'
                             << endl << "View another index? [y/n] \n>";
                        cin >> again;
                        cin.ignore(100, '\n');
                    }while(toupper(again) == 'Y');
                    again = '\0';
                }
            }
            break;

            case 9:{
                //read in from the file
                city_io io;
                char *filename{nullptr};
                int file_status{0};
                cout << endl << "What is the name of the file to load from?\n>";
                if(!io.dynamic_read(filename, SIZE)) 
                    cout << endl << "Error!" << endl;
                file_status = cities.file(filename);
                if(file_status >= 0) 
                    cout << endl << file_status << " cities loaded." << endl;
                else if(file_status == -1)
                    cout << endl << "Operation Failed: No file by the name \"" << filename 
                         << "\" was found." << endl;
                else if(file_status == -2)
                    cout << endl << "Operatipn Failed: \"" << filename 
                         << "\" was found, but contains no entries." << endl;
                else if(file_status == -3)
                    cout << endl << "Operation Failed: \"" << filename 
                         << "\" was found, but encountered an error while loading." 
                         << endl;
                delete [] filename;
            }
            break;
        }
    }
} 
