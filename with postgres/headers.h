#ifndef HEADERS_H
#define HEADERS_H

#include <iostream>
#include <string>
#include <conio.h>
#include <httplib.h>
#include <Windows.h>
#include <filesystem>
#include <vector>
#include <libpq-fe.h>
#include <curl/curl.h>
#include <clocale>
#include <nlohmann/json.hpp>

extern const char* conninfo;
extern PGconn* conn;
extern PGresult* res;

using json = nlohmann::json;
using namespace std;


json GetWeather(const string cityID, const string key);
void addUser(json json_data);
void handle_post_reg(const httplib::Request& req, httplib::Response& res);
bool authenticateUser(const string& name, const string& password);
void default_value(const httplib::Request& req, httplib::Response& res);
string getDataUser(string name);
string GetSearchData(const string& name, const string& city_name);
void additional_data(const std::string& name, const bool& session, const httplib::Request& req, httplib::Response& res);
void delete_geo(const std::string& name, const bool& session, const httplib::Request& req, httplib::Response& res);


#endif