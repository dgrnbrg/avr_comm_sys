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

#include "signal_generator.h"

ISR(TIMER_ISR) {
  uint8_t now = TIMER_CNT;
  uint8_t next_time;
  if (pwm_tick(now, &next_time)) {
    TIMER_OCR = next_time;
  }
}

ISR(TIMER_OVF) {
  pwm_overflow();
}

int main()
{	
	DDRB=0xff;	// all PORT B output
	wdt_disable();
	TCCR0B = 3;
	TIMSK0 = 1<<OCIE0A | 1<<TOIE0;
	pwm_set_duty_cycle(0,0);
	pwm_set_duty_cycle(1,64);
	pwm_set_duty_cycle(2,128);
	pwm_set_duty_cycle(3,192);
	pwm_set_duty_cycle(4,255);
	pwm_set_period(0xff);
	pwm_set_enable_mask(0x1f);

	DDRC = 0xff;

	sei();
	volatile int i;
	PORTC = 0;
#if 1
	while(1) {
		for (i = 0; i < 0x3f; i++);
		PORTC = (PORTC & 0xf) | (TCNT0);
	}
#endif
}

