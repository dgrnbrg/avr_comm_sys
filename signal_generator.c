#include <avr/interrupt.h>
#include <stdint.h>


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
}

void pwm_set_period(uint8_t period) {
  TIMER_TOP = period;
}

static void pwm_overflow(void) {
  uint8_t mask = softpwm_enable_mask;
  uint8_t x = mask;
  for (uint8_t i = 0; i < 8; i++) {
    if (!softpwm_duty_cycles[i]) x &= ~_BV(i);
  }
  //turn off all pwm pins, then reenable the ones with nonzero duty cycles
  PWM_PORT = (PWM_PORT & ~mask) | x;
}

static uint8_t pwm_tick(uint8_t now, uint8_t * next_time) {
  uint8_t mask = softpwm_enable_mask;
  uint8_t x = mask;

  *next_time = 0xff;
  uint8_t found_next = 0;

  for (uint8_t i = 0; i < 8; i++) {
    uint8_t duty_cycle = softpwm_duty_cycles[i];
    //turn off earlier ones and find the nearest next one
    if (duty_cycle <= now)
      x &= ~_BV(i);
    else if (duty_cycle <= next_time) {
      found_next = 1;
      *next_time = duty_cycle;
    }
  }
  PWM_PORT = (PWM_PORT & ~mask
  return found_next;
}

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
