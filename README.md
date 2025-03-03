## Firmware description

The purpose of this Error and Status Transceiver is to check the received data in hex format using CRC8/CDMA2000. If the data is correct, the program adds an additional bit that indicates the status of the transceiver's x variable (two end switches: min and max). It then calculates a new CRC value for the new data line and sends it for further processing. If the data reception line was corrupted or the data is not received for other reasons, the transceiver sends only the x end switches status and the calculated CRC for this status for further data processing. Considering that the microcontroller is an ATtiny212 and it has only 2KB of memory for storing the program code, the code had to be compressed as much as possible, eliminating convenient functions such as printf(), sprintf(), etc.During testing, the microcontroller operated with an external 20MHz clock generator. However, the firmware code includes the option to perform tests using the internal frequency generator.This firmware prototype will later be used for a fiber optic rotary joint and a solar tower controller.

## Wiring diagram

Attiny212 (SOIC-8 package)
* PA6 (2 Pin) used as USART TX
* PA7 (3 Pin) used as USART RX
