/*!
 * @file InputOutput.ino
 *
 * In this example you can see how to use KMP_MCP23S08 library.
 * The example presets using of the MCP23S08 SPI I/O expander for reading buttons and set LEDs.
 * When you press the button, the coresponding LED will turn on. 
 * When you release the button, the coresponding LED will turn off.
 *
 * Connection digarm:
 * MCP23S08 pin | Arduino Uno board
 *            1 | D13 SCK
 *            2 | D11 MOSI 
 *            3 | D12 MISO
 *      4, 5, 9 | GND -
 *        6, 18 | 5V  + Power
 *            7 | D10 CS
 *    10 ... 13 | to button and other pin to GND
 *    14 ... 17 | 220 Ohm to the (+) of the LED and other pin to GND  -==--|>|--|
 *
 * KMP Electronics invests time and resources providing this open source code,
 * please support KMP Electronics and open-source hardware by purchasing
 * products from KMP Electronics!
 *
 * Created: 04 April 2021
 * Written by Plamen Kovandzhiev for KMP Electronics Ltd. contact@kmpelectronics.eu
 * It is licensed under the MIT License, see LICENSE.txt.
 */

#include <KMP_MCP23S08.h>

#define CS_PIN  10

KMP_MCP23S08 _expander(CS_PIN);

const int halfPins = 4;

void setup() {
  _expander.begin(); // Start expander

  // Set pins from 0 to 3 as input pullup pins 
  for (int pin = 0; pin < halfPins; pin++) {
    _expander.pinMode(pin, INPUT_PULLUP);
  }

  // Set pins from 4 to 7 as output pins
  for (int pin = halfPins; pin < MCP23S08_PIN_COUNT; pin++) {
    _expander.pinMode(pin, OUTPUT);
  }
}

void loop() {
  // Reading input pins from 0 to 3 and write result in output pins 4 to 7.
  for (int pin = 0; pin < halfPins; pin++) {
    bool state = !_expander.read(pin);         // Read input and invert
    _expander.write(pin + halfPins, state);   // Write state to output
  }
}
