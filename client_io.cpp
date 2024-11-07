/*
Ian Leuty CS163 July 25 2024 ileuty@pdx.edu

This file contains the implementation of the client side io functions
uses dynamic memory, could be static to reduce overhead. This is just to read in
cities from the user, & then it is passed to the build of city_data & destructed. 

a city info line contains:
    -city (name) 
    -city_ascii (ASCII name)
    -lat (lattitude)
    -lng (longitude)
    -country
    -iso2 (abbreviation 1)
    -iso3 (abbreviation 2)
    -state (state/region)
    -capital_type (admin code)
    -pop (poulation)
    -id (internal id)
*/

#include "client_io.h"

using namespace std;

//struct constructor
city_io::city_io(){
    city = nullptr;
    city_ascii = nullptr;
    lat = nullptr;
    lng = nullptr;
    country = nullptr;
    iso2 = nullptr;
    iso3 = nullptr;
    state = nullptr;
    capital_type = nullptr;
    pop = 0;
    id = 0;
}

//io struct destructor
city_io::~city_io(){
    delete [] city;
    delete [] city_ascii;
    delete [] lat;
    delete [] lng;
    delete [] country;
    delete [] iso2;
    delete [] iso3;
    delete [] state;
    delete [] capital_type;
    city = nullptr;
    city_ascii = nullptr;
    lat = nullptr;
    lng = nullptr;
    country = nullptr;
    iso2 = nullptr;
    iso3 = nullptr;
    state = nullptr;
    capital_type = nullptr;
    pop = 0;
    id = 0;
}

int city_io::read(){
    cout << endl;
    cout << "Enter a city name with diacritics if applicable.\n>";
    if(!dynamic_read(city, SIZE)) return 0;
    cout << "Enter a city name in ascii characters.\n>";
    if(!dynamic_read(city_ascii, SIZE)) return 0;
    cout << "Enter a lattitude for the city (i.e. -49.223)\n>";
    if(!dynamic_read(lat, SIZE)) return 0;
    cout << "Enter a longitude for the city (i.e 23.1042)\n>";
    if(!dynamic_read(lng, SIZE)) return 0;
    cout << "Enter the country name.\n>";
    if(!dynamic_read(country, SIZE)) return 0;
    cout << "Enter one form of abbreviation (i.e. United States is US)\n>";
    if(!dynamic_read(iso2, SIZE)) return 0;
    cout << "Enter one form of abbreviation (i.e. United States is USA)\n>";
    if(!dynamic_read(iso3, SIZE)) return 0;
    cout << "Enter the state/region/admin name (i.e. for Portland enter Oregon)\n>";
    if(!dynamic_read(state, SIZE)) return 0;
    cout << "Enter the capital_type type for the state (i.e. primary, secondary, admin, null)\n>";
    if(!dynamic_read(capital_type, SIZE)) return 0;
    cout << "Enter the population of the city.\n>";
    cin >> pop;
    cin.ignore(100,'\n');
    cout << "Enter the unique id for the city (i.e. 4423).\n>";
    cin >> id;
    cin.ignore(100, '\n');
    return 1;
}


//dynamically get char* 
int city_io::dynamic_read(char *&field, const int TEMP){
    char temp[TEMP];
    cin.get(temp, TEMP, '\n');
    while(cin.peek() != '\n'){
        cin.ignore(100, '\n');
        cout << "Enter less than " << TEMP << " characters.\n>";
        cin.get(temp, TEMP, '\n');
    };
    cin.ignore(100, '\n');
    field = new char[strlen(temp) + 1];
    if(!strcpy(field, temp)) return 0;
    return 1;
}
