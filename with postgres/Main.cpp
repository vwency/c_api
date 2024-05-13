#include <iostream>
#include"headers.h"

using namespace std;
using json = nlohmann::json;

static int DataBaseConnect()
{
    if (PQstatus(conn) == CONNECTION_BAD) {
        cerr << "Ошибка подключения к базе данных: " << PQerrorMessage(conn) << endl;
        PQfinish(conn);
        return 1;
    }

    cout << "Подключение к базе данных успешно!" << endl;

    res = PQexec(conn, "SELECT version();");
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        cerr << "Ошибка выполнения запроса: " << PQerrorMessage(conn) << endl;
        PQclear(res);
        PQfinish(conn);
        return 1;
    }

}
static void svrResponse()
{
    httplib::Server svr;
    bool session = false;
    string session_name;

    svr.Post("/aunth", [&](const auto& req, auto& res) {
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
            res.set_content("Привет", "text/plain");
        }});
        


    svr.Post("/search", [&session_name, &session](const httplib::Request& req, httplib::Response& res) {
        if (req.has_header("Content-Type") && req.get_header_value("Content-Type") == "application/json" && session) {
            json json_data = json::parse(req.body);
            string city_name = json_data["city_name"];
            res.set_content(GetSearchData(session_name, city_name), "text/plain");
        }
        else {
            res.status = 400;
            res.set_content("Неверный формат данных", "text/plain");
        }
        });

    svr.Post("/delete", [&session_name, &session](const httplib::Request& req, httplib::Response& res) {
        delete_geo(session_name, session, req, res);
        });

    svr.Post("/add", [&session_name, &session](const httplib::Request& req, httplib::Response& res) {
        additional_data(session_name, session, req, res);
        });

    svr.set_error_handler([](const auto& req, auto& res) {
        res.set_redirect("/", 302);
        });

    svr.Post("/register", handle_post_reg);

    svr.Post("/logout", [&](const auto& req, auto& res) {
        session = false;
        });
     
    svr.listen("127.0.0.1", 8080);

    cout << "Data inserted successfully\n";

    PQclear(res);
    PQfinish(conn);
}


int main() {
    
    SetConsoleOutputCP(1251);

    DataBaseConnect();
    svrResponse();
    
    _getch();
    return 0;
}