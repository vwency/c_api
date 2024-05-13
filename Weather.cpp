#include "Weather.h"
#include "apikey.h"


json GetWeather(const string cityID, const string key)
{
    httplib::Client client("http://api.openweathermap.org");

    string path = "/data/2.5/weather?id=" + cityID + "&appid=" + apiKey;
    auto res1 = client.Get(path.c_str());
    if (res1 && res1->status == 200)
    {
        return json::parse(res1->body)[key];
    }
    else {
        cerr << "Error: Could not get weather data" << endl;
        return 0;
    }

}