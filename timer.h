/**
 * @file   timer.h
 * @brief  Defines functions that use the timer to call other functions at
 * a given frequency.
 * @author Stefan Bossbaly (sbossb@gmail.com)
 * @date   April, 2014
 *
 */
#ifndef TIMER_H
#define	TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @name    Initialize Timer using Microseconds
 * @brief   Use the timer to call the function at the specified frequency in
 * microseconds.
 * @ingroup timer
 *
 * Calls the function at the specified frequency. This is accomplished
 * using the timer compare interrupt.
 *
 * @param [in] frequency the time (in microseconds) between function calls
 * @param [in] function the function that will be called at the given
 * frequency
 *
 */
void timer2_init_us(unsigned long frequency, void (*function)(void));

/**
 * @name    Initialize Timer using Milliseconds
 * @brief   Use the timer to call the function at the specified frequency in
 * milliseconds.
 * @ingroup timer
 *
 * Calls the function at the specified frequency. This is accomplished
 * using the timer compare interrupt.
 *
 * @param [in] frequency the time (in milliseconds) between function calls
 * @param [in] function the function that will be called at the given
 * frequency
 *
 */
void timer2_init_ms(unsigned long frequency, void (*function)(void));

/**
 * @name    Disable Timer
 * @brief   Stops the timer from counting.
 * @ingroup timer
 *
 * Stops the timer from counting. The specified function will no longer be
 * called at the given frequency.
 *
 */
void timer2_stop();

#ifdef __cplusplus
}
#endif

#endif	/* TIMER_H */
