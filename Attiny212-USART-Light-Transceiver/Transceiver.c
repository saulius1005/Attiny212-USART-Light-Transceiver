/*
 * Transceiver.c
 *
 * Created: 2025-03-01 21:48:43
 *  Author: Saulius
 */ 
 #include "Settings.h"
 #include "TransceiverVar.h"

 void executeCommand(char *command) {

	char temp[2] = {!(PORTA.IN & PIN1_bm) + '0', '\0'};
	USART0_sendChar('<');
	strcat(command, "|");
	strcat(command, temp);
	strcat(command, "|");
	temp[0] = !(PORTA.IN & PIN2_bm) + '0';
	strcat(command, temp);
	strcat(command, ">\r\n");

	USART0_sendString(command);
 }

 void Transceiver() {
	 uint8_t index = 0;
	 char command[32] = {0};
	 uint8_t start = 0;

    while (1) {
	    char c = USART0_readChar();

	    if (!Status.warning) {
		    if (start == 1) {
			    if (c == '>') {
				    start = 0;
				    executeCommand(command);
				    index = 0;
				    break;
				    } else {
				    command[index++] = c;
			    }
		    }
		    if (c == '<') {
			    start = 1;
		    }
		    if (Status.error == 1) {
			    Status.errorCounter = 0;
			    Status.error = 0;
		    }
		    } else {
		    Status.warning = 0;
		    if (Status.errorCounter < CountForError) {
			    Status.errorCounter += 1;
			    } else {
			    Status.error = 1;
		    }
		    break;
	    }
    }
 }