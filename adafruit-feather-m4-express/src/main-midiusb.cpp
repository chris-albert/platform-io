#include <Arduino.h>
#include "MIDIUSB.h"

int LED = LED_BUILTIN;
String msg = "";

void setup() {

    Serial.begin(31250);
    // Control_Surface.begin();
}

void loop() {
  midiEventPacket_t rx;
  do {
    rx = MidiUSB.read();
    if (rx.header != 0) {
      Serial.print("Received: ");
      Serial.print(rx.header, HEX);
      Serial.print("-");
      Serial.print(rx.byte1, HEX);
      Serial.print("-");
      Serial.print(rx.byte2, HEX);
      Serial.print("-");
      Serial.println(rx.byte3, HEX);
    }
  } while (rx.header != 0);
}