/**
 * @file asyncScheduler.c
 * @author Darren Remund (darren.remund@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-10-18
 * 
 * 
 */

#include "asyncScheduler.h"

static asyncScheduler_time_t async_callbackPeriod_us;
static asyncScheduler_callback_t *callbacks;
static uint16_t numCallbacks;

void asyncScheduler_init(uint8_t timer, asyncScheduler_time_t period_us) {
    numCallbacks = 0;
    async_callbackPeriod_us = period_us;

    cli();

    switch(timer) {
    case TIMER_0:
        //set timer0 interrupt at 2kHz
        TCCR0A = 0;// set entire TCCR0A register to 0
        TCCR0B = 0;// same for TCCR0B
        TCNT0  = 0;//initialize counter value to 0
        // set compare match register for 2khz increments
        OCR0A = 124;// = (16*10^6) / (2000*64) - 1 (must be <256)
        // turn on CTC mode
        TCCR0A |= (1 << WGM01);
        // Set CS01 and CS00 bits for 64 prescaler
        TCCR0B |= (1 << CS01) | (1 << CS00);   
        // enable timer compare interrupt
        TIMSK0 |= (1 << OCIE0A);
        break;
    case TIMER_1:
        //set timer1 interrupt at 1Hz
        TCCR1A = 0;// set entire TCCR1A register to 0
        TCCR1B = 0;// same for TCCR1B
        TCNT1  = 0;//initialize counter value to 0
        // set compare match register for 1hz increments
        OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
        // turn on CTC mode
        TCCR1B |= (1 << WGM12);
        // Set CS10 and CS12 bits for 1024 prescaler
        TCCR1B |= (1 << CS12) | (1 << CS10);  
        // enable timer compare interrupt
        TIMSK1 |= (1 << OCIE1A);
        break;
    case TIMER_2:
        //set timer2 interrupt at 8kHz
        TCCR2A = 0;// set entire TCCR2A register to 0
        TCCR2B = 0;// same for TCCR2B
        TCNT2  = 0;//initialize counter value to 0
        // set compare match register for 8khz increments
        OCR2A = 249;// = (16*10^6) / (8000*8) - 1 (must be <256)
        // turn on CTC mode
        TCCR2A |= (1 << WGM21);
        // Set CS21 bit for 8 prescaler
        TCCR2B |= (1 << CS21);   
        // enable timer compare interrupt
        TIMSK2 |= (1 << OCIE2A);
        break;
    default:
        break;
    }

    sei();
}


void asyncScheduler_addCallback(asyncScheduler_callback_fptr callback_ptr, uint16_t period_us) {
    asyncScheduler_callback_t *temp;

    numCallbacks++;
    temp = malloc(numCallbacks * sizeof(asyncScheduler_callback_t));

    for(uint16_t i = 1; i < numCallbacks; i++)
        temp[i - 1] = callbacks[i];
    
    temp[numCallbacks - 1].callback_ptr = callback_ptr;
    temp[numCallbacks - 1].tickPeriod = period_us / async_callbackPeriod_us;
    temp[numCallbacks - 1].ticks = 0;
    
    free(callbacks);
    callbacks = temp;
}

void asyncScheduler_runCallbacks() {
    cli();

    for(uint16_t i = 0; i < numCallbacks; i++) {
        callbacks[i].ticks++;
        if(callbacks[i].ticks >= callbacks[i].tickPeriod) {
            callbacks[i].callback_ptr();
            callbacks[i].ticks = 0;
        }
    }

    sei();
}

