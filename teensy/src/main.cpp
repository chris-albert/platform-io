#include <Arduino.h>

//External projects located in ./lib
#include <Bounce.h>
#include <Flicker.h>

void setup() {

    Serial.begin(31250);

    Serial.println(" Hello Teensy 4.1 ");

    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {  
    digitalWrite(LED_BUILTIN, HIGH);   
    delay(3000);                       
    digitalWrite(LED_BUILTIN, LOW);   
    delay(3000);  

}
