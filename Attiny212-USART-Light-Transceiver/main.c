/**
 * @file Attiny212-USART-Light-Transceiver.c
 * @brief Main program for initializing and managing USART communication and transceiver functionality.
 * 
 * This file contains the main function for initializing system components including clocks, GPIO pins, 
 * and USART for communication. It also starts the transceiver process, which manages the communication 
 * logic between the system and other components.
 * 
 * @author Saulius
 * @date 2025-03-01
 */

#include "Settings.h"

/**
 * @brief Main function for the ATTiny212 USART light transceiver.
 * 
 * This function initializes the clock system, GPIO pins, and USART communication. It then enters an 
 * infinite loop where it repeatedly calls the `Transceiver` function to handle communication tasks. 
 * The clock system is initialized to use an external high-frequency clock generator, but the internal 
 * clock generator can be enabled as an alternative.
 * 
 * @return int This function does not return as it enters an infinite loop.
 */
int main(void)
{
    // Initialize the external high-frequency clock generator for more stable operation.
    CLOCK_XOSCHF_clock_init(); 
    
    // Uncomment the following line if the internal high-frequency clock generator is preferred.
    //CLOCK_INHF_clock_init(); 

    // Initialize GPIO pins for communication and control tasks.
    GPIO_init();

    // Initialize USART0 for serial communication.
    USART0_init();

    // Main loop: continuously handle communication via the transceiver.
    while (1) 
    {
        // Call the transceiver function to manage communication.
        Transceiver();
    }
}
