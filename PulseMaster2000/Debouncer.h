#ifndef DEBOUNCER_H
#define DEBOUNCER_H

#include <Arduino.h>

// The purpose of this class is to sample a specific digital input that may be
// connected to a mechanical switch, necessitating the need to allow for bouncing.
class Debouncer
{
	// Class Member Variables
	// These are initialized at startup
	int samplePin;				// the input pin to be sampled
	int curPinValue;			// current input value
	int lastPinValue;			// last input value
	unsigned long lastMillis;	// last millisecond value

	// Constructor - creates a Flasher 
	// and initializes the member variables and state
	public:
	Debouncer(int pin)
	{
		samplePin = pin;
		pinMode(samplePin, INPUT_PULLUP);   // TLG
		curPinValue = digitalRead(samplePin);
		lastPinValue = curPinValue;
		lastMillis = 0;
	}

	int getValue()
	{
		// Check pin value every 10 msecs
		if (millis() - lastMillis > 10)
		{
			int pinValue = digitalRead(samplePin);
			
			// if this value is the same as the last sample, consider it changed
			if (pinValue == lastPinValue)
			{
				curPinValue = pinValue;
			}
			lastPinValue = pinValue;
			lastMillis = millis();
		}
		return curPinValue;
	}
};

#endif	// DEBOUNCER_H
