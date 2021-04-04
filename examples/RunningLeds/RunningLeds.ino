/*!
 * @file RunningLeds.ino
 *
 * In this example you can see how to use KMP_MCP23S08 library.
 * The example presets using of the MCP23S08 SPI I/O expander for control LEDs.
 * This is a simulation of the running lights.
 *
 * Connection digarm:
 * MCP23S08 pin | Arduino Uno board
 *            1 | D13 SCK
 *            2 | D11 MOSI 
 *            3 | D12 MISO
 *      4, 5, 9 | GND -
 *        6, 18 | 5V  + Power
 *            7 | D10 CS
 *    10 ... 17 | 220 Ohm to the (+) of the LED and other pin to GND -==--|>|--|
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

void setup() {
  _expander.begin(); // Start expander

  // Set pins from 0 to 7 as output pins 
  for (int pin = 0; pin < MCP23S08_PIN_COUNT; pin++) {
    _expander.pinMode(pin, OUTPUT);
  }
}

void loop() {
  // Runing LEDs from first to last
  for (int pin = 0; pin < MCP23S08_PIN_COUNT; pin++) {
    _expander.write(pin, HIGH);     // Turn LED on
    delay(100);                     // Wait 100ms
    _expander.write(pin, LOW);      // Turn LED off
  }

  // Runing LEDs from last to first
  for (int pin = MCP23S08_PIN_COUNT; pin >= 0; pin--) {
    _expander.write(pin, HIGH);     // Turn LED on
    delay(100);                     // Wait 100ms
    _expander.write(pin, LOW);      // Turn LED off
  }
}
