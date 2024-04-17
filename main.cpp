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
            stoi(cols[10]),cols[11],cols[12],cols[13],cols[14],
            cols[15],cols[16],cols[17],cols[18],cols[19],
            cols[20],cols[21],cols[22],cols[23],cols[24]);
    }
    catch(exception& exept){
        return;
    }

    return song;
}


void fileHandler(std::vector<Song> &songs)
{
    // Set filePath to downloaded csv file (Change later??)
    string filePath = "C:\\Users\\jackb\\Documents\\UniversityOfFlorida\\Spring2024\\COP3530\\Project3\\universal_top_spotify_songs.csv";
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