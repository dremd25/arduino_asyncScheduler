/**
 * @file asyncScheduler_defs.h
 * @author Darren Remund (darren.remund@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-10-18
 * 
 * 
 */

#include "Arduino.h"

#ifndef ASYNC_SCHEDULER_DEFS_H
#define ASYNC_SCHEDULER_DEFS_H

#ifdef __cplusplus
extern "C"{
#endif

#define TIMER_0 0
#define TIMER_0_PERIOD_US
#define TIMER_1 1
#define TIMER_1_PERIOD_US
#define TIMER_2 2
#define TIMER_2_PERIOD_US

typedef uint16_t asyncScheduler_time_t;
typedef uint16_t asyncScheduler_ticks_t;
typedef void (*asyncScheduler_callback_fptr)();

typedef struct asyncScheduler_callback_t {
    asyncScheduler_callback_fptr callback_ptr;
    asyncScheduler_ticks_t ticks;
    asyncScheduler_ticks_t tickPeriod;
} asyncScheduler_callback_t;

#ifdef __cplusplus
}
#endif
#endif /* ASYNC_SCHEDULER_DEFS_H */