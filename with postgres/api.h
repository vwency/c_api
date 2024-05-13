#include "SimpleIni.h"

CSimpleIniA api;
SI_Error err = api.LoadFile("config.ini");

const string apiKey = api.GetValue("API", "key", "DEFAULT_API_KEY");

