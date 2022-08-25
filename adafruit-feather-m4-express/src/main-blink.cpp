#include <Arduino.h>

void setup() {

    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    Serial.println("Blink");
    digitalWrite(LED_BUILTIN, HIGH);   
    delay(1000);                      
    digitalWrite(LED_BUILTIN, LOW);   
    delay(1000);    
}