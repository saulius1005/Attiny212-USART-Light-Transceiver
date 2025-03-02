/*
 * Transceiver.c
 *
 * Created: 2025-03-01 21:48:43
 *  Author: Saulius
 */ 
 #include "Settings.h"
 #include "TransceiverVar.h"

size_t countLeadingZeros(char *command) {
	size_t count;
	for (count = 0; count < 16 && command[count] == '0'; count++);
	return count;
}


void executeCommand(char *command) {
	char newData[22] = {'<', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '>', '\r', '\n'};
	uint8_t x = (!(PORTA.IN & PIN1_bm)) | ((!(PORTA.IN & PIN2_bm)) << 1); //checking X min and max values (checking PA1 and PA2 values and shifting those to get 0,1,2,3 values instead of 0,2,4,6)
	if(!Status.error){
	uint64_t a = verify_crc8_cdma2000(hexStringToUint64(command));
		a = (a << 4) | x; //shift data and add X value
		uint64ToHex(a, newData +1 + countLeadingZeros(command)); //fill new data starting fom 1 symbol
		uint64ToHex(crc8_cdma2000(a), newData + 16); //add new data crc value starting fom 16 symbol
	}
	else{// if error active sending only x value with calculated crc it can be: 0xff if x=0x00 (returns first crc8/cmda2000 value), 0xe0 x=0x01, 0xd6 x=0x02, 0x4d x=0x03 (impossible value but still calculated for later easier fault detection (expl.: short circuit))
		uint64ToHex(x, newData + 15);
		uint64ToHex(crc8_cdma2000(x), newData + 16);
	}
	USART0_sendString(newData);
}



void Transceiver() {
	uint8_t index = 0;
	char command[16] = {0}; // 16 nuliai + null terminatorius
	uint8_t start = 0;

	while (1) {
		char c = USART0_readChar();

		if (Status.error) {
			executeCommand("0");
			Status.error = 0; // Atstatome klaidà po vykdymo
			Status.errorCounter = 0;
			break;
		}

		if (start) {
			if (c == '>') {
				start = 0;
				executeCommand(command);
				index = 0;
				break;
				} else if (index < 16) {
				command[index++] = c;
			}
		}

		if (c == '<') {
			start = 1;
			index = 0;
			Status.error = 0; // Atstatome klaidà
			Status.errorCounter = 0;
		}

		if (Status.warning) {
			Status.warning = 0;
			if (Status.errorCounter < CountForError) {
				Status.errorCounter++;
				} else {
				Status.error = 1;
			}
		}
	}
}

