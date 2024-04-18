#include <vector>
#include <string>
#include <iostream>
#include "Song.h"
#include "CountryTable.h"





int main()
{
    std::vector<Song> songs;
    std::cout << "[*] Beginning file reading!" << std::endl;
    fileHandler(songs, 50000); // reading 50000 songs atm
    return 0;
}