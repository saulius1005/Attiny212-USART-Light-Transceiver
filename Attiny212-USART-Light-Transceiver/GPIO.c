/*
 * GPIO.c
 *
 * Created: 2025-03-01 20:26:40
 *  Author: Saulius
 */ 
 #include "Settings.h"

void GPIO_init(){

    PORTA.DIRSET = PIN6_bm; // Set PA6 as UART Transceiver TX output
    PORTA.PIN6CTRL = PORT_PULLUPEN_bm; //
    
    PORTA.DIRCLR = PIN1_bm | PIN2_bm | PIN7_bm; // Set PA1 as Xmax input, Set PA2 as Xmin input, Set PA7 as Light UART RX input
    PORTA.PIN1CTRL = PORT_PULLUPEN_bm; //
	PORTA.PIN2CTRL = PORT_PULLUPEN_bm; //
	PORTA.PIN7CTRL = PORT_PULLUPEN_bm; //
}