#include "Validation_user.h"
#include "Existed_data.h"


bool validation_new_user(string name)
{

    for (auto el : existedData(users))
    {
        if (el["name"] == name) return 0;
    }
    return 1;
}