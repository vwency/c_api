#include "Existed_data.h"

json existedData(string filename)
{
    json existing_data;

    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Файл не существует. Создаем новый файл." << endl;
        ofstream create_file(filename);
        create_file.close();
        infile.open(filename);
        if (!infile.is_open()) {
            cerr << "Ошибка создания файла." << endl;
            exit(EXIT_FAILURE);
        }
    }

    try
    {
        string file_content((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
        existing_data = json::parse(file_content);
    }
    catch (const exception& e)
    {
        ;
    }

    infile.close();
    
    return existing_data;
}