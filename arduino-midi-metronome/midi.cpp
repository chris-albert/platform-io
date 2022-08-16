#include <Arduino.h>
#include <Adafruit_VS1053.h>

// See http://www.vlsi.fi/fileadmin/datasheets/vs1053.pdf Pg 31
#define VS1053_BANK_DEFAULT 0x00
#define VS1053_BANK_DRUMS1 0x78
#define VS1053_BANK_DRUMS2 0x7F
#define VS1053_BANK_MELODY 0x79

// See http://www.vlsi.fi/fileadmin/datasheets/vs1053.pdf Pg 32 for more!
#define VS1053_GM1_OCARINA 80
#define VS1053_METRO_CLICK 33
#define VS1053_METRO_BELL 34

#define MIDI_NOTE_ON  0x90
#define MIDI_NOTE_OFF 0x80
#define MIDI_CHAN_MSG 0xB0
#define MIDI_CHAN_BANK 0x00
#define MIDI_CHAN_VOLUME 0x07
#define MIDI_CHAN_PROGRAM 0xC0


#if defined(ESP8266) || defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
  #define VS1053_MIDI Serial
#else
  // anything else? use the hardware serial1 port
  #define VS1053_MIDI Serial1
#endif

void midiSetInstrument(uint8_t chan, uint8_t inst) {
  if (chan > 15) return;
  inst --; // page 32 has instruments starting with 1 not 0 :(
  if (inst > 127) return;
  
  VS1053_MIDI.write(MIDI_CHAN_PROGRAM | chan);  
  delay(10);
  VS1053_MIDI.write(inst);
  delay(10);
}


void midiSetChannelVolume(uint8_t chan, uint8_t vol) {
  if (chan > 15) return;
  if (vol > 127) return;
  
  VS1053_MIDI.write(MIDI_CHAN_MSG | chan);
  VS1053_MIDI.write(MIDI_CHAN_VOLUME);
  VS1053_MIDI.write(vol);
}

void midiSetChannelBank(uint8_t chan, uint8_t bank) {
  if (chan > 15) return;
  if (bank > 127) return;
  
  VS1053_MIDI.write(MIDI_CHAN_MSG | chan);
  VS1053_MIDI.write((uint8_t)MIDI_CHAN_BANK);
  VS1053_MIDI.write(bank);
}

void midiNoteOn(uint8_t chan, uint8_t n, uint8_t vel) {
  if (chan > 15) return;
  if (n > 127) return;
  if (vel > 127) return;
  
  VS1053_MIDI.write(MIDI_NOTE_ON | chan);
  VS1053_MIDI.write(n);
  VS1053_MIDI.write(vel);
}

void midiNoteOff(uint8_t chan, uint8_t n, uint8_t vel) {
  if (chan > 15) return;
  if (n > 127) return;
  if (vel > 127) return;
  
  VS1053_MIDI.write(MIDI_NOTE_OFF | chan);
  VS1053_MIDI.write(n);
  VS1053_MIDI.write(vel);
}

void click(uint8_t chan, u_int8_t n) {
    midiNoteOn(chan, n, 127); 
    delay(100);
    midiNoteOff(chan, n, 0);
    delay(250);
}

void midi_setup() {
  delay(1000);

  VS1053_MIDI.begin(31250); // MIDI uses a 'strange baud rate'
  
  midiSetChannelBank(0, VS1053_BANK_DRUMS1);
  midiSetChannelBank(1, VS1053_BANK_DRUMS1);

  midiSetChannelVolume(0, 127);
  midiSetChannelVolume(1, 127);

//   midiSetInstrument(0, VS1053_METRO_BELL);
//   midiSetInstrument(1, VS1053_METRO_CLICK);
}

void midi_loop() {  
  click(0, 33);
  for (uint8_t i=0; i<3; i++) {
    click(1, 34);
  }
}

