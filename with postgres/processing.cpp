#include "postgresDB.h"
#include "Weather.h"

void addUser(const json json_data)
{
    string name = json_data["name"];
    string password = json_data["password"];
    int location = json_data["location"];
    json weather = GetWeather(to_string(location), "main");
    string city_name = GetWeather(to_string(location), "name");
    addUserDB(name, password, location, weather, city_name);
}

void handle_post_reg(const httplib::Request& req, httplib::Response& res) {
    if (req.has_header("Content-Type") && req.get_header_value("Content-Type") == "application/json") {
        json json_data = json::parse(req.body);

        res.set_content("Данные успешно получены", "text/plain");
        addUser(json_data);
    }
    else {
        res.status = 400;
        res.set_content("Неверный формат данных", "text/plain");
    }
}

bool authenticateUser(const string& name, const string& password) {

    res = authenticateUserDB(name, password);

    if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res) > 0) {
        int count = atoi(PQgetvalue(res, 0, 0));
        PQclear(res);
        return count > 0;
    }
    else {
        cerr << "Failed to fetch data from database: " << PQerrorMessage(conn) << ::endl;
        PQclear(res);
        return false;
    }
}

void default_value(const httplib::Request& req, httplib::Response& res)
{
    res.set_content("Привет", "text/plain");
}

string getDataUser(const string name)
{
    res = getDataUserDB(name);
    string user_data;
    for (int row = 0; row < PQntuples(res); ++row) {
        for (int col = 0; col < PQnfields(res); ++col) {
            user_data += PQgetvalue(res, row, col);
            user_data += " | ";
        }
        user_data += "\n";
    }

    PQclear(res);

    return user_data;
}

string GetSearchData(const string& name, const string& city_name)
{
    res = searchDataDB(name, city_name);

    string user_data;
    for (int row = 0; row < PQntuples(res); ++row) {
        for (int col = 0; col < PQnfields(res); ++col) {
            user_data += PQgetvalue(res, row, col);
            user_data += " | ";
        }
        user_data += "\n";
    }

    PQclear(res);
    return user_data;
}

void additional_data(const string& name, const bool& session, const httplib::Request& req, httplib::Response& res)
{
    if (req.has_header("Content-Type") && req.get_header_value("Content-Type") == "application/json" && session) {
        json json_data = json::parse(req.body);
        int location = json_data["location"];
        json weather = GetWeather(to_string(location), "main");
        string city_name = GetWeather(to_string(location), "name");

        pushbackDataDB(name, location, weather, city_name);
    }
    else {
        res.status = 400;
        res.set_content("Неверный формат данных", "text/plain");
    }
}

void delete_geo(const string& name, const bool& session, const httplib::Request& req, httplib::Response& res)
{
    if (req.has_header("Content-Type") && req.get_header_value("Content-Type") == "application/json") {
        json json_data = json::parse(req.body);
        string city_name = json_data["city_name"];

        delete_dataDB(name, city_name);
    }
    else {
        res.status = 400;
        res.set_content("Неверный формат данных", "text/plain");
    }
}



