#include <Arduino.h>
#include <Audio.h>
#include <vector>
#include <string>
#include <algorithm>
#include <EEPROM.h>
#include "Path.h"
#include "Songs.h"

using namespace std;

void readDirectory(Path *path, File *dir, vector<Path*> *paths) {
  while(true) {
     File entry = dir->openNextFile();
     if (! entry) {
       //Serial.println("** no more files **");
       break;
     }
     if(entry.name()[0] != '.') {
        Path *newPath = path->append(entry.name());
        if (entry.isDirectory()) {
          readDirectory(newPath, &entry, paths);
        } else {
          paths->push_back(newPath);
        }
     }
     entry.close();
  }
}

vector<Path*> getSongPaths() {
    vector<Path*> paths;
    Path *root = new Path();
    File rootFile = SD.open("/");
    readDirectory(root, &rootFile, &paths);
    return paths;
}

Songs::Songs() {
    Serial.println("Initializing Songs");
    vector<Path*> songPaths;

    songPaths = getSongPaths();

    sortPaths(&songPaths);
    this->songs = toSimpleStringPath(&songPaths);
    this->printSongs();

    Serial.println("Done initializing songs");

    EEPROM.get(EEPROM_CURRENT_SONG, this->currentSong);
    //If we dont have anything in EEPROM, default to 0
    if(this->currentSong < 0) {
        this->currentSong = 0;
    }
    string currentSongIndexPrint = "Current song index: " + to_string(this->currentSong);
    Serial.println(currentSongIndexPrint.c_str());
}

void Songs::printSongs() {
    for(unsigned int i = 0; i < songs.size(); i++) {
        Serial.println(songs[i].c_str());
    }
}

void Songs::play(AudioPlaySdWav *playWav) {
    Serial.print("Playing file: ");
    string filename = getCurrentSong();
    Serial.println(filename.c_str());

    advanceCurrentSongIndex();
    // Start playing the file.  This sketch continues to
    // run while the file plays.
    playWav->play(filename.c_str());

    // A brief delay for the library read WAV info
    delay(25);

    // Simply wait for the file to finish playing.
    while (playWav->isPlaying()) { }
}

string Songs::getCurrentSong() {
    return songs[currentSong];
}

void Songs::advanceCurrentSongIndex() {
    if(currentSong < songs.size()) {
        currentSong++;
    } else {
        currentSong = 0;
    }
    EEPROM.put(EEPROM_CURRENT_SONG, currentSong);
}