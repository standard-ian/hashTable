/*
Ian Leuty CS163 July 25 2024 ileuty@pdx.edu

This file contains the interface for client side io.
Might be better to use static memory in later revisions
*/

#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>
#include <cmath>

#ifndef CLIENT
#define CLIENT

const int SIZE{150}; //temp char array size

//client io struct with dynamic mem to load into from file
struct city_io{
    //constructor
    city_io(); 
    //destructor
    ~city_io(); 
    //read in from the user a cities data
    int read();
    //dynamically read characters
    int dynamic_read(char *&field, const int TEMP);
    
    char *city;
    char *city_ascii;
    char *lat;
    char *lng;
    char *country;
    char *iso2;
    char *iso3;
    char *state;
    char *capital_type;
    double pop;
    double id;
};
#endif
