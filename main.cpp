#include <vector>
#include <string>
#include <fstream>
#include <istream>
#include <sstream>
#include <regex>
#include <cstring>
#include "Song.h"


using namespace std;

vector<string> splitStrings(const string &line)
{
    std::regex reg("\\\"(.*?)\\\"");
    std::sregex_iterator iter(line.begin(), line.end(), reg);
    std::sregex_iterator end;
    // // Vector to store the split strings
    // std::vector<std::string> tokens{ iter, std::sregex_iterator() };
    vector<string> tokens;
    while (iter != end)
    {
        string hold = iter->str();
        hold = hold.substr(1,hold.size()-2);
        tokens.emplace_back(hold);

        ++iter;
    }

    return tokens;
}

Song readSong(const string &line)
{
    vector<string> cols = splitStrings(line);   

    try{
        Song song(cols[0],cols[1],cols[2],stoi(cols[3]),stoi(cols[4]),
            stoi(cols[5]),cols[6],cols[7],stoi(cols[8]),cols[9], //9 is bool
            stoi(cols[10]),cols[11],cols[12],stof(cols[13]),stof(cols[14]),
            stoi(cols[15]),stof(cols[16]),stoi(cols[17]),stof(cols[18]),stof(cols[19]),
            stof(cols[20]),stof(cols[21]),stof(cols[22]),stof(cols[23]),stoi(cols[24]));

            return song;
    }
    catch(exception& exept){
        Song song;
        return song;
    }

    
}


void fileHandler(std::vector<Song> &songs)
{
    // Set filePath to downloaded csv file (Change later??)
    string filePath = "C:\\Users\\jackb\\Documents\\UniversityOfFlorida\\Spring2024\\COP3530\\Project3\\universal_top_spotify_songs.csv";
    fstream csvFile(filePath, std::ios_base::in);

    string line;
    getline(csvFile, line); // header line

    int count = 0;
    
    while(csvFile.good() && (count < 100))
    {
        getline(csvFile, line);
        songs.emplace_back(readSong(line));
        count++;
    }
    

}




int main()
{
    std::vector<Song> songs;
    fileHandler(songs);
    return 0;
}