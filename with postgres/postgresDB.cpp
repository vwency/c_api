#include "postgresDB.h"

void addUserDB(string name, string password, int location, json weather, string city_name)
{

    string sqlQuery = "INSERT INTO users (name, password) VALUES ('" + name + "', '" + password + "');";
    res = PQexec(conn, sqlQuery.c_str());

    sqlQuery = "INSERT INTO geo_data(name, id, weather, city_name) VALUES ('" + name + "'," + to_string(location).c_str() + ", '" + weather.dump() + "', '" + city_name + "')";
    res = PQexec(conn, sqlQuery.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        cerr << "Insert failed: " << PQerrorMessage(conn) << ::endl;
        PQclear(res);
        PQfinish(conn);
    }
    cout << "Data inserted successfully" << endl;
    PQclear(res);
}

void pushbackDataDB(string name, int location, json weather, string city_name)
{
    string query = "INSERT INTO geo_data (name, id, weather, city_name) VALUES ('" + name + "', '" + to_string(location) + "', '" + weather.dump() + "', '" + city_name + "')";
    res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        cerr << "Query execution failed: " << PQerrorMessage(conn) << endl;
        PQclear(res);
        PQfinish(conn);
    }

    cout << "Data inserted successfully." << endl;
    PQclear(res);
}

void delete_dataDB(string name, string city_name)
{
    string query = "DELETE FROM geo_data WHERE name = '" + name + "' AND city_name = '" + city_name + "'";
    res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        cerr << "Query execution failed: " << PQerrorMessage(conn) << endl;
        PQclear(res);
        PQfinish(conn);
    }
    PQclear(res);
}

PGresult *getDataUserDB(string name)
{
    string query = "SELECT * FROM geo_data WHERE name = '" + name + "'";
    res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        PQclear(res);
        PQfinish(conn);
    }

    return res;
}

PGresult *authenticateUserDB(string name, string password)
{
    const string sql = "SELECT COUNT(*) FROM users WHERE name = $1  AND password = $2; ";
    const char *paramValues[2] = {name.c_str(), password.c_str()};
    const int paramLengths[2] = {static_cast<int>(name.length()), static_cast<int>(password.length())};
    const int paramFormats[2] = {0, 0};

    res = PQexecParams(conn, sql.c_str(), 2, NULL, paramValues, paramLengths, paramFormats, 0);
    return res;
}

PGresult *searchDataDB(string name, string city_name)
{
    string query = "SELECT id, weather, city_name FROM geo_data WHERE name = '" + name + "' AND city_name = '" + city_name + "'";
    auto res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        PQclear(res);
        PQfinish(conn);
    }
    return res;
}