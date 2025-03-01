/*
 * Attiny212-USART-Light-Transceiver.c
 *
 * Created: 2025-03-01 20:23:07
 * Author : Saulius
 */ 

#include "Settings.h"


int main(void)
{
	CLOCK_XOSCHF_clock_init();
	//CLOCK_INHF_clock_init();
	GPIO_init();
	USART0_init();

    while (1) 
    {
		Transceiver();
		_delay_ms(100);
    }
}

