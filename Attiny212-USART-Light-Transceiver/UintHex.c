/**
 * @file UintHex.c
 * @brief Functions for converting between hexadecimal strings and 64-bit unsigned integers.
 * 
 * This file contains two functions:
 * - `hexStringToUint64`: Converts a hexadecimal string into a 64-bit unsigned integer.
 * - `uint64ToHex`: Converts a 64-bit unsigned integer to its hexadecimal string representation.
 * 
 * Both functions support hexadecimal digits from '0' to '9' and 'A' to 'F' (or 'a' to 'f').
 * The `uint64ToHex` function omits leading zeros unless the value is 0.
 * 
 * @author Saulius
 * @date 2025-03-02
 */

#include "Settings.h"

/**
 * @brief Converts a hexadecimal string to a 64-bit unsigned integer.
 * 
 * This function takes a string representing a hexadecimal number and converts it to
 * a uint64_t value. The input string can contain both uppercase and lowercase letters
 * ('0'-'9', 'A'-'F', 'a'-'f'). The function stops converting at the first invalid character.
 * 
 * @param hexStr The hexadecimal string to convert.
 * @return The resulting uint64_t value. If the string contains invalid characters, the conversion stops.
 */
uint64_t hexStringToUint64(const char *hexStr) {
    uint64_t result = 0; // Initialize result to 0
    while (*hexStr) {
        char c = *hexStr;
        uint8_t value = 0;

        // Check if character is a valid hexadecimal digit
        if (c >= '0' && c <= '9') {
            value = c - '0'; // Convert '0'-'9' to 0-9
        } else if (c >= 'A' && c <= 'F') {
            value = c - 'A' + 10; // Convert 'A'-'F' to 10-15
        } else if (c >= 'a' && c <= 'f') {
            value = c - 'a' + 10; // Convert 'a'-'f' to 10-15
        } else {
            break; // Invalid character, stop conversion
        }

        result = (result << 4) | value; // Shift 4 bits and add new value
        hexStr++; // Move to the next character
    }
    return result; // Return the converted value
}

/**
 * @brief Converts a 64-bit unsigned integer to a hexadecimal string.
 * 
 * This function converts a uint64_t value to a string representing its hexadecimal
 * representation. The result is written to the provided output buffer, with each nibble
 * (4 bits) converted to a single hexadecimal character. Leading zeros are omitted, unless
 * the value is 0, in which case "0" is written to the buffer.
 * 
 * @param value The uint64_t value to convert.
 * @param out The output buffer where the hexadecimal string will be written.
 */
void uint64ToHex(uint64_t value, char *out) {
    uint8_t started = 0; // Flag to indicate if we have started writing digits
    // Loop through each nibble (4 bits) of the uint64_t value
    for (int8_t i = 60; i >= 0; i -= 4) {
        uint8_t nibble = (value >> i) & 0xF; // Extract the nibble
        if (nibble || started) { // Write the nibble if it's non-zero or we've already started
            *out++ = (nibble < 10) ? ('0' + nibble) : ('a' + nibble - 10); // Convert nibble to hex character
            started = 1; // Set started flag once we begin writing digits
        }
    }
    if (!started) *out++ = '0'; // If the value was 0, output a single '0'
}
