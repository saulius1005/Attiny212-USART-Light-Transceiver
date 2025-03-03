/**
 * @file GPIO.c
 * @brief GPIO initialization for ATTiny212.
 * 
 * This file contains functions for configuring the GPIO pins for specific functions such as UART communication, 
 * and input/output configuration for various pins.
 * 
 * @author Saulius
 * @date 2025-03-01
 */

#include "Settings.h"

/**
 * @brief Initializes the GPIO pins for UART communication and other input/output functionality.
 * 
 * This function configures the following pins:
 * - PA6: Set as UART Transceiver TX output with pull-up resistor.
 * - PA1: Set as Xmax input with pull-up resistor.
 * - PA2: Set as Xmin input with pull-up resistor.
 * - PA7: Set as Light UART RX input with pull-up resistor.
 */
void GPIO_init() {

    // Configure PA6 as UART Transceiver TX output
    PORTA.DIRSET = PIN6_bm;  ///< Set PA6 as an output for TX.
    PORTA.PIN6CTRL = PORT_PULLUPEN_bm;  ///< Enable pull-up resistor for PA6 (not strictly needed for TX, but it’s configured for consistency).
    
    // Configure PA1, PA2, and PA7 as inputs with pull-up resistors
    PORTA.DIRCLR = PIN1_bm | PIN2_bm | PIN7_bm; ///< Set PA1, PA2, and PA7 as input pins.
    
    // Enable pull-up resistors for PA1, PA2, and PA7
    PORTA.PIN1CTRL = PORT_PULLUPEN_bm;  ///< Enable pull-up resistor for PA1.
    PORTA.PIN2CTRL = PORT_PULLUPEN_bm;  ///< Enable pull-up resistor for PA2.
    PORTA.PIN7CTRL = PORT_PULLUPEN_bm;  ///< Enable pull-up resistor for PA7.
}
