#pragma once
#include "SimpleIni.h"

CSimpleIniA jsn;
SI_Error err_jsn = jsn.LoadFile("config.ini");

 string users = jsn.GetValue("JSON_DATA", "users", "default_json_data_user");
 string weather_data = jsn.GetValue("JSON_DATA", "weather_data", "default_weather_data");
