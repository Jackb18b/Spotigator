#include <vector>
#include <string>
#include <fstream>
#include <istream>
#include <sstream>
#include "Song.h"


using namespace std;



Song readSong(std::string &line)
{
    vector<string> cols;
    stringstream ss(line);

    while(ss.good())
    {
        string sub;
        getline(ss, sub, ',');
        cols.push_back(sub);
    }
    try{
        Song song(cols[0],cols[1],cols[2],stoi(cols[3]),stoi(cols[4]),
            stoi(cols[5]),cols[6],cols[7],stoi(cols[8]),cols[9], //9 is bool
            stoi(cols[10]),cols[11],cols[12],stof(cols[13]),stof(cols[14]),
            stoi(cols[15]),stof(cols[16]),stoi(cols[17]),stof(cols[18]),stof(cols[19]),
            stof(cols[20]),stof(cols[21]),stof(cols[22]),stof(cols[23]),stoi(cols[24]));

            return song;
    }
    catch(exception& exept){
        return;
    }

    //return song;
}


void fileHandler(std::vector<Song> &songs)
{
    // Set filePath to downloaded csv file (Change later??)
    string filePath = "";
    fstream csvFile(filePath, std::ios_base::in);

    string line;
    getline(csvFile, line); // header line
    
    while(csvFile.good())
    {
        getline(csvFile, line);
        songs.emplace_back(readSong(line));
    }

}




int main()
{
    std::vector<Song> songs;
    fileHandler(songs);
    return 0;
}