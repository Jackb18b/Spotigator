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
        //std::cout << "Invalid Date & time\t";
        //std::cout << date << "\n";
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
    if (hashedDate == 0 )
    {
        //std::cout << song.name << "\n";
        return;
    }
    Table[hashedCountry][hashedDate].emplace_back(song);
}

vector<Song> CountryTable::getSongs(std::string country, std::string date)
{
    return Table[hashCountry(country)][hashDate(date)];
}

std::string CountryTable::displayTopTen(std::string country, std::string date)
{
    std::string returnSongs = "";
    vector<Song> topFifty = getSongs(country, date);
    for (int i = 0; i < 10; i++)
    {
        returnSongs += topFifty[i].printSong();
    }
    return returnSongs;
}