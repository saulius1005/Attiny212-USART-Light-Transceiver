/*
 * UintHex.c
 *
 * Created: 2025-03-02 15:42:51
 *  Author: Saulius
 */ 
  #include "Settings.h"

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

/*uint64_t hexStringToUint64(const char *hexStr) {
	uint64_t result = 0;
	char c;

	while ((c = *hexStr++)) {
		uint8_t value;

		if (c >= '0' && c <= '9') {
			value = c - '0';
			} else if (c >= 'A' && c <= 'F') {
			value = c - ('A' - 10);
			} else if (c >= 'a' && c <= 'f') {
			value = c - ('a' - 10);
			} else {
			break; // Neteisingas simbolis
		}

		result = (result << 4) | value;
	}
	return result;
}*/


  /* void uint64ToHex(uint64_t value, char *out) {
	   uint8_t started = 0; // Þymi, ar pradëti raðyti ne nulius

	   for (int8_t i = (sizeof(value) * 8) - 4; i >= 0; i -= 4) {
		   uint8_t nibble = (value >> i) & 0xF;
		   if (nibble || started) {
			   *out++ = (nibble < 10) ? ('0' + nibble) : ('a' + nibble - 10);
			   started = 1;
		   }
	   }   
	   if (!started) { // Jei reikðmë buvo 0
		   *out++ = '0';
	   }
   }*/

void uint64ToHex(uint64_t value, char *out) {
	uint8_t started = 0;
	for (int8_t i = 60; i >= 0; i -= 4) {
		uint8_t nibble = (value >> i) & 0xF;
		if (nibble || started) {
			*out++ = (nibble < 10) ? ('0' + nibble) : ('a' + nibble - 10);
			started = 1;
		}
	}
	if (!started) *out++ = '0'; // Jei reikðmë buvo 0
}