/*!
 * @file KMP_MCP23S08.h
 *
 * This is a library for the MCP23S08 SPI expander
 *
 * This library can work with every Arduino device and KMP Electronics use it together its devices:
 * ----> https://kmpelectronics.eu/products/prodino-wifi-esp-wroom-02-v1/
 * ----> https://kmpelectronics.eu/products/prodino-esp32-v1/
 *
 * This is an Arduino library which allows you use MCP23S08 SPI based
 * I/O port expander through methods: digitalWrite, digitalRead and pinMode.
 * 
 * KMP Electronics invests time and resources providing this open source code,
 * please support KMP Electronics and open-source hardware by purchasing
 * products from KMP Electronics!
 *
 * Written by Plamen Kovandzhiev for KMP Electronics Ltd. contact@kmpelectronics.eu
 * It is licensed under the MIT License, see LICENSE.txt.
 */
 
#ifndef KMP_MCP23S08_H
#define KMP_MCP23S08_H

#include "Arduino.h"
#include <SPI.h>

const byte MCP23S08_PIN_COUNT = 8;

class KMP_MCP23S08 {
public:
	/*!
	 * @brief Crate an instance of KMP_MCP23S08
	 * @param csPin Chip select pin
	 */	
	KMP_MCP23S08(byte csPin);

	/*!
	 * @brief Crate an instance of KMP_MCP23S08. Attention! It is not fully checked
	 * @param csPin Chip select pin
	 * @param deviceAddr Describe a device address
	 */	
	KMP_MCP23S08(byte csPin, byte deviceAddr);
	
	/*!
	 * @brief Start MCP23S08
	 */
	void begin();
	
	/*!
	 * @brief Read curent pin state. The pin can be from 0 to MCP23S08_PIN_COUNT -1
	 * @param pin The pin number
	 * @return true for 1 and false for 0
	 */
	bool read(byte pin);

	/*!
	 * @brief Write curent pin state
	 * @param pin The pin number. It can be from 0 to MCP23S08_PIN_COUNT -1
	 * @param state Set 1 if true or 0 if false
	 */
	void write(byte pin, bool state);
	
	/*!
	 * @brief Set a pin mode
	 * @param pin The pin number. It can be from 0 to MCP23S08_PIN_COUNT -1
	 * @param mode Pin mode can be: INPUT, OUTPUT and INPUT_PULLUP
	 */
	void pinMode(byte pin, byte mode);

	/*!
	 * @brief Configure every pin mode separately Input or Output
	 * @param mode Every bit of the byte represent one pin. 1 for Input and 0 for Output
	 */
	void setMode(byte mode);

	/*!
	 * @brief Get all pins mode Input or Output.
	 * @return Every bit of the byte represent one pin. 1 for Input and 0 for Output
	 */
	byte getMode();
	
	/*!
	* @brief Set pins in output state High or Low
	* @param state Every bit of the byte represent one pin. 1 for High and 0 for Low
	*/
	void setOutput(byte state);

	/*!
	 * @brief Get all pins output state High or Low. Every bit of the byte represent one pin.
	 * @return All pins output state. 1 for High and 0 for Low
	 */
	byte getOutput();
	
	/*!
	 * @brief Get all pins input state. Every bit of the byte represent one pin.
	 * @return All pins input state. 1 for High and 0 for Low
	 */
	byte getInput();

	/*!
	 * @brief Set pins in pullup mode state. Every bit of the byte represent one pin.
	 * @param state State per pin. 1 = Pull-up enabled and 0 = Pull-up disabled
	 */
	void setPullup(byte state);

	/*!
	 * @brief Get all pins pullup state
	 * @return Every bit of the byte represent one pin. 1 = Pull-up enabled and 0 = Pull-up disabled
	 */
	byte getPullup();
	
	/*!
	 * @brief Reset all registers
	 */
	void reset();
	
private:
	byte _csPin;
	byte _deviceOpcode = 0x40;
	
	void writeRegister(byte address, byte data);
	byte readRegister(byte address);

	void beginTransaction();
	void endTransaction();
};

#endif	// KMP_MCP23S08_H
