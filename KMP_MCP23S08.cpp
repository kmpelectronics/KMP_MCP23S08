/*!
 * @file KMP_MCP23S08.cpp
 *
 * This is a library for the the MCP23S08 SPI expander
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

#include "KMP_MCP23S08.h"

#define IODIR		0x00
#define IPOL		0x01
#define GPINTEN		0x02
#define DEFVAL		0x03
#define INTCON		0x04
#define IOCON		0x05
#define GPPU		0x06
#define INTF		0x07
#define INTCAP		0x08
#define GPIO		0x09
#define OLAT		0x0A

#define CLOCK		10000000 // Clock speed 10 Mhz
#define BIT_ORDER	MSBFIRST
#define DATA_MODE	SPI_MODE0

KMP_MCP23S08::KMP_MCP23S08(byte csPin) : _csPin(csPin) {}

KMP_MCP23S08::KMP_MCP23S08(byte csPin, byte deviceAddr) : _csPin(csPin) {
	// Attention! It is not fully checked.
	_deviceOpcode |= ((deviceAddr & 0x03) << 1);
}

void KMP_MCP23S08::begin() {
	pinMode(_csPin, OUTPUT);

	// Start SPI
	SPI.begin();
}

bool KMP_MCP23S08::read(byte pin) {
	if (pin >= MCP23S08_PIN_COUNT) {
		return false;
	}

	return (getInput() >> pin) & 1;
}

void KMP_MCP23S08::write(byte pin, bool state) {
	if (pin >= MCP23S08_PIN_COUNT) {
		return;
	}
	
	setOutput((getOutput() & ~(1 << pin)) | (state << pin));
}

void KMP_MCP23S08::pinMode(byte pin, byte mode) {
	if (pin >= MCP23S08_PIN_COUNT) {
		return;
	}
	
	switch (mode) {
		case INPUT:
			setMode(getMode() & ~(1 << pin));		// set pin direction to input
			setPullup(getPullup() & ~(1 << pin));	// disable pullup for pin
			break;
		case OUTPUT:
			setMode(getMode() | (1 << pin));		// set pin direction to output
			setPullup(getPullup() & ~(1 << pin));	// disable pullup for pin
			break;
		case INPUT_PULLUP:
			setMode(getMode() & ~(1 << pin));		// set pin direction to input
			setPullup(getPullup() | (1 << pin));	// enable pullup for pin
			break;
	}
}

void KMP_MCP23S08::setOutput(byte state) {
	writeRegister(OLAT, state);
}

void KMP_MCP23S08::setMode(byte mode) {
	writeRegister(IODIR, ~(mode));
}

void KMP_MCP23S08::setPullup(byte state) {
	writeRegister(GPPU, state);
}

byte KMP_MCP23S08::getInput() {
	return readRegister(GPIO);
}

byte KMP_MCP23S08::getOutput() {
	return readRegister(OLAT);
}

byte KMP_MCP23S08::getMode() {
	return ~(readRegister(IODIR));
}

byte KMP_MCP23S08::getPullup() {
	return readRegister(GPPU);
}

void KMP_MCP23S08::writeRegister(byte address, byte data) {
	beginTransaction();
	
	SPI.transfer(_deviceOpcode);
	SPI.transfer(address);
	SPI.transfer(data);
	
	endTransaction();
}

byte KMP_MCP23S08::readRegister(byte address) {
	beginTransaction();
	
	SPI.transfer(_deviceOpcode | 1);
	SPI.transfer(address);
	byte data = SPI.transfer(0);
	
	endTransaction();
	
	return data;
}

void KMP_MCP23S08::beginTransaction() {
	SPI.beginTransaction(SPISettings(CLOCK, BIT_ORDER, DATA_MODE));
	write(_csPin, LOW);
}

void KMP_MCP23S08::endTransaction() {
	write(_csPin, HIGH);
	SPI.endTransaction();
}

void KMP_MCP23S08::reset() {
	writeRegister(IODIR, 0xFF);
	for (byte i = IPOL; i <= OLAT; i++) {
		writeRegister(i, 0x00);
	}
}