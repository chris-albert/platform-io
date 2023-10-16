#include <Arduino.h>
#include <Audio.h>
#include <vector>
#include <string>
#include <EEPROM.h>
#include "songs.h"

AudioPlaySdWav  playWav;
AudioOutputI2S  i2s1;
AudioAmplifier	amp1;
AudioConnection patch1(playWav, amp1);
AudioConnection patch2(amp1, 0, i2s1, 0);
AudioConnection patch3(amp1, 0, i2s1, 1);

AudioControlSGTL5000     shield;

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7   // Teensy 4 ignores this, uses pin 11
#define SDCARD_SCK_PIN   14  // Teensy 4 ignores this, uses pin 13

Songs * songs;

void setup() {
  #ifdef USB_SERIAL
    Serial.begin(9600);
    while (!Serial && millis() < 4000 );
  #endif

  AudioMemory(10);
  amp1.gain(.5);

  shield.enable();
  shield.volume(1);

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  songs = new Songs();
}

void loop() {
  songs->play(&playWav);
}
