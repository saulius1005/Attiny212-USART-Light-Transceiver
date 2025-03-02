/*
 * Transceiver.c
 *
 * Created: 2025-03-01 21:48:43
 *  Author: Saulius
 */ 
 #include "Settings.h"
 #include "TransceiverVar.h"


 uint64_t hexStringToUint64(const char *hexStr) {
	 uint64_t result = 0;
	 while (*hexStr) {
		 char c = *hexStr;
		 uint8_t value = 0;

		 if (c >= '0' && c <= '9') {
			 value = c - '0';
			 } else if (c >= 'A' && c <= 'F') {
			 value = c - 'A' + 10;
			 } else if (c >= 'a' && c <= 'f') {
			 value = c - 'a' + 10;
			 } else {
			 break; // Neteisingas simbolis
		 }

		 result = (result << 4) | value; // Perkeliame 4 bitus ir pridedame naujà reikðmæ
		 hexStr++;
	 }
	 return result;
 }

 void uint64ToHex(uint64_t value, char *out) {
	 char *ptr = out;
	 int shift = 60; // Pradësime nuo didþiausio reikðmingo 4 bitø bloko

	 while (shift >= 0) {
		 uint8_t nibble = (value >> shift) & 0xF;
		 if (nibble || ptr != out) { // Praleidþia priekinius nulinius simbolius
			 *ptr++ = (nibble < 10) ? ('0' + nibble) : ('a' + nibble - 10);
		 }
		 shift -= 4;
	 }
	 if (ptr == out) { // Jei reikðmë buvo 0
		 *ptr++ = '0';
	 }
	 *ptr = '\0'; // Pridedame string'o pabaigos simbolá
 }

 void executeCommand(char *command) {
	
	uint64_t a = verify_crc8_cdma2000(hexStringToUint64(command));
	char buffer[20]; // 16 simboliø + null terminatorius
	uint8_t x = 0;

	if(!(PORTA.IN & PIN1_bm))
		x=4;
	else if(!(PORTA.IN & PIN2_bm))
	x=8;
	a = a+16;	 
	//uint64ToHex(a, buffer);
	//USART0_sendString(buffer);
	char test[4];
	utoa(crc8_cdma2000(0x23278C9FA1F6900),test,16);

	//strcat(buffer, test);
	USART0_sendChar('<');
	USART0_sendString(test); //send crc
	USART0_sendString(">\r\n");
	/*char temp[2] = {!(PORTA.IN & PIN1_bm) + '0', '\0'}; //PA1 bit value to string 
	USART0_sendChar('<');
	strcat(command, "|");
	strcat(command, temp);
	strcat(command, "|");
	temp[0] = !(PORTA.IN & PIN2_bm) + '0'; //PA2 bit value to string
	strcat(command, temp);
	strcat(command, ">\r\n");

	USART0_sendString(command);*/
 }

 void Transceiver() {
	 uint8_t index = 0;
	 char command[25] = {0};
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