/*!
 * @file KMP_MCP23S08.h
 * 
 * This is a library for the MCP23S08 SPI expander
 * 
 * This library for the Arduino IDE allows the simple usage of the MCP23S08 SPI based
 * I/O port expander by providing functions like digitalWrite, digitalRead and pinMode.
 * It is licensed under the MIT License, see LICENSE.txt.
 * 
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
	 * @brief Crate an instance of KMP_MCP23S08
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
	 * @param pin The pin number.
	 * @return true if it in 1 or false
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
	void setPinMode(byte pin, byte mode);
	
	/*!
	* @brief Set pins in output state
	* @param state State describe every pin state
	*/
	void setOutput(byte state);

	/*!
	 * @brief Set pins in mode
	 * @param mode Mode can be: INPUT, OUTPUT and INPUT_PULLUP
	 */
	void setMode(byte mode);

	/*!
	 * @brief Set pins in pullup mode state
	 * @param state State per pin
	 */
	void setPullup(byte state);
	
	/*!
	 * @brief Get all pins input state
	 * @return All pins input state
	 */
	byte getInput();

	/*!
	 * @brief Get all pins output state
	 * @return All pins output state
	 */
	byte getOutput();

	/*!
	 * @brief Get all pins mode
	 * @return All pins pins mode
	 */
	byte getMode();

	/*!
	 * @brief Get all pins pullup state
	 * @return All pins pullup state
	 */
	byte getPullup();
	
private:
	byte _csPin;
	byte _deviceOpcode = 0x40;
	
	void writeRegister(byte address, byte data);
	byte readRegister(byte address);

	void beginTransaction();
	void endTransaction();
};

#endif	// KMP_MCP23S08_H
