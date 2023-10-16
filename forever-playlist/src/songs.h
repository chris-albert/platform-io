#include <vector>
#include <string>
#include <Audio.h>

using namespace std;

#ifndef SONGS_H
#define SONGS_H

class Songs {

    private:
        static const int EEPROM_CURRENT_SONG = 0;

        vector<string> songs;
        int currentSong;

        string getCurrentSong();
        void advanceCurrentSongIndex();

    public:
        Songs();
        void printSongs();
        void play(AudioPlaySdWav *playWav);
};


#endif