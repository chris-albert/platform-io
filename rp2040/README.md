## Adafruit RP2040 Feather

There seems to be some [problem](https://community.platformio.org/t/arduino-rp4020-connect-upload-error/26655) with uploading the firmware to the rp2040 feather,
the work around is to copy the firmware manually to the device while in boot mode.

### Uploading firmware
You can still compile and montior the rp2040 with platformio, but you have to manually copy the firmware over. 

 - Plug device in while holding the `BOOTSEL` button, this will mount the rp2040 as `/Volumes/RPI-RP2`
 - copy `./.pio/build/rp2040/firmware.uf2` to `/Volumes/RPI-RP2`
    - `cp ./.pio/build/rp2040/firmware.uf2 /Volumes/RPI-RP2/firmware.uf2`