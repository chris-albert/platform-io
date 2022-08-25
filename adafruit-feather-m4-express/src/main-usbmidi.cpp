#include <Arduino.h>
#include <USB-MIDI.h>
#include <Adafruit_NeoPixel.h>

#define PIN       8
#define NUMPIXELS 1

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

USBMIDI_CREATE_DEFAULT_INSTANCE();

void noteOnStatus() {
    pixels.setPixelColor(0, pixels.Color(0, 150, 0));
    pixels.show();
    delay(100);
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.show();
}

String noteOnMessage = "";
void handleNoteOn(byte channel, byte pitch, byte velocity) {
    noteOnMessage = "Midi Note on - ";
    noteOnMessage.concat(pitch);
    Serial.println(noteOnMessage);
    noteOnStatus();
}

void setup() {
    MIDI.begin(MIDI_CHANNEL_OMNI);
    MIDI.setHandleNoteOn(handleNoteOn);

    pinMode(LED_BUILTIN, OUTPUT);
    pixels.begin();
}

void loop() {
    MIDI.read();
}