Here is the SPI pinout table mapping the NodeMCU (Master) to the ESP32-S3 (Slave):

| SPI Signal | NodeMCU (ESP8266 Master) | ESP32-S3 (Slave) | Description |
| --- | --- | --- | --- |
| **MOSI** | D7 (GPIO 13) | GPIO 11 | Master Out, Slave In |
| **MISO** | D6 (GPIO 12) | GPIO 13 | Master In, Slave Out |
| **SCK** | D5 (GPIO 14) | GPIO 12 | Serial Clock |
| **CS / SS** | D8 (GPIO 15) | GPIO 10 | Chip Select |
| **GND** | GND | GND | Shared Ground (**Required**) |

*(Note: Ensure you also connect 3.3V power appropriately, but always maintain a common GND between both boards).*