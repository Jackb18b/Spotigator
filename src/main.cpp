#include <vector>
#include <string>
#include <iostream>
#include "Song.h"





int main()
{
    std::vector<Song> songs;
    std::cout << "[*] Beginning file reading!" << std::endl;
    fileHandler(songs, 50000);
    return 0;
}