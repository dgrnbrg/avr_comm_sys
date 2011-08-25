
#include <stdint.h>
#include "signal_generator.h"


//this allows for 8 max pwm channels, since they
//must happen on a single port

//we store the duty cycle for each pin and the enable mask
volatile static uint8_t softpwm_duty_cycles[8];
volatile static uint8_t softpwm_enable_mask;

void pwm_set_duty_cycle(uint8_t index, uint8_t cycle) {
  softpwm_duty_cycles[index] = cycle;
}

void pwm_set_enable_mask(uint8_t mask) {
  softpwm_enable_mask = mask;
  pwm_overflow();
}

void pwm_set_period(uint8_t period) {
  TIMER_TOP = period;
}

void pwm_overflow(void) {
  uint8_t mask = softpwm_enable_mask;
  uint8_t x = 0;
  uint8_t first_int = 0xff;
  for (uint8_t i = 0; i < 8; i++) {
    uint8_t duty_cycle = softpwm_duty_cycles[i];
    if (duty_cycle) x |= _BV(i);
    if (duty_cycle && duty_cycle < first_int) first_int = duty_cycle;
  }
  TIMER_OCR = first_int;
  //turn off all pwm pins, then reenable the ones with nonzero duty cycles
  PWM_PORT = (PWM_PORT & ~mask) | x;
}

uint8_t pwm_tick(uint8_t now, uint8_t * next_time) {
  uint8_t mask = softpwm_enable_mask;
  uint8_t x = 0xff;

  *next_time = 0xff;
  uint8_t found_next = 0;

  for (uint8_t i = 0; i < 8; i++) {
    if ((mask & _BV(i)) == 0) continue;
    uint8_t duty_cycle = softpwm_duty_cycles[i];
    //turn off earlier ones and find the nearest next one
    if (duty_cycle <= now) {
      x &= ~_BV(i);
    } else if (duty_cycle <= *next_time) {
      found_next = 1;
      *next_time = duty_cycle;
    }
  }
  PWM_PORT &= x;
  PORTC = (PORTC & 0xf0) | (0xf & x);
  return found_next;
}

