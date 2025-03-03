/*
 * @file TransceiverVar.h
 * @brief Header file for transceiver variable definitions.
 *
 * This header file defines the global variables used for managing the communication 
 * status of the transceiver. It includes a `Status` structure that tracks the error 
 * state, error counter, and warning flag.
 * 
 * @author Saulius
 * @date 2025-03-01
 */

#ifndef TRANSCEIVERVAR_H_
#define TRANSCEIVERVAR_H_

/**
 * @brief Communication status structure.
 * 
 * This structure holds flags and counters used to track the status of the 
 * communication system. The structure includes the following fields:
 * 
 * - `.error`: A flag indicating if an error has occurred.
 * - `.errorCounter`: A counter that increments when warnings occur.
 * - `.warning`: A flag indicating if there is a warning.
 */
Communication Status = {
    .error = 0,           ///< Error flag, initialized to 0 (no error).
    .errorCounter = 0,    ///< Error counter, initialized to 0.
    .warning = 0          ///< Warning flag, initialized to 0 (no warning).
};

#endif /* TRANSCEIVERVAR_H_ */
