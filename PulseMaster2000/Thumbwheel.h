#ifndef THUMB_H
#define THUMB_H

/*
 * This header file contains the planting-specific code.
 */
#include <Arduino.h>
class Thumbwheel
{
	// Constructor - creates a Thumbwheel & initializes it
	public:
	Thumbwheel()
	{
		pinMode(thumbDigit1Pin, OUTPUT); // Units
		pinMode(thumbDigit2Pin, OUTPUT); // Tenths
    pinMode(thumbDigit3Pin, OUTPUT); // Hundredths
		pinMode(thumb1Pin, INPUT_PULLUP);
		pinMode(thumb2Pin, INPUT_PULLUP);
		pinMode(thumb4Pin, INPUT_PULLUP);
		pinMode(thumb8Pin, INPUT_PULLUP);

		// initialise the pins to turn selection off
		digitalWrite(thumbDigit1Pin, HIGH);
    digitalWrite(thumbDigit2Pin, HIGH);
    digitalWrite(thumbDigit3Pin, HIGH);
	}

	/*
	 * ReadThumbwheels()
	 *
	 * This function reads the thumbwheel settings and returns a float value
	 * representation (e.g. - 02 = 0.2, 19 = 1.9).
	 */
	float ReadThumbwheels()
	{
		float thumbValue;
	
		// Read the unit number
		digitalWrite(thumbDigit1Pin, LOW);
    delay(100);
		thumbValue = GetValue();
		digitalWrite(thumbDigit1Pin, HIGH);
    delay(100);
	
		// Read the tenths number
		digitalWrite(thumbDigit2Pin, LOW);
    delay(100);
		float tenthsValue = (float) GetValue();
		thumbValue += tenthsValue / 10;
		digitalWrite(thumbDigit2Pin, HIGH);
    delay(100);

    // Read the hundredths number
    digitalWrite(thumbDigit3Pin, LOW);
    delay(100);
    float hundredthsValue = (float) GetValue();
    thumbValue += hundredthsValue / 100;
    digitalWrite(thumbDigit3Pin, HIGH);
    delay(100);
  
		return thumbValue;
	}

	private:
	/*
	 * GetValue()
	 *
	 * Reads the currently selected digit, converting the BCD value to an integer.
	 */
	int GetValue()
	{
		int value = 0;
	
		// Read each of the BCD values and convert to an int
		value += (digitalRead(thumb1Pin) == LOW ? 1 : 0);
		value += (digitalRead(thumb2Pin) == LOW ? 2 : 0);
		value += (digitalRead(thumb4Pin) == LOW ? 4 : 0);
		value += (digitalRead(thumb8Pin) == LOW ? 8 : 0);
		
		return value;
	}
};

#endif	// THUMB_H
