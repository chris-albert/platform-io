#include <Arduino.h>

//External projects located in ./lib
#include <Bounce.h>
#include <Flicker.h>

int count = 0;

int LED = LED_BUILTIN;

void setup() {

    Serial.println(" Hello RP2040 ");

    pinMode(LED, OUTPUT);
}

void loop() {
    String str = "Loop - ";
    str.concat(String(count));
    Serial.println(str);
    digitalWrite(LED, HIGH);   
    delay(1000);                       
    digitalWrite(LED, LOW);   
    delay(1000);  
    count++;
}