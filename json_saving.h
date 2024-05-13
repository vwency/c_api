#ifndef JSON_SAVING_H
#define JSON_SAVING_H

#include "Main.h"
#include<fstream>


void addUser(string name, string password);
void pushData(string name, int location, json weather, string city_name);
void delete_data(string name, string city_name);
string getDataUser(string name);
string searchData(string name, string city_name);


#endif