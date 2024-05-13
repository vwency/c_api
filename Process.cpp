#include "Main.h"
#include "json_saving.h"
#include "Validation_user.h"
#include "Weather.h"
#include "Existed_data.h"
#include "json_names.h"



void addUser(const json json_data)
{
    string name = json_data["name"];
    string password = json_data["password"];
    int location = json_data["location"];
    json weather = GetWeather(to_string(location), "main");
    string city_name = GetWeather(to_string(location), "name");

    pushData(name, location, weather, city_name);
    addUser(name, password);
}

void registration(const httplib::Request& req, httplib::Response& res) {
    if (req.has_header("Content-Type") && req.get_header_value("Content-Type") == "application/json") {
        json json_data = json::parse(req.body);
        string name = json_data["name"];

        if (validation_new_user(name))
        {
            res.set_content("Registration successful. ", "text/plain");
            addUser(json_data);
        }

        else cout << "User arleady existed! \n";
    }
    else {
        res.status = 400;
        res.set_content("Incorrect data format. ", "text/plain");
    }
}

bool authenticateUser(const string& name, const string& password) {

    json userList = existedData(users);
    for (auto el : userList)
    {
        if (el["name"] == name && el["password"] == password)
        {
            cout << "You was loggined successfully\n";
            return 1;
        }
    }
    cout << "Authentication failed. \n";
    return 0;
}

void default_value(const httplib::Request& req, httplib::Response& res)
{
    res.set_content("Привет", "text/plain");
}

string GetSearchData(const string& name, const string& city_name)
{
    
    return searchData(name, city_name);
}

void add_data(const string& name, const bool& session, const httplib::Request& req, httplib::Response& res)
{
    if (req.has_header("Content-Type") && req.get_header_value("Content-Type") == "application/json" && session) {
        json json_data = json::parse(req.body);
        int location = json_data["location"];
        json weather = GetWeather(to_string(location), "main");
        string city_name = GetWeather(to_string(location), "name");

        pushData(name, location, weather, city_name);
    }
    else if (!session)
    {
        cout << "You not authorized! \n";
    }
    else {
        res.status = 400;
        res.set_content("Incorrect data format.", "text/plain");
    }
}

void delete_weather(const string& name, const bool& session, const httplib::Request& req, httplib::Response& res)
{
    if (req.has_header("Content-Type") && req.get_header_value("Content-Type") == "application/json" && session) {
        json json_data = json::parse(req.body);
        string city_name = json_data["city_name"];

        delete_data(name, city_name);
    }
    else if(!session)
    {
        res.status = 400;
        cout << "You not authorized! \n";
    }
    else {
        res.status = 400;
        res.set_content("Incorrect data format.", "text/plain");
    }
}

