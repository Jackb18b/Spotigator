#include <vector>
#include <regex>
#include <fstream>
#include <istream>
#include <iostream>
#include "Song.h"


using namespace std;

std::string Song::printSong()
{
    int commaIndex = artist.find(',');
    std::string shortArtist;
    // shortArtist is for display purposes
    if (commaIndex != std::string::npos && commaIndex + 1 < artist.size()) {
        shortArtist = artist.substr(0,commaIndex);
    } else {
        shortArtist = artist;
    }
    std::string song = std::to_string(daily_rank) + ". " + name + " by " + shortArtist + "\n";
    std::cout << name << " by " << artist << ": " << daily_rank << "\n";

    return song;
}


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

// bool sameDates(Song &songA, Song &songB){
//     return songA.snapshot_date == songB.snapshot_date;
// }

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


void fileHandler(vector<Song> &songs, int numberOfSongs)
{
    // Set filePath to downloaded csv file (Change later??)
    string filePath = "..\\..\\Data\\universal_top_spotify_songs.csv";
    fstream csvFile(filePath, std::ios_base::in);
    if (!csvFile)
    {
        cout << "[-] File failed to open!\n";
        exit(1);
    }

    string line;
    getline(csvFile, line); // header line
    int count = 0;

    //TreeNode dateTree;
    //Song baseSong;

    while(csvFile.good() && (count < numberOfSongs))
    {
        if (count % 50000 == 0 && count > 0)
        {
            cout << "[*] Read " << count << " songs\n";
        }

        getline(csvFile, line);
        Song currSong = readSong(line);
        
        // if (count == 0) {
        //     baseSong = currSong;
        // }
        songs.emplace_back(currSong);
        //dateTree.insert(currSong.snapshot_date, currSong.country);
        // if (sameDates(baseSong, currSong)) {
        //     sameDateCountry_Song.emplace(currSong.country, currSong.spotify_id);
        // } else baseSong = currSong;
        count++;
    }
    cout << "[+] Read all songs!\n";
    // cout << "dateTree height: " << dateTree.getHeight(dateTree.root) << endl;
    // cout << "dateTree inorder: " << endl;
    // dateTree.inorderHelper(dateTree.root);
    // cout << dateTree.orderedList << endl;

}
