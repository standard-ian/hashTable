/*
Ian Leuty CS163 July 25 2024 ileuty@pdx.edu

This file contains the implementation of the city data class 
member functions.

The will include: 
    -read in one city
    -display 1 city
    -is match country, unique id, and city_ascii name
    -copy a city from another city_data object
    -build a city from a city_io struct 
    -get lowercase country or city_ascii name

*/

#include "city_data.h"

using namespace std;

//constructor
city_data::city_data(){
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

//destructor
city_data::~city_data(){
    delete [] city;
    delete [] city_ascii;
    delete [] lat;
    delete [] lng;
    delete [] country;
    delete [] iso2;
    delete [] iso3;
    delete [] capital_type;
    delete [] state;
    pop = 0;
    id = 0;
    city = nullptr;
    city_ascii = nullptr;
    lat = nullptr;
    lng = nullptr;
    country = nullptr;
    iso2 = nullptr;
    iso3 = nullptr;
    state = nullptr;
    capital_type = nullptr;
}

//read in from a file dynamically
int city_data::get_from_file(ifstream &filein, char *&field, char delim){
    char temp[SIZE];
    filein.get(temp, SIZE, delim);
    if(filein.peek() != delim)
        return 0;
    filein.ignore(100, delim);
    field = new char[strlen(temp) + 1];
    strcpy(field, temp);
    return 1;
}

//loads in one city's data
int city_data::load(ifstream &filein){
        if(!get_from_file(filein, city, ',')) return 0;
        if(!get_from_file(filein, city_ascii, ',')) return 0;
        if(!get_from_file(filein, lat, ',')) return 0;
        if(!get_from_file(filein, lng, ',')) return 0;
        if(!get_from_file(filein, country, ',')) return 0;
        if(!get_from_file(filein, iso2, ',')) return 0;
        if(!get_from_file(filein, iso3, ',')) return 0;
        if(!get_from_file(filein, state, ',')) return 0;
        if(!get_from_file(filein, capital_type, ',')) return 0;
        filein >> pop;
        filein.ignore(100, ',');
        filein >> id;
        filein.ignore(100, '\n');
        filein.peek();
        if(filein.eof()) return 0; //return 0 if end of file
        return 1; //else return success state
}

//delete a city (callable destructor)
int city_data::delete_city(){
    if(!city || !city_ascii || !lat ||
        !lng || !country || !iso2 ||
        !iso3 || !capital_type)
        return 0;
    delete [] city; delete [] city_ascii;
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
    return 1;
}

//setter
int city_data::build(city_io &source){
    if(!source.city || !source.city_ascii || !source.lat ||
        !source.lng || !source.country || !source.iso2 ||
        !source.iso3 || !source.capital_type)
        return 0;
    city = new char[strlen(source.city) + 1];
    strcpy(city, source.city);
    city_ascii = new char[strlen(source.city_ascii) + 1];
    strcpy(city_ascii, source.city_ascii);
    lat = new char[strlen(source.lat) + 1];
    strcpy(lat, source.lat);
    lng = new char[strlen(source.lng) + 1];
    strcpy(lng, source.lng);
    country = new char[strlen(source.country) + 1];
    strcpy(country, source.country);
    iso2 = new char[strlen(source.iso2) + 1];
    strcpy(iso2, source.iso2);
    iso3 = new char[strlen(source.iso3) + 1];
    strcpy(iso3, source.iso3);
    state = new char[strlen(source.state) + 1];
    strcpy(state, source.state);
    capital_type = new char[strlen(source.capital_type) + 1];
    strcpy(capital_type, source.capital_type);
    pop = source.pop;
    id = source.id;
    return 1;
}

//copy a city
int city_data::copy(const city_data &source){
    if(!source.city || !source.city_ascii || !source.lat ||
        !source.lng || !source.country || !source.iso2 ||
        !source.iso3 || !source.capital_type)
        return 0;
    city = new char[strlen(source.city) + 1];
    strcpy(city, source.city);
    city_ascii = new char[strlen(source.city_ascii) + 1];
    strcpy(city_ascii, source.city_ascii);
    lat = new char[strlen(source.lat) + 1];
    strcpy(lat, source.lat);
    lng = new char[strlen(source.lng) + 1];
    strcpy(lng, source.lng);
    country = new char[strlen(source.country) + 1];
    strcpy(country, source.country);
    iso2 = new char[strlen(source.iso2) + 1];
    strcpy(iso2, source.iso2);
    iso3 = new char[strlen(source.iso3) + 1];
    strcpy(iso3, source.iso3);
    state = new char[strlen(source.state) + 1];
    strcpy(state, source.state);
    capital_type = new char[strlen(source.capital_type) + 1];
    strcpy(capital_type, source.capital_type);
    pop = source.pop;
    id = source.id;
    return 1;
}

//display 1 city;
int city_data::display() const{
    if(!city || !city_ascii || !lat ||
        !lng || !country || !iso2 ||
        !iso3 || !capital_type)
        return 0;
    cout << city << ", "
         << city_ascii << ", "
         << lat << ", "
         << lng << ", "
         << country << ", "
         << iso2 << ", "
         << iso3 << ", "
         << state << ", "
         << capital_type << ", "
         << pop << ", "
         << id << endl;
         return 1;
}

//check if is a match by city_ascii
bool city_data::is_match_city(char *key) const{
    if(strcmp(key, city_ascii) == 0) return 1;
    return 0;
}

//check if is a match by country
bool city_data::is_match_country(char *key) const{
    if(strcmp(key, country) == 0) return 1;
    return 0;
}

//check if match by id
bool city_data::is_match_id(int keyid){
    if(id == keyid) return 1;
    return 0;
}

/*
these next two functions maybe could just get an int value instead of the char
however, hash_function1 concatenates ascii values & requires an array of values
to do so. we could concatenate here, and return 1 int but it would be huge. 
if we solved this by modding by table size, might as well put the whole hash function in the 
underlying data type, but that also seems weird. 
so these are getters, but they convert to lower case at the data level at least. :p
*/

//get the name of a city object with all lowercase chars
void city_data::lower_name(char *&some_name) const{
    int length{0};
    some_name = new char[strlen(city_ascii) + 1];
    strcpy(some_name, city_ascii);
    length = strlen(some_name) + 1;
    for(int i = 0; i < length; ++i){
        if(isupper(some_name[i]))
            some_name[i] = tolower(some_name[i]);
    }
}

//retrieve county name from a data object as lowercase chars
void city_data::lower_country(char *&name) const{
    int length{0};
    name = new char[strlen(country) + 1];
    strcpy(name, country);
    length = strlen(name) + 1;
    for(int i = 0; i < length; ++i){
        if(isupper(name[i]))
            name[i] = tolower(name[i]);
    }
}
