#ifndef Weather_H
#define Weather_H

#include <iostream>
#include <string>
#include <httplib.h>
#include <libpq-fe.h>
#include <curl/curl.h>
#include <nlohmann/json.hpp>


using json = nlohmann::json;
using namespace std;

json GetWeather(const string cityID, const string key);

#endif