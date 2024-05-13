#ifndef postgresDB_H
#define postgresDB_H

#include"headers.h"



void addUserDB(string name, string password, int location, json weather, string city_name);
void pushbackDataDB(string name, int location, json weather, string city_name);
void delete_dataDB(string name, string city_name);
PGresult* getDataUserDB(string name);
PGresult* authenticateUserDB(string name, string password);
PGresult* searchDataDB(string name, string city_name);

#endif	