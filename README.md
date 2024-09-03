# ubitxv6

uBitx v6.3.1 Arduino sketch

IMPORTANT: It will compile only if you place this in the Arduino's own sketch directory! This is because of the restricted places that the Arduino searches for it's include files (the headers).

- This is refactored to remove dependencies on any library except the standard Arduino libraries of SPI, I2C, EEPROM, etc.
- This works with ILI9341 display controller. The pins used by the TFT display are the same as that of the 16x2 LCD display of the previous versions.
- As the files are now split into .cpp files, the nano gui, morse reader, etc. can be reused in other projects as well

This is released under GPL v3 license.

## This sketch now includes AB1GO's fixes:

- Immediate change when pressing USB / LSB buttons
- Better automatic USB / LSB switching and corresponding display update
- Correct display of frequencies below 1 MHz
- Fix crashing bug when entering menu (due to uninitialized variable)
- Tuning knob improvement: only register detents, not half-way points
- Tuning knob improvement: Improve tuning speed and display update rate.  This was almost all there with the interrupt driven encoder code, but needed some final cleanup to get it to be really smooth.
- Tuning knob improvement: Rework knob "momentum" code: now the tuning jumps at fast rate if you have been turning the knob fast for a while.
- Fix some text alignment issues: buttons were being erased
- Fix some focus related issues: now selected VFO is indicated by white text, and white outline only means focus.  So now when you press tuning button you get immediate feedback.
- Put project into folder with same name as sketch so that Arduino IDE is happy

## Arduino IDE hints

Install CH340 serial port driver on your operating system if COM port /
serial port does not show up when you plug uBitx v6 into your computer.

Use "Arduino Duemilanove or Diecimila" instead of "Arduino Nano" as the
board type if you get errors when trying to upload.  Some low cost Arduino
Nano clones don't match real Nanos and this is a work-around.
