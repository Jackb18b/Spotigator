#include <vector>
#include <string>
#include <iostream>
//#include <iomanip>
#include "Song.h"
#include "CountryTable.h"
#include "RBtree.h"
#include <chrono>




int main()
{
    std::vector<Song> songs;
    //std::set<std::pair<std::string, std::string>> sameDateCountry_Song;
    CountryTable table;
    RBtree Dates;

    std::cout << "[*] Beginning file reading!" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    fileHandler(songs, 200000); // reading 50000 songs atm
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout << "\n" << duration.count() << " seconds to read 200,000 songs\n";
    
    
    std::cout << "Earliest date included: " << songs.back().snapshot_date << "\n\n";
    for (auto &song : songs)
    {
        table.insertSong(song);

    }
    std::string date = "2024-01-15";
    start = std::chrono::high_resolution_clock::now();
    table.displayTopTen("JP", date);
    stop = std::chrono::high_resolution_clock::now();
    auto durationms = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "\n" << duration.count() << " microseconds to find and print top 10\n";
    
    
    return 0;
}