#ifndef _SIGNAL_GENERATOR_H_
#define _SIGNAL_GENERATOR_H_

#define PWM_PORT PORTB
#define TIMER_ISR TIM0_COMPA_vect
#define TIMER_OVF TIM0_COMPB_vect
#define TIMER_CNT TCNT0
#define TIMER_OCR OCR0A
#define TIMER_TOP OCR0A

void pwm_set_duty_cycle(uint8_t index, uint8_t cycle);

void pwm_set_enable_mask(uint8_t mask);

void pwm_set_period(uint8_t period);

#endif
