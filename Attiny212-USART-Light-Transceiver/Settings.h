/*
 * Settings.h
 *
 * Created: 2025-03-01 20:26:15
 *  Author: Saulius
 */ 


#ifndef SETTINGS_H_
#define SETTINGS_H_

/** @brief CPU frequency in Hz. */
#define F_CPU 20000000

/**
 * @brief Macro to calculate the baud rate setting for USART0.
 * 
 * @param BAUD_RATE The desired baud rate.
 * @return The value to be written to the USART0 baud register.
 */
#define USART0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (8 * (float)BAUD_RATE)) + 0.5) //dual speed 8, normal 16

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

void CLOCK_INHF_clock_init();

void CLOCK_XOSCHF_clock_init();

/**
 * @brief Initializes the General Purpose I/O (GPIO) pins for necessary tasks.
 * 
 * This function configures the necessary GPIO pins for communication, control, 
 * or other I/O purposes. The exact configuration will depend on the application.
 */
void GPIO_init();

/**
 * @brief Initializes USART0 for serial communication.
 * 
 * This function sets up USART0 for communication with a specified baud rate, 
 * data format, and enables the transmitter and receiver.
 */
void USART0_init();

/**
 * @brief Sends a single character via USART0.
 * 
 * This function waits for the USART transmit data register to be empty and 
 * then sends the specified character to the serial port.
 * 
 * @param c The character to send.
 */
void USART0_sendChar(char c);

/**
 * @brief Custom output function for printf-style printing via USART0.
 * 
 * This function allows `printf` to output characters via USART0 by using the 
 * USART0_sendChar function.
 * 
 * @param c The character to print.
 * @param stream The stream to print to (not used in this case).
 * @return int 0 to indicate the character was successfully sent.
 */
int USART0_printChar(char c, FILE *stream);

/**
 * @brief Sends a string via USART0.
 * 
 * This function sends a string by calling the `USART0_sendChar` function for 
 * each character in the string until the entire string has been transmitted.
 * 
 * @param str The string to send.
 */
void USART0_sendString(char *str);

/**
 * @brief Reads a single character from USART0.
 * 
 * This function waits for a character to be received via USART0 and returns 
 * the received character after clearing the receive interrupt flag.
 * 
 * @return char The received character.
 */
char USART0_readChar();

void Transceiver();

uint64_t verify_crc8_cdma2000(uint64_t data_with_crc);

uint8_t crc8_cdma2000(uint64_t data);

uint64_t hexStringToUint64(const char *hexStr);

void uint64ToHex(uint64_t value, char *out);


#endif /* SETTINGS_H_ */