#include <stdint.h>
#include <inttypes.h>
#define NULL 0

struct period;
struct period {
	uint8_t level;
	uint8_t duration;
	uint8_t credit;
	uint8_t next_duration;
	struct period * next;
};

struct processed_period;
struct processed_period {
	uint8_t levels;
	uint8_t mask;
	uint8_t duration;
	struct processed_period * next;
};

struct period * signals[8];
struct processed_period * signals_processed;

//all configured signals start simultaneously and execute together
void signal_compile_and_sync(void) {
	//choose the soonest elapsed period or finish if all null
	//for each period that elapses at the same time, add it to the result
	//advance those which were added to the next period
}

#define min(a,b) ((a) < (b) ? (a) : (b))

uint8_t signal_tick(uint8_t now) {
	static uint8_t last_time;
	uint8_t future_delta = 0xff; //how long until next event
	uint8_t cur_delta = now - last_time;
	last_time = now;

	uint8_t port_mask = 0, port_vals = 0;

	for (uint8_t i = 0; i < 8; i++) {
		if (signals[i] == NULL) continue; //no signal

		uint8_t credit = signals[i]->credit;
		uint8_t tmp = credit + cur_delta;
		if (tmp < credit) //overflow, so saturate
			tmp = 0xff;
		credit = tmp;

		while (credit >= signals[i]->duration) {
			//elapsed
			signals[i] = signals[i]->next;
			port_mask |= _BV(i);
			if (signals[i]->level)
				port_vals |= _BV(i);
			else
				port_vals &= ~_BV(i);
			credit = 0;
			signals[i]->duration = signals[i]->next_duration;
		}

		signals[i]->credit = credit;
		future_delta = min(future_delta, signals[i]->duration - credit);
	}

	SIGNAL_PORT = (SIGNAL_PORT & ~port_mask) | port_vals;

	return now + future_delta;
}
