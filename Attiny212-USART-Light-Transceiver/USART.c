/**
 * @file USART.c
 * @brief USART configuration and communication functions for ATTiny1614.
 * 
 * This file contains functions for initializing USART0, sending data (both single characters and strings), 
 * and supporting formatted output via USART0. The baud rate is set to 0.25 Mbps, and double-speed operation is used.
 * 
 * @author Saulius
 * @date 2025-01-19
 */

#include "Settings.h"

/**
 * @brief Initializes USART0 with a baud rate of 250000.
 * 
 * Configures USART0 for asynchronous communication with the following settings:
 * - Baud rate of 0.25 Mbps.
 * - Double-speed operation for higher communication speed.
 * - Transmitter enabled, reception mode set for double-speed.
 * - Asynchronous communication mode with 8 data bits, no parity, and 1 stop bit.
 */
void USART0_init() {
    USART0.BAUD = (uint16_t)USART0_BAUD_RATE(500000); ///< Set baud rate to 0.25 Mbps.
    USART0.CTRLB = USART_TXEN_bm | USART_RXEN_bm | USART_RXMODE_CLK2X_gc; ///< Enable transmitter, double-speed mode.
    USART0.CTRLC = USART_CMODE_ASYNCHRONOUS_gc | ///< Configure for asynchronous mode.
                  USART_CHSIZE_8BIT_gc |      ///< Set data frame to 8 bits.
                  USART_PMODE_DISABLED_gc |  ///< Disable parity.
                  USART_SBMODE_1BIT_gc;      ///< Set 1 stop bit.
}

/**
 * @brief Sends a single character via USART0.
 * 
 * This function waits for the USART0 data register to be empty and then transmits the specified character.
 * 
 * @param c The character to be transmitted.
 */
void USART0_sendChar(char c) {
    while (!(USART0.STATUS & USART_DREIF_bm)); ///< Wait for data register to be empty.
    USART0.TXDATAL = c; ///< Transmit the character.
}

/**
 * @brief Sends a string via USART0.
 * 
 * This function sends a string of characters one by one using the `USART0_sendChar` function.
 * 
 * @param str The string to be transmitted.
 */
void USART0_sendString(char *str) {
    for (size_t i = 0; i < strlen(str); i++) {
        USART0_sendChar(str[i]); ///< Send each character of the string.
    }
}

char USART0_readChar() {
	USART0.STATUS = USART_RXCIF_bm; // Clear buffer before reading
	uint32_t timeout_counter = TIMEOUT_COUNTER; // Set a timeout counter
	while (!(USART0.STATUS & USART_RXCIF_bm)) { // Wait for data to be received
		if (--timeout_counter == 0) { // Timeout condition
			Status.warning = 3; // Set warning if timeout occurs
			break;
		}
	}
	return USART0.RXDATAL; // Return received character
}

