#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <conio.h>	
#include <httplib.h>
#include <filesystem>
#include <vector>
#include <curl/curl.h>
#include <clocale>
#include <nlohmann/json.hpp>


using namespace nlohmann;
using namespace std;


extern string users;
extern string weather_data;


void addUser(json json_data);
void registration(const httplib::Request& req, httplib::Response& res);
bool authenticateUser(const string& name, const string& password);
string getDataUser(string name);
string GetSearchData(const string& name, const string& city_name);
void add_data(const std::string& name, const bool& session, const httplib::Request& req, httplib::Response& res);
void delete_weather(const std::string& name, const bool& session, const httplib::Request& req, httplib::Response& res);

#endif