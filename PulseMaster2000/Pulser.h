#ifndef PULSER_H
#define PULSER_H

#include <Arduino.h>

typedef void (*GeneralFunction) ();

/*
 * This class provides control over the generation of a pulse to a specific pin.
 */
class Pulser
{
	#define IDLE_STATE		0
	#define DELAY_STATE		1
	#define ON_STATE		2

	// Class Member Variables
	int pulsePin;				// the pin we're pulsing
	int curPulseValue;			// current output value
	int lastPulseValue;			// last output value
	unsigned long lastMillis;	// last millisecond value
	long delayTime;				// milliseconds of delay before on-time
	long onTime;				// milliseconds of on-time
	int pulseState;				// track where we are in the pulse
	GeneralFunction callback;	// callbackfunction

	// Constructor - creates a Pulser object and initialises everything
	public:
	Pulser(int pin, long delay, long on)
	{
		pulsePin = pin;
		delayTime = delay;
		onTime = on;
		
		curPulseValue = HIGH;  ///// TG
		lastMillis = 0;
		pulseState = IDLE_STATE;
		pinMode(pulsePin, OUTPUT);
		digitalWrite(pulsePin, curPulseValue);
	}

	/*
	 * Trigger()
	 *
	 * Trigger the pulse.  If a callback function is specified, register it
	 * so it can be called when the pulse cycle has completed. Useful for
	 * chaining pulses together.
	 */
	void Trigger()
	{
		pulseState = DELAY_STATE;	// flag start of delay state
		lastMillis = millis();		// remember the start time for the delay state
	}
	void Trigger(GeneralFunction func)
	{
		callback = func;
		Trigger();
	}

	/*
	 * Update()
	 *
	 * Called by the application loop to process the pulse.
	 */
	void Update()
	{
		// check to see if it's time to change the state of the LED
		unsigned long curMillis = millis();

		// if we're not in idle mode...
		if (pulseState != IDLE_STATE)
		{
			if (pulseState == DELAY_STATE && (curMillis - lastMillis >= delayTime))
			{
				// end of delay, turn the pulse on
				pulseState = ON_STATE;
				lastMillis = curMillis;			// Remember the start of on-time
				digitalWrite(pulsePin, LOW);  //////TG
			}
			else if (pulseState == ON_STATE && (curMillis - lastMillis >= onTime))
			{
				// end of on-time, turn the pulse off
				pulseState = IDLE_STATE;
				digitalWrite(pulsePin, HIGH);  //////TG
				
				// if there is a callback function specified, call it now
				if (callback)
				{
					callback();
				}
			}
		}
	}
};

#endif	// PULSER_H
