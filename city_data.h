/*
Ian Leuty CS163 July 25 2024 ileuty@pdx.edu

This file contains the interface for the city data object

A city consists of: 
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

#ifndef DATA
#define DATA
//underlying data class for the table
class city_data{
    public: 
        //constructor
        city_data();
        //detructor
        ~city_data();
        //manages the reading in of a line
        int load(std::ifstream &filein); 
        //manages the reading of strings between delims (one char*)
        int get_from_file(std::ifstream &filein, char *&field, char delim); 
        //callable destructor for one city object
        int delete_city();
        //display once city with all its data inline
        int display() const;
        //sets data members of city_data to those from a city_io struct
        int build(city_io &source); 
        //copies data members of city_data object to another
        int copy(const city_data &source);
        //is_matches to check private data against keys 
        bool is_match_city(char *key) const;
        bool is_match_country(char *key) const;
        bool is_match_id(int keyid);

        //retrieve name or country as lowercase chars*
        void lower_name(char *&name) const;
        void lower_country(char *&name) const;

    private:
        char *city;
        char *city_ascii;
        char *lat;
        char *lng;
        char *country;
        char *iso2;
        char *iso3;
        char *state;
        char *capital_type;
        int pop;
        int id;
};
#endif
