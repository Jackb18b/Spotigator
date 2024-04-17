#include <vector>
#include <iostream>
#include <fstream>

struct Song
{
    // Columns from Kaggle dataset
    std::string spotify_id;
    std::string name;
    std::string artist;
    int daily_rank;
    int daily_movement;
    int weekly_movement;
    std::string country;
    std::string snapshot_date;
    int popularity;
    int duration_ms;
    std::string album_name;
    std::string album_release_date;

    struct Style
    {
        bool is_explicit;
        float danceability;
        float energy;
        int key;
        float loudness;
        int mode;
        float speechiness;
        float acousticness;
        float instrumentalness;
        float liveness;
        float valence;
        float tempo;
        int time_signature;
    };
};


void fileHandler()
{
    // Set filePath to downloaded csv file (Change later??)
    std::string filePath = "";
    std::fstream csvFile(filePath, std::ios_base::in);

}



int main()
{

    return 0;
}