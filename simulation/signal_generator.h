#ifndef _SIGNAL_GENERATOR_H_
#define _SIGNAL_GENERATOR_H_

#include <avr/interrupt.h>
#include <avr/io.h>

#define PWM_PORT PORTB
#define TIMER_ISR TIMER0_COMPA_vect
#define TIMER_OVF TIMER0_COMPB_vect
#define TIMER_CNT TCNT0
#define TIMER_OCR OCR0A
#define TIMER_TOP OCR0B

void pwm_set_duty_cycle(uint8_t index, uint8_t cycle);

void pwm_set_enable_mask(uint8_t mask);

void pwm_set_period(uint8_t period);

uint8_t pwm_tick(uint8_t now, uint8_t * next_time);

void pwm_overflow(void);

#endif
