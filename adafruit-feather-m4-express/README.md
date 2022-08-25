
## Compiling 
```
pio run --environment usbmidi
```

## Upload
```
pio run --target upload --environment usbmidi 
```

## Cleaning
```
pio run -t clean
```
 - [m4 pinout](https://github.com/adafruit/Adafruit-Feather-M4-Express-PCB/blob/master/Adafruit%20Feather%20M4%20Express%20Pinout.pdf)
 - [platformio](https://docs.platformio.org/en/latest/boards/atmelsam/adafruit_feather_m4.html)
 - [MIDI over USB](https://tttapa.github.io/Control-Surface-doc/Doxygen/d8/d4a/md_pages_MIDI-over-USB.html)
 - [MIDIUSB](https://www.arduino.cc/reference/en/libraries/midiusb/)
 - [USB MIDI name](https://github.com/arduino-libraries/MIDIUSB/issues/37)