#include <Arduino.h>

#include <AppleMIDI.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

APPLEMIDI_CREATE_DEFAULTSESSION_INSTANCE(); 

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
 
}

void loop() {

}