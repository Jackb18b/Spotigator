#include <vector>
#include <string>
#include <iostream>
//#include <iomanip>
#include "Song.h"
#include "CountryTable.h"




int main()
{
    std::vector<Song> songs;
    //std::set<std::pair<std::string, std::string>> sameDateCountry_Song;
    std::cout << "[*] Beginning file reading!" << std::endl;
    fileHandler(songs, 5000); // reading 50000 songs atm
    // string date = "2024-03-07";
    // std::cout << std::setprecision(10);
    // std::cout << dateToInt(date);
    
    return 0;
}