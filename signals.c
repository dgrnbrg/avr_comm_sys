//
//  main.c
//  avr_comm_sys
//
//  Created by David Greenberg on 8/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <signal.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <inttypes.h>

#define SIGHIGH SIGUSR1
#define SIGLOW SIGUSR2

//.5ms
#define PERIOD 1000
#define SYNC_PERIOD (8*PERIOD)
#define LOW_PERIOD (2*PERIOD)
#define HIGH_PERIOD (4*PERIOD)

enum last_state_t {
    LOW,
    HIGH
};

static volatile enum last_state_t last_state = LOW;
static volatile uint64_t last_time;
static volatile unsigned int recieved_data;
static volatile uint32_t recieved_bit_cnt;

static int fuzz_test(uint64_t base, uint64_t x, uint64_t fuzz) {
    return x < base + fuzz && x + fuzz > base;
}

//here, we just store the state
static void high_to_low_trans() {
    printf("[%u] saw high-to-low\n",getpid());
    struct timeval tp;
    gettimeofday(&tp, NULL);
    
    uint64_t diff =  (uint64_t)tp.tv_usec - last_time;
    
    //we want to shift in a zero or one depending on if we got a 1 or 2 period signal
    recieved_data <<= 1;
    if (fuzz_test(LOW_PERIOD, diff, PERIOD)) {
        printf("[%u] got 0\n",getpid());
        recieved_bit_cnt++;
    } else if (fuzz_test(HIGH_PERIOD, diff, PERIOD)) {
        recieved_data |= 1;
        recieved_bit_cnt++;
        printf("[%u] got 1\n",getpid());
    } else if (fuzz_test(SYNC_PERIOD, diff, PERIOD)) {
        printf("[%u] got SYNC\n",getpid());
        recieved_bit_cnt = 0;
    } else {
        printf("[%u] error in bit recieve--out of time bounds (got %llu)\n", getpid(), diff);
    }
                  
    last_time = tp.tv_usec;
}

static void low_to_high_trans() {
    printf("[%u] saw low-to-high\n",getpid());
    struct timeval tp;
    gettimeofday(&tp, NULL);
    last_time = tp.tv_usec;
}

// this shouldn't happen but can in anomylous situations
static void no_trans(enum last_state_t s) {
    printf("[%u] error in bit recieve--no change detected\n",getpid());
}

static void pc_high(int sig) {
    assert(sig == SIGHIGH);
    if (last_state == LOW)
        low_to_high_trans();
    else
        no_trans(HIGH);
    last_state = HIGH;
}

static void pc_low(int sig) {
    assert(sig == SIGLOW);
    if (last_state == HIGH)
        high_to_low_trans();
    else
        no_trans(LOW);
    last_state = LOW;
}

static void send_hardware(int target, unsigned int period) {
    kill(target, SIGHIGH);
    usleep(period);
    kill(target, SIGLOW);
    usleep(LOW_PERIOD);
}

static void send_data(int target, uint32_t len, uint64_t data) {
    send_hardware(target, SYNC_PERIOD);
    for (int i = 0; i < len; i++) {
        if ((data & 1<<i)) {
            send_hardware(target, HIGH_PERIOD);
        } else {
            send_hardware(target, LOW_PERIOD);
        }
    }
    usleep(SYNC_PERIOD);
}

static void root_producer(int child0, int child1) __attribute__((noreturn));
static void root_producer(int child0, int child1) {
    printf("root producer with kids %d and %d\n", child0, child1);
    usleep(SYNC_PERIOD * 10);
    send_data(child0, 8, 0xAA);
    usleep(1000);
    send_data(child1, 8, 0x55);
    exit(0);
}

int main (int argc, const char * argv[])
{
    // we'll create a binary tree of nodes
    // each time we fork 2 children, and send them signals to propagate
    // protocol is high for 6 cycles, then boolean for addr or data, then address or data follows (data goes with previous addr)
    // empty addr == process data
    
    signal(SIGHIGH, pc_high);
    signal(SIGLOW, pc_low);
    const int max_depth = 2;
    int depth = max_depth;
    int child0, child1;
    while (--depth) {
        child0 = child1 = 0;
        if ((child0 = fork()) && (child1 = fork())) //child
            break;
        printf("forking...\n");
    }
    
    if (depth == max_depth - 1 && child0 && child1) root_producer(child0, child1);
    
    printf("child waiting for commands\n");
    
    //here, we have the two child process pids
    //or, if depth == 0, this is a terminal
    int primed = 0;
    while(1) {
        struct timeval tp;
        gettimeofday(&tp, NULL);
        //if it's been low for a while
        if (primed && last_state == LOW && (uint64_t)tp.tv_usec - last_time > SYNC_PERIOD) {
            printf("got message 0x%x, length %u\n",recieved_data, recieved_bit_cnt);
            break;
#if 0
            //see if it's retrans or for us, then quit
            assert(recieved_bit_cnt >= 1);
            if ((recieved_data & (1 << (recieved_bit_cnt-1)))) {
                //starts with a one
            } else {
                //starts with a zero
            }
#endif
            primed = 0;
        }
        if (last_state == HIGH) primed = 1;
        usleep(1);
    }
    printf("thread finished\n");
    return 0;
}

