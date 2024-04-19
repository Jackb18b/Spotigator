#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Song.h"

using namespace std;



class CountryTable
{
private:
    const int SizeOfTable1 = 800;
    const int SizeOfTable2 = 1231;

    vector<Song>** Table; 



public:
    CountryTable()
    {
        Table = new vector<Song>*[SizeOfTable1];
        for (int i = 0; i < SizeOfTable1; i++)
        {
            Table[i] = new vector<Song>[SizeOfTable2];
        }
    }
    ~CountryTable()
    {
        for (int i = 0; i < SizeOfTable1; i++)
        {
            delete[] Table[i];
        }
        delete[] Table;
    }
    
    int hashDate(const std::string &date);
    int hashCountry(const std::string &countryCode);

    void insertSong(Song &song);

};