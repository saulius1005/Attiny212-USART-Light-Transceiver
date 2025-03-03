/**
 * @file Settings.h
 * @brief Header file for configuration settings, USART communication, and utility function prototypes.
 * 
 * This file contains macro definitions, function prototypes, and includes required libraries 
 * for setting up the system configuration, USART communication, and other utility functions 
 * such as clock initialization, GPIO initialization, and CRC calculation.
 * 
 * @author Saulius
 * @date 2025-03-01
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

/** 
 * @brief CPU frequency in Hz.
 * 
 * Defines the CPU clock speed for the system. This is used for calculating 
 * various parameters like baud rates.
 */
#define F_CPU 20000000

/**
 * @brief Macro to calculate the baud rate setting for USART0.
 * 
 * This macro calculates the baud rate register value based on the desired 
 * baud rate and the system clock frequency. It is designed for dual-speed 
 * operation (8x speed) for better performance.
 * 
 * @param BAUD_RATE The desired baud rate.
 * @return The value to be written to the USART0 baud register.
 */
#define USART0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (8 * (float)BAUD_RATE)) + 0.5) ///< Baud rate calculation for dual speed

#include <avr/io.h>
#include <stdio.h>       /**< Include standard I/O library for functions like printf. */
#include <stdlib.h>
#include <string.h>      /**< Include string library for handling string functions like strlen. */
#include <util/delay.h>  /**< Include delay utilities for timing functions. */
#include <avr/cpufunc.h> /**< Include AVR-specific functions like ccp_write_io. */

#include "Transceiver.h"

////////////////////////////////////////////////////////////////////////////////
// Function Prototypes
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Initializes the internal high-frequency clock generator.
 * 
 * This function sets up the internal clock generator for the system to provide 
 * a stable high-frequency clock source.
 */
void CLOCK_INHF_clock_init();

/**
 * @brief Initializes the external high-frequency clock generator.
 * 
 * This function sets up the external high-frequency clock generator for better 
 * stability and accuracy than the internal clock source.
 */
void CLOCK_XOSCHF_clock_init(); 

/**
 * @brief Initializes the General Purpose I/O (GPIO) pins for necessary tasks.
 * 
 * Configures the necessary GPIO pins for communication, control, or other I/O purposes.
 * The exact configuration will depend on the application.
 */
void GPIO_init();

/**
 * @brief Initializes USART0 for serial communication.
 * 
 * Sets up USART0 for communication with a specified baud rate, data format, 
 * and enables the transmitter and receiver.
 */
void USART0_init();

/**
 * @brief Sends a single character via USART0.
 * 
 * Waits for the USART transmit data register to be empty and then sends 
 * the specified character to the serial port.
 * 
 * @param c The character to send.
 */
void USART0_sendChar(char c);

/**
 * @brief Custom output function for printf-style printing via USART0.
 * 
 * Allows `printf` to output characters via USART0 by using the `USART0_sendChar` function.
 * 
 * @param c The character to print.
 * @param stream The stream to print to (not used in this case).
 * @return int 0 to indicate the character was successfully sent.
 */
int USART0_printChar(char c, FILE *stream);

/**
 * @brief Sends a string via USART0.
 * 
 * Sends a string by calling the `USART0_sendChar` function for each character 
 * in the string until the entire string has been transmitted.
 * 
 * @param str The string to send.
 */
void USART0_sendString(char *str);

/**
 * @brief Reads a single character from USART0.
 * 
 * Waits for a character to be received via USART0 and returns the received 
 * character after clearing the receive interrupt flag.
 * 
 * @return char The received character.
 */
char USART0_readChar();

/**
 * @brief Transceiver function for handling communication.
 * 
 * This function handles the communication between the transceiver and other 
 * components, processing received commands and managing error conditions.
 */
void Transceiver();

/**
 * @brief Verifies the CRC8-CDMA2000 checksum of data.
 * 
 * Verifies the CRC of a given 64-bit data value and returns 0 if the CRC is incorrect, 
 * or the data if the CRC is correct.
 * 
 * @param data_with_crc The data including the CRC to verify.
 * @return uint64_t The data if CRC is correct, or 0 if the CRC is incorrect.
 */
uint64_t verify_crc8_cdma2000(uint64_t data_with_crc); 

/**
 * @brief Calculates the CRC8-CDMA2000 checksum for data.
 * 
 * Calculates and returns the CRC value for the given 64-bit data.
 * 
 * @param data The data to calculate the CRC for.
 * @return uint8_t The CRC value of the data.
 */
uint8_t crc8_cdma2000(uint64_t data); 

/**
 * @brief Converts a hexadecimal string to a uint64_t variable.
 * 
 * Converts a string of hexadecimal digits into an unsigned 64-bit integer.
 * 
 * @param hexStr The hexadecimal string to convert.
 * @return uint64_t The converted 64-bit integer.
 */
uint64_t hexStringToUint64(const char *hexStr); 

/**
 * @brief Converts a uint64_t value to a hexadecimal string.
 * 
 * Converts a 64-bit integer to a string representation in hexadecimal format.
 * 
 * @param value The value to convert.
 * @param out The output buffer where the hexadecimal string will be stored.
 */
void uint64ToHex(uint64_t value, char *out); 

#endif /* SETTINGS_H_ */
