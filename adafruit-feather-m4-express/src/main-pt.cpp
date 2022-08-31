#include <Arduino.h>
#include <USB-MIDI.h>
#include <Adafruit_NeoPixel.h>
#include <protothreads.h>

// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <SD.h>
#include <Adafruit_VS1053.h>

// These are the pins used
#define VS1053_RESET   -1     // VS1053 reset pin (not used!)

// Feather ESP8266
#if defined(ESP8266)
  #define VS1053_CS      16     // VS1053 chip select pin (output)
  #define VS1053_DCS     15     // VS1053 Data/command select pin (output)
  #define CARDCS          2     // Card chip select pin
  #define VS1053_DREQ     0     // VS1053 Data request, ideally an Interrupt pin

// Feather ESP32
#elif defined(ESP32) && !defined(ARDUINO_ADAFRUIT_FEATHER_ESP32S2)
  #define VS1053_CS      32     // VS1053 chip select pin (output)
  #define VS1053_DCS     33     // VS1053 Data/command select pin (output)
  #define CARDCS         14     // Card chip select pin
  #define VS1053_DREQ    15     // VS1053 Data request, ideally an Interrupt pin

// Feather Teensy3
#elif defined(TEENSYDUINO)
  #define VS1053_CS       3     // VS1053 chip select pin (output)
  #define VS1053_DCS     10     // VS1053 Data/command select pin (output)
  #define CARDCS          8     // Card chip select pin
  #define VS1053_DREQ     4     // VS1053 Data request, ideally an Interrupt pin

// WICED feather
#elif defined(ARDUINO_STM32_FEATHER)
  #define VS1053_CS       PC7     // VS1053 chip select pin (output)
  #define VS1053_DCS      PB4     // VS1053 Data/command select pin (output)
  #define CARDCS          PC5     // Card chip select pin
  #define VS1053_DREQ     PA15    // VS1053 Data request, ideally an Interrupt pin

#elif defined(ARDUINO_NRF52832_FEATHER )
  #define VS1053_CS       30     // VS1053 chip select pin (output)
  #define VS1053_DCS      11     // VS1053 Data/command select pin (output)
  #define CARDCS          27     // Card chip select pin
  #define VS1053_DREQ     31     // VS1053 Data request, ideally an Interrupt pin

// Feather M4, M0, 328, ESP32S2, nRF52840 or 32u4
#else
  #define VS1053_CS       6     // VS1053 chip select pin (output)
  #define VS1053_DCS     10     // VS1053 Data/command select pin (output)
  #define CARDCS          5     // Card chip select pin
  // DREQ should be an Int pin *if possible* (not possible on 32u4)
  #define VS1053_DREQ     9     // VS1053 Data request, ideally an Interrupt pin

#endif

Adafruit_VS1053_FilePlayer musicPlayer = 
  Adafruit_VS1053_FilePlayer(VS1053_RESET, VS1053_CS, VS1053_DCS, VS1053_DREQ, CARDCS);

#define PIN       8
#define NUMPIXELS 1

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

USBMIDI_CREATE_DEFAULT_INSTANCE();

#define ONE_MIDI 43

#define ONE_MIDI_FILE "/midi_43.wav"
#define NOT_ONE_MIDI_FILE "/midi_44.wav"

void handleNoteOn(byte channel, byte pitch, byte velocity) {

    if(pitch == ONE_MIDI) {
        // pixels.setPixelColor(0, pixels.Color(150, 0, 0));
        // pixels.show(); 
        musicPlayer.playFullFile(ONE_MIDI_FILE);
    } else {
        // pixels.setPixelColor(0, pixels.Color(0, 150, 0));
        // pixels.show();
        musicPlayer.playFullFile(NOT_ONE_MIDI_FILE);
    }
    musicPlayer.stopPlaying();

    // delay(50);
    // pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    // pixels.show();
}

// Stats ProtoThread
pt ptStatus;
boolean shouldFire;

int statusThread(struct pt* pt) {
  PT_BEGIN(pt);

  // Loop forever
  for(;;) {
    if(shouldFire) {
      pixels.setPixelColor(0, pixels.Color(150, 0, 0));
      pixels.show();
      PT_SLEEP(pt, 1000);
      pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      pixels.show();
    }
   
  }

  PT_END(pt);
}


void setup() {
    if (! musicPlayer.begin()) { // initialise the music player
        Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
        while (1);
    }

     Serial.println(F("VS1053 found"));
 
    if (!SD.begin(CARDCS)) {
        Serial.println(F("SD failed, or not present"));
        while (1);  // don't do anything more
    }
    Serial.println("SD OK!");

    musicPlayer.setVolume(0, 0);

    MIDI.begin(MIDI_CHANNEL_OMNI);
    MIDI.setHandleNoteOn(handleNoteOn);

    pixels.begin();
}

void loop() {
    MIDI.read();
}