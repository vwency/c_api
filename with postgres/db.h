#include "SimpleIni.h"


CSimpleIniA db;
SI_Error err_db = db.LoadFile("config.ini");

string host = db.GetValue("Database", "host", "localhost");
string port = db.GetValue("Database", "port", "5432");
string username = db.GetValue("Database", "username", "default_username");
string password = db.GetValue("Database", "password", "default_password");
string database = db.GetValue("Database", "database", "default_database");


const string conninfo1 = "host=" + host +
" port=" + port +
" user=" + username +
" password=" + password +
" dbname=" + database;

const char* conninfo = conninfo1.c_str();

PGconn* conn = PQconnectdb(conninfo);
PGresult* res = PQexec(conn, "SELECT version();");
