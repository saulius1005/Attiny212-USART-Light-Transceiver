/*
 * @file Transceiver.c
 * @brief Implementation of transceiver communication logic.
 *
 * This file contains functions to manage communication between the microcontroller and 
 * an external device using USART, including CRC validation, error detection, and 
 * command execution. The transceiver performs operations like reading data, executing 
 * commands, and sending back the response. It also handles error states and warnings.
 *
 * @author Saulius
 * @date 2025-03-01
 */

#include "Settings.h"
#include "TransceiverVar.h"

/**
 * @brief Count the leading zeros in a command string.
 *
 * This function counts how many leading zeros are present in a given command string
 * up to a maximum of 16 characters.
 * 
 * @param command The command string to process.
 * @return The number of leading zeros.
 */
size_t countLeadingZeros(char *command) {
    size_t count;
    for (count = 0; count < 16 && command[count] == '0'; count++);
    return count;
}

/**
 * @brief Execute a command received by the transceiver.
 *
 * This function processes the command, validates the CRC, and modifies the data 
 * based on the error status. It then sends the modified data back through USART.
 * 
 * If an error is detected in the system, the function only sends a specific error 
 * value based on the state of the microcontroller's input pins (PA1 and PA2).
 *
 * @param command The command string to execute.
 */
void executeCommand(char *command) {
    char newData[22] = {'<', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '>', '\r', '\n'};
    uint8_t x = (!(PORTA.IN & PIN1_bm)) | ((!(PORTA.IN & PIN2_bm)) << 1); // Checking X min and max values (PA1 and PA2 values)
    
    if (!Status.error) {
        uint64_t a = verify_crc8_cdma2000(hexStringToUint64(command));
        a = (a << 4) | x; // Shift data and add X value
        uint64ToHex(a, newData + 1 + countLeadingZeros(command)); // Fill new data starting from 1 symbol
        uint64ToHex(crc8_cdma2000(a), newData + 16); // Add new data CRC value starting from 16 symbol
    } else { // If error active, sending only X value with calculated CRC
        uint64ToHex(x, newData + 15);
        uint64ToHex(crc8_cdma2000(x), newData + 16);
    }
    
    USART0_sendString(newData); // Send the data via USART
}

/**
 * @brief Main transceiver function.
 *
 * This function continuously reads incoming data via USART, processes the data, 
 * and executes the appropriate command. If an error occurs or a warning is set, 
 * it handles the corresponding state. The function handles both normal command 
 * processing and error recovery.
 */
void Transceiver() {
    uint8_t index = 0;
    char command[16] = {0}; // Empty command array
    uint8_t start = 0;

    while (1) {
        char c = USART0_readChar(); // Reading a character from USART

        if (Status.error) { // If an error is active
            executeCommand("0"); // Execute command 0 for error handling
            Status.error = 0; // Reset error value
            Status.errorCounter = 0;
            break;
        }

        if (start) {
            if (c == '>') { // If received data end symbol
                start = 0;
                executeCommand(command); // Execute the received command
                index = 0;
                break;
            } else if (index < 16) {
                command[index++] = c; // Store received character in command array
            }
        }

        if (c == '<') { // If received data start symbol
            start = 1;
            index = 0;
            Status.error = 0; // Reset error state
            Status.errorCounter = 0; // Reset error counter
        }

        if (Status.warning) {
            Status.warning = 0;
            if (Status.errorCounter < CountForError) {
                Status.errorCounter++;
            } else {
                Status.error = 1; // Set error flag if too many warnings
            }
        }
    }
}
