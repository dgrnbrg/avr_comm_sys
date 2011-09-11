/*
	atmega48_ledramp.c
	
	Copyright 2008, 2009 Michel Pollet <buserror@gmail.com>

 	This file is part of simavr.

	simavr is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	simavr is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with simavr.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/wdt.h>

// for linker, emulator, and programmer's sake
#include "avr_mcu_section.h"
AVR_MCU(F_CPU, "atmega48");

#define SIGNAL_PORT PORTB
#include "pwm_generator.c"

volatile uint8_t now;

ISR(TIMER0_COMPA_vect) {
	OCR0A = signal_tick(TCNT0);
//	PORTC = (old & ~_BV(0)) | ~(old & _BV(0));
//	PORTC = OCR0A;
}

int main()
{	
	DDRB=0xff;	// all PORT B output
	TCCR0B = 3;
	TIMSK0 = 1<<OCIE0A | 1<<TOIE0;
	OCR0A = 0xff;

	DDRC = 0xff;

	struct period on = { .level = 1, .duration = 74 };
	struct period off = { .level = 0, .duration = 37 };
	on.next = &off;
	off.next = &on;
	signals[0] = &on;

	sei();
	volatile int i;
#if 1
	while(1) {
//		for (i = 0; i < 0x3f; i++);
//		PORTC = (PORTC & 0xf) | (TCNT0 & 0xf0);
//		now = TCNT0;
	}
#endif
}

