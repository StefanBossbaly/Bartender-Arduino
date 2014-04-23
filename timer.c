#include "timer.h"


void (*intFunc)(void) = 0;
void (*intFunc2)(void) = 0;
int times = 0;
int times_init = 0;

void timer2_setup()
{
	// Disable Timer2 interrupt.
	timer2_stop();

	// Clock source for timer2 is from internal clock not external (PG 145)
	ASSR &= ~(1 << AS2);

	// Set Timer2 to CTC mode.
	// Clear timer on compare match
	TCCR2A = (1 << WGM21);

	// Set Timer2 prescaler to 1024 (64uS/count, 64uS - 14400us range).
	TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);

	// Reset Timer2 counter.
	TCNT2 = 0;
}

void timer2_init_us(unsigned long frequency, void (*function)(void))
{
	// Configure the timer interrupt.
	timer2_setup();

	// User's function to call when there's a timer event.
	intFunc = function;

	// Every count is 64uS, so divide by 64 (bitwise shift right 2) subtract one, then make sure we don't go over 255 limit.
	OCR2A = min((frequency >> 6) - 1, 255);
	
	// Enable Timer2 interrupt.
	TIMSK2 |= (1 << OCIE2A);
}

void timer2_ms_countdown()
{
	if (times == 0)
	{
		intFunc2();
		times = times_init;
	}
	else
	{
		times--;
	}
}

void timer2_init_ms(unsigned long frequency, void (*function)(void))
{
	// Configure the timer interrupt.
	timer2_setup();

	// How often we should call the function
	times = times_init = frequency;

	// Call the countdown function every millisecond and count down
	intFunc = timer2_ms_countdown;
	intFunc2 = function;

	// (16 - 1) * 64 = 1024 uS ... close enough 
	OCR2A = 15;

	// Enable Timer2 interrupt
	TIMSK2 |= (1 << OCIE2A);
}

void timer2_stop()
{
	// Page 163 of documentation
	// Disable OCIE2A (Timer/Counter2 Output Compare Match A Interrupt Enable)
	TIMSK2 &= ~(1 << OCIE2A);
}

// ISR of timer 2 compare vector
ISR (TIMER2_COMPA_vect)
{
	if (intFunc)
	{
		intFunc(); // If wrapped function is set, call it.
	}
}
