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

#define F_CPU 1000000UL  // 8 MHz
#include <util/delay.h>

#define SIGNAL_PORT PORTB
#include "pwm_generator.c"

volatile uint8_t now;

ISR(TIM0_COMPA_vect) {
	OCR0A = signal_tick(OCR0A);
//	OCR0A = signal_tick(TCNT0);
//	PORTC = (old & ~_BV(0)) | ~(old & _BV(0));
//	PORTC = OCR0A;
}

static struct period *
alloc_period(uint8_t level, uint8_t duration, struct period * next)
{
	struct period * p = malloc(sizeof(*p));
	p->level = level;
	p->next_duration = duration;
	p->next = next;
	return p;
}

static struct period *
alloc_period_loop(uint8_t level, uint8_t duration, struct period *** pnext)
{
	struct period * p = malloc(sizeof(*p));
	p->level = level;
	p->next_duration = duration;
	*pnext = &p->next;
	return p;
}

int main()
{	
	DDRB=0xff;	// all PORT B output
	TCCR0B = 3;
	TIMSK0 = 1<<OCIE0A;
	OCR0A = 0xff;

	struct period ** pp;
	signals[0] = alloc_period(1, 10, alloc_period_loop(0, 200, &pp));
	*pp = signals[0];
#if 0
	static struct period on = { .level = 1, .next_duration = 10, .credit = 0 };
	static struct period off = { .level = 0, .next_duration = 200, .credit = 0 };
	on.next = &off;
	off.next = &on;
	signals[0] = &on;
#endif

#if 0
	static struct period on2 = { .level = 1, .next_duration = 20, .credit = 0 };
	static struct period off2 = { .level = 0, .next_duration = 200, .credit = 0 };
	on2.next = &off2;
	off2.next = &on2;
	signals[1] = &on2;
#endif
	signal_tick(0);

	sei();
	volatile uint32_t i;
	uint8_t split = 30;
	int8_t dir = 3;
	while(1) {
		for (i = 0; i < 10000; i++);
		if (split > 220 || split < 20) dir = -dir;
		split += dir;
#if 0
		on2.next_duration = 0xff-split;
		off2.next_duration = split;
#endif
		on.next_duration = split;
		off.next_duration = 0xff-split;
		__sync_synchronize();
	}
}

