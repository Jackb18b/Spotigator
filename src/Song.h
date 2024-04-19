#pragma once
#include <string>
using namespace std;

struct Style
{
    string is_explicit;
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

    void setStyle(string is_explicit,
    float danceability,
    float energy,
    int key,
    float loudness,
    int mode,
    float speechiness,
    float acousticness,
    float instrumentalness,
    float liveness,
    float valence,
    float tempo,
    int time_signature) {

    this->is_explicit = is_explicit;
    this->danceability = danceability;
    this->energy = energy;
    this->key = key;
    this->loudness = loudness;
    this->mode = mode;
    this->speechiness = speechiness;
    this->acousticness = acousticness;
    this->instrumentalness = instrumentalness;
    this->liveness = liveness;
    this->valence = valence;
    this->tempo = tempo;
    this->time_signature = time_signature;

    }
};

class Song
{
private:
    // Columns from Kaggle dataset
    
    string name;
    string artist;
    int daily_rank;
    int daily_movement;
    int weekly_movement;
    
    
    int popularity;
    int duration_ms;
    string album_name;
    string album_release_date;

    Style song_style;
    
public:
    string snapshot_date;
    string country;
    string spotify_id;
    Song(){};

    Song(string spotify_id,
    string name,
    string artist,
    int daily_rank,
    int daily_movement,
    int weekly_movement,
    string country,
    string snapshot_date,
    int popularity,
    string is_explicit,
    int duration_ms,
    string album_name,
    string album_release_date,
    
    float danceability,
    float energy,
    int key,
    float loudness,
    int mode,
    float speechiness,
    float acousticness,
    float instrumentalness,
    float liveness,
    float valence,
    float tempo,
    int time_signature)
    {
        song_style.setStyle(is_explicit,
        danceability,
        energy,
        key,
        loudness,
        mode,
        speechiness,
        acousticness,
        instrumentalness,
        liveness,
        valence,
        tempo,
        time_signature);

        this->spotify_id = spotify_id;
        this->name = name;
        this->artist = artist;
        this->daily_rank = daily_rank;
        this->daily_movement = daily_movement;
        this->weekly_movement = weekly_movement;
        this->country = country;
        this->snapshot_date = snapshot_date;
        this->popularity = popularity;
        this->duration_ms = duration_ms;
        this->album_name = album_name;
        this->album_release_date = album_release_date;

    }

    
};

void fileHandler(vector<Song> &songs, int numberOfSongs);