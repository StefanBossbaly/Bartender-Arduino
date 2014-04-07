#ifndef TIMER_H
#define	TIMER_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
#else
	#include <WProgram.h>
	#include <pins_arduino.h>
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

#ifdef __cplusplus
extern "C"
{
#endif

void timer2_setup();
void timer2_init_us(unsigned long frequency, void (*function)(void));
void timer2_init_ms(unsigned long frequency, void (*function)(void));
void timer2_stop();

void timer1_setup();
void timer1_init_ms(unsigned long frequency, void (*function)(void));
void timer1_stop();

#ifdef __cplusplus
}
#endif

#endif	/* TIMER_H */