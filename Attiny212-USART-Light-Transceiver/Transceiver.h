/*
 * Transceiver.h
 *
 * Created: 2025-03-01 21:55:40
 *  Author: Saulius
 */ 


#ifndef TRANSCEIVER_H_
#define TRANSCEIVER_H_

#define CountForError 10
#define TIMEOUT_COUNTER 500000 ///< Timeout counter value for operations

typedef struct {
	uint8_t error;     /**< Error flag (1 if an error occurs, 0 otherwise) */
	uint8_t errorCounter; /**< Counter for error occurrences */
	uint8_t warning;   /**< Warning flag (1 if a warning occurs) */
} Communication;

extern Communication Status;

#endif /* TRANSCEIVER_H_ */