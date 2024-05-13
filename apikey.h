#include "SimpleIni.h"


CSimpleIniA api;
SI_Error err_api = api.LoadFile("config.ini");

string apiKey = api.GetValue("API", "key", "DEFAULT_API_KEY");
