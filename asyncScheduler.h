/**
 * @file asyncScheduler.h
 * @author Darren Remund (darren.remund@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-10-18
 * 
 * 
 */

#include "asyncScheduler_defs.h"

#ifndef ASYNC_SCHEDULER_H
#define ASYNC_SCHEDULER_H

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief 
 * 
 * @param timer
 * @param period_us
 */
void asyncScheduler_init(uint8_t timer, asyncScheduler_time_t period_us);

/**
 * @brief 
 * 
 * @param callback_ptr 
 * @param period_us 
 */
void asyncScheduler_addCallback(asyncScheduler_callback_fptr callback_ptr, uint16_t period_us);

/**
 * @brief 
 * 
 */
void asyncScheduler_runCallbacks();


#ifdef __cplusplus
}
#endif
#endif /* ASYNC_SCHEDULER_H */
