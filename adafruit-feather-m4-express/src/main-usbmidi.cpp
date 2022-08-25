#include <Arduino.h>
#include <USB-MIDI.h>

USBMIDI_CREATE_DEFAULT_INSTANCE();

String noteOnMessage = "";
void handleNoteOn(byte channel, byte pitch, byte velocity) {
    noteOnMessage = "Midi Note on - ";
    noteOnMessage.concat(pitch);
    Serial.println(noteOnMessage);
}

void setup() {
    MIDI.begin(1);
    MIDI.setHandleNoteOn(handleNoteOn);
}

void loop() {
    MIDI.read();
}