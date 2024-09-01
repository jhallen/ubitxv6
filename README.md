# ubitxv6
uBitx v6.3.1 Arduino sketch
IMPORTANT: It will compile only if you place this in the Arduino's own sketch directory! This is because of the restricted places that the Arduino searches for it's include files (the headers).

- This is refactored to remove dependencies on any library except the standard Arduino libraries of SPI, I2C, EEPROM, etc.
- This works with ILI9341 display controller. The pins used by the TFT display are the same as that of the 16x2 LCD display of the previous versions.
- As the files are now split into .cpp files, the nano gui, morse reader, etc. can be reused in other projects as well

This is released under GPL v3 license.

## Arduino IDE hints

The "Arduino Nano" included with the uBitx v6 is a low cost clone, so:

Install CH340 serial port driver.  Select the serial port that shows up when
you plug the board in, but select "Arduino Duemilanove or Diecimila" as the
Ardiuno type, not "Arduino Nano".
