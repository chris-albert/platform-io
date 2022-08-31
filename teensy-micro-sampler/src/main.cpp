#include <Arduino.h>
#include <Audio.h>
#include <protothreads.h>
#include <string>

const int chipSelect = BUILTIN_SDCARD;

AudioPlayMemory    sound;
AudioPlaySdWav     playWav1;

AudioOutputMQS  audioOutput;
AudioAmplifier	amp1;

AudioConnection patch1(playWav1, amp1);
AudioConnection patch2(amp1, 0, audioOutput, 0);

void playFile(const char *filename) {
  playWav1.play(filename);
}

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

char filename[] = "/midi_XX.wav";
char num[2];

void noteOn(byte channel, byte note, byte velocity) {
    if(note < 100) {
      statusState = HIGH;
      ultoa((long) note, num, 10);
      filename[6] = num[0];
      filename[7] = num[1];
      playFile(filename);
    }
}

void setup() {

  Serial.begin(9600);
  while (!Serial && millis() < 4000 );
  
  pinMode(LED_BUILTIN, OUTPUT);

  AudioMemory(10);
  amp1.gain (0.5);

  Serial.println("Initializing SD card...");
  
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    while(1);
  }
  Serial.println("SD Card initialized.");

  usbMIDI.setHandleNoteOn(noteOn);

  PT_INIT(&ptStatus);
}

void loop() {  

  PT_SCHEDULE(statusThread(&ptStatus));

  while (usbMIDI.read()) ;

}