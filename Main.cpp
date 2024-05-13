#include <iostream>
#include "Main.h"
#include<locale.h>
using namespace std;
using namespace nlohmann;

void server()
{
    httplib::Server svr;
    bool session = false;
    string session_name;

    svr.Post("/login", [&](const auto& req, auto& res) {
        json data = json::parse(req.body);

        string name = data["name"].get<string>();
        string password = data["password"].get<string>();


        if (authenticateUser(name, password))
        {
            res.set_content("Authentication successful", "text/plain");
            session = true;
            session_name = name;

        }
        else {
            res.set_content("Authentication failed", "text/plain");
            res.status = 401;
        }
        });

    svr.Get("/", [&session_name, &session](const auto& req, auto& res) {
        if (session)
        {
            res.set_content(getDataUser(session_name), "text/plain");
        }
        else
        {
            res.set_content("You not sign in!", "text/plain");
            res.status = 206;
        }});

    svr.Post("/search", [&session_name, &session](const auto& req, auto& res) {
        if (req.has_header("Content-Type") && req.get_header_value("Content-Type") == "application/json" && session) {
            json json_data = json::parse(req.body);
            string city_name = json_data["city_name"];
            res.set_content(GetSearchData(session_name, city_name), "text/plain");
        }
        else if (!session)
        {
            res.status = 400;
            cout << "Not signed in. \n";
        }
        else {
            res.status = 400;
            res.set_content("Incorrect data format.", "text/plain");
        }
        });

    svr.Get("/get_session", [&session_name, &session](const auto& req, auto& res) {
        if (session) {
            res.set_content(session_name, "text/plain");
        }
        else if (!session)  
        {
            res.status = 400;
            cout << "Not signed in. \n";
        }
        else {
            res.status = 400;
            res.set_content("Incorrect data format.", "text/plain");
        }
        });

    svr.Post("/delete", [&session_name, &session](const auto& req, auto& res) {
        delete_weather(session_name, session, req, res);
        });

    svr.Post("/add", [&session_name, &session](const auto& req, auto& res) {
        add_data(session_name, session, req, res);
        });

    svr.Post("/register", registration);

    svr.Post("/logout", [&](const auto& req, auto& res) {
        session = false;
        });

    svr.set_error_handler([](const auto& req, auto& res) {
        res.set_redirect("/", 302);
        });


    svr.listen("127.0.0.1", 8080);

    cout << "Data inserted successfully\n";

}


int main() {
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    server();

    return 0;
}