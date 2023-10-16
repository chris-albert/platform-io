#include <Arduino.h>
#include <Audio.h>
#include <protothreads.h>
#include <string>
#include "AudioSampleOneBeat.h"
#include "AudioSampleBeat.h"

#define ONE_BEAT_MIDI 43
#define BEAT_MIDI 44

AudioPlayMemory playMem;
AudioOutputI2S  i2s1;
AudioAmplifier	amp1;
AudioConnection patch1(playMem, amp1);
AudioConnection patch2(amp1, 0, i2s1, 0);
AudioConnection patch3(amp1, 0, i2s1, 1);

AudioControlSGTL5000     shield;

/*
  MIDI Status LED Protothread
 */
int statusState = LOW;
pt ptStatus;
int statusThread(struct pt* pt) {
  PT_BEGIN(pt);
  while(1) {
    if (statusState == HIGH) {
      digitalWrite(LED_BUILTIN, HIGH);
      PT_SLEEP(pt, 200);
      digitalWrite(LED_BUILTIN, LOW);
      statusState = 0;
    } else {
      PT_YIELD(pt);
    }
  }

  PT_END(pt);
}

void noteOn(byte channel, byte note, byte velocity) {
    statusState = HIGH;
    if(note == ONE_BEAT_MIDI) {
        playMem.play(AudioSampleOneBeat);
    } else if(note == BEAT_MIDI) {
        playMem.play(AudioSampleBeat);
    }
}

void setup() {

  #ifdef USB_SERIAL
    Serial.begin(9600);
    while (!Serial && millis() < 4000 );
  #endif
  
  pinMode(LED_BUILTIN, OUTPUT);

  AudioMemory(10);
  amp1.gain(1);

  shield.enable();
  shield.volume(1);

  noteOn(0, ONE_BEAT_MIDI, 127);

  #ifdef USB_MIDI
    usbMIDI.setHandleNoteOn(noteOn);
  #endif

  PT_INIT(&ptStatus);

}

void loop() {  

  PT_SCHEDULE(statusThread(&ptStatus));

  #ifdef USB_MIDI
    while (usbMIDI.read()) ;
  #endif

}