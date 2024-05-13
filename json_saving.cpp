#include "json_saving.h"
#include "Existed_data.h"

void addUser(string name, string password)
{
    json json_data = {
       {"name", name},
       {"password", password}
    };


    json existing_data = existedData(users);

    existing_data.push_back(json_data);

    ofstream file(users);
    if (file.is_open()) {
        file << setw(4) << existing_data << endl;
        file.close();
        cout << "Данные успешно записаны в файл " << users << ". \n" << endl;
    }
    else {
        cerr << "Ошибка открытия файла для записи." << endl;
    }
}

void pushData(string name, int location, json weather, string city_name)
{
    json json_data = {
        {"name", name},
        {"location", location},
        {"weather", weather},
        {"city_name", city_name}
    };

    json existing_data = existedData(weather_data);

    existing_data.push_back(json_data);

    ofstream file(weather_data);
    if (file.is_open()) {
        file << setw(4) << existing_data << endl;
        file.close();
        cout << "Данные успешно записаны в файл " << weather_data << ". \n" << endl;
    }
    else {
        cerr << "Ошибка открытия файла для записи." << endl;
    }
}

void delete_data(string name, string city_name)
{
    json data = existedData(weather_data);
    json new_data;
    for (auto c : data)
    {
        if (!(c["name"] == name && c["city_name"] == city_name))
        {
            new_data.push_back(c);
        }
    }

    ofstream file(weather_data);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла для записи." << endl;
        return;
    }

    file << std::setw(4) << new_data << endl;
    file.close();
    cout << "Deletion successfully \n";
}

string getDataUser(string name)
{
    json data = existedData(weather_data);
    json new_data;
    for (auto c : data)
    {
        if (c["name"] == name) new_data.push_back(c);
    }
    return new_data.dump();
}

string searchData(string name, string city_name)
{
    json data = existedData(weather_data);
    json new_data;
    for (auto c : data)
    {
        if (c["name"] == name && c["city_name"] == city_name)
        {
            new_data.push_back(c);
        }
    }
    return new_data.dump();
}