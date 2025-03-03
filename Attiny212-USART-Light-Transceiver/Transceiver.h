/*
 * @file Transceiver.h
 * @brief Header file for transceiver communication status and constants.
 *
 * This header file defines the communication-related constants and the structure
 * used to track the status of the transceiver. It includes the `Communication` 
 * structure that stores the error flag, error counter, and warning flag. Additionally,
 * it defines constants for error thresholds and timeout values.
 *
 * @author Saulius
 * @date 2025-03-01
 */

#ifndef TRANSCEIVER_H_
#define TRANSCEIVER_H_

/**
 * @brief Maximum count for consecutive errors before marking the system as faulty.
 */
#define CountForError 10

/**
 * @brief Timeout counter value for operations.
 * 
 * This constant defines the timeout threshold for operations. If the counter 
 * exceeds this value, it indicates a timeout has occurred.
 */
#define TIMEOUT_COUNTER 40000 ///< Timeout counter value for operations

/**
 * @brief Structure to hold communication status.
 *
 * This structure is used to track the state of communication for the transceiver. 
 * It includes flags and counters to handle errors and warnings.
 */
typedef struct {
    uint8_t error;         /**< Error flag (1 if an error occurs, 0 otherwise) */
    uint8_t errorCounter;  /**< Counter for error occurrences */
    uint8_t warning;       /**< Warning flag (1 if a warning occurs) */
} Communication;

/**
 * @brief Global variable for tracking communication status.
 *
 * This external variable is used to store the current communication status, 
 * including error and warning states.
 */
extern Communication Status;

#endif /* TRANSCEIVER_H_ */
