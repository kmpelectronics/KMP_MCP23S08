# KMP MCP23S08 library
## Description
This is an Arduino library for a SPI expander MCP23S08. With this expander you can add 8 inputs or/and outputs to your board. More details about the MCP23S08 chip you can see [here](https://ww1.microchip.com/downloads/en/DeviceDoc/MCP23008-MCP23S08-Data-Sheet-20001919F.pdf). We use this expander in our products:
- [PRODINo ESP32](https://kmpelectronics.eu/products/prodino-esp32-v1/) series
- [PRODINo WIFI-ESP WROOM-02](https://kmpelectronics.eu/products/prodino-wifi-esp-wroom-02-v1/)

## Installation
Open **Arduino IDE**. From many selects Sketch -> Include Library -> Manage libraries. In **Library Manager** search for "KMP MCP23S08 library" and install the library.

## Examples
With this library we provide following examples:
- [InputOutput](https://github.com/kmpelectronics/KMP_MCP23S08/blob/main/examples/InputOutput/InputOutput.ino). The example reads input state and set the same state to the output in this case a LED. When you press the button the LED is On.
- [RunningLeds](https://github.com/kmpelectronics/KMP_MCP23S08/blob/main/examples/RunningLeds/RunningLeds.ino). We set all pins as outputs and simulate running lights. Move LED from left to right and opposite.

`KMP Electronics` invests time and resources providing this open source code, please support KMP Electronics and open-source hardware by purchasing products from [KMP Electronics](https://kmpelectronics.eu/)!


## License
This project is licensed under the MIT License, see [LICENSE](https://github.com/kmpelectronics/KMP_MCP23S08/blob/main/LICENSE) for further information.