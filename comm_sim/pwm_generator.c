#include <stdint.h>
#include <inttypes.h>
#define NULL 0

struct period;
struct period {
	uint8_t level;
	uint8_t duration;
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
		if (signals[i]->duration > cur_delta) {
			//in the future
			future_delta = min(future_delta, signals[i]->duration - cur_delta);
			continue;
		}
		//elapsed
		port_mask |= _BV(i);
		if (signals[i]->level) port_vals |= _BV(i);
	}

	SIGNAL_PORT = (SIGNAL_PORT & ~port_mask) | port_vals;

	PORTB = now;

	return now + future_delta;
}
