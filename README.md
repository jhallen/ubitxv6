# ubitxv6

uBitx v6.3.1 Arduino sketch

IMPORTANT: It will compile only if you place this in the Arduino's own sketch directory! This is because of the restricted places that the Arduino searches for it's include files (the headers).

- This is refactored to remove dependencies on any library except the standard Arduino libraries of SPI, I2C, EEPROM, etc.
- This works with ILI9341 display controller. The pins used by the TFT display are the same as that of the 16x2 LCD display of the previous versions.
- As the files are now split into .cpp files, the nano gui, morse reader, etc. can be reused in other projects as well

This is released under GPL v3 license.

## AB1GO's (Joe Allen's) version

This version adds no new features, but fixes many UI related things
including:

- Immediate change when pressing USB / LSB buttons
- Fix crashing bug when entering menu (due to uninitialized variable)
- Tuning knob improvement: only register detents, not half-way points
- Tuning knob improvement: Improve tuning speed and display update rate.  This was almost all there with the interrupt driven encoder code, but needed some final cleanup to get it to be really smooth.
- Tuning knob improvement: Rework knob "momentum" code: now the tuning jumps at fast rate if you have been turning the knob fast for a while.
- Fix some text alignment issues: buttons were being erased
- Fix some focus related issues: now selected VFO is indicated by white text, and white outline only means focus.  So now when you press tuning button you get immediate feedback.

## Arduino IDE hints

The "Arduino Nano" included with the uBitx v6 is a low cost clone, so:

Install CH340 serial port driver.  Select the serial port that shows up when
you plug the board in, but select "Arduino Duemilanove or Diecimila" as the
Ardiuno type, not "Arduino Nano".
