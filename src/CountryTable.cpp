#include "CountryTable.h"




int CountryTable::hash(std::string countryCode)
{
    int hashValue = 0;
    if (countryCode.size() != 2)
    {
        return hashValue;
    }

    hashValue = ((int(countryCode[0])-65 ) <<3 | (int(countryCode[1])-65));
    return hashValue; 
}

