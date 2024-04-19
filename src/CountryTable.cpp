#include "CountryTable.h"




int CountryTable::hashCountry(const std::string &countryCode)
{
    int hashValue = 0;
    if (countryCode.size() != 2)
    {
        return hashValue;
    }

    hashValue = ((int(countryCode[0])-65 ) <<5 | (int(countryCode[1])-65));
    return hashValue; 
}

int CountryTable::hashDate(const std::string &date)
{
    int hashValue = 0;
    std::string monthDay = "";
    if (date.length() != 10)
    {
        
        return hashValue;
    }

    monthDay += date.substr(5,2);
    monthDay += date.substr(8,2);

    hashValue = std::stoi(monthDay);

    return hashValue;
}

void CountryTable::insertSong(Song &song)
{
    int hashedCountry = hashCountry(song.country);
    int hashedDate = hashDate(song.snapshot_date);
    Table[hashedCountry][hashedDate].emplace_back(song);
}