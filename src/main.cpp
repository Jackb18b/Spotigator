#include <vector>
#include <string>
#include <iostream>
//#include <iomanip>
#include "Song.h"
#include "CountryTable.h"
#include "RBtree.h"
#include "SFMLHelper.h"
#include <chrono>




int main()
{
    std::vector<Song> songs;
    //std::set<std::pair<std::string, std::string>> sameDateCountry_Song;
    CountryTable table;
    RBtreeDates Dates;
    int numberOfSongs = 200000;
    // Returns paramVect[country, date]

    std::cout << "[*] Beginning file reading!" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    fileHandler(songs, numberOfSongs); // reading 50000 songs atm
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout << "\n" << duration.count() << " seconds to read " << numberOfSongs << " songs\n";


    std::cout << "Earliest date included: " << songs.back().snapshot_date << "\n\n";
    start = std::chrono::high_resolution_clock::now();
    for (auto &song : songs)
    {

        try
        {
            table.insertSong(song);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }


        //Dates.insertDate(song, song.snapshot_date);
        // if (Dates.root->date < 2023) {
        //     cout << Dates.root->date << endl;
        // }
    }
    stop = std::chrono::high_resolution_clock::now();
    auto duration_load_hash = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << duration_load_hash.count() << " milliseconds to load Hashtable\n";

    start = std::chrono::high_resolution_clock::now();
    for (auto &song : songs)
    {
        //table.insertSong(song);
        Dates.insertDate(song, song.snapshot_date);
        if (Dates.root->date < 2023) {
            cout << Dates.root->date << endl;
        }
    }
    stop = std::chrono::high_resolution_clock::now();
    auto duration_load_table = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "\n" << duration_load_table.count() << " milliseconds to load RBTree\n\n";

    SFMLHelper::displayStartWindow();
    while (true)
    {
        std::vector<std::string> paramVect = SFMLHelper::displayInputWindow();

        std::string date = paramVect[1];
        string country = paramVect[0];


        cout << "\t\tHash Table Top 10:\n";
        start = std::chrono::high_resolution_clock::now();
        std::string hashString = "Hash Table\n" + table.displayTopTen(country, date);
        stop = std::chrono::high_resolution_clock::now();
        auto duration_hash = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "\n" << duration_hash.count() << " microseconds to find and print top 10 from Hashtable\n\n";
        hashString += "\nTime to find in microseconds: " + to_string(duration_hash.count());

        
        cout << "\t\tRed-Black Tree Top 10:\n";
        start = std::chrono::high_resolution_clock::now();
        std::string RBString = "Red Black Tree\n" + Dates.displayTopTen(date, country);
        stop = std::chrono::high_resolution_clock::now();
        auto duration_rbtree = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "\n" << duration_rbtree.count() << " microseconds to find and print top 10 from RBtree\n\n";
        RBString += "\nTime to find in microseconds: " + to_string(duration_rbtree.count());
        //Dates.level_order();
        cout << RBString << endl << hashString;
        SFMLHelper::displayResultsWindow(hashString, RBString);
    }
    return 0;
}