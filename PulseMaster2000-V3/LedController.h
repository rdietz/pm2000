#ifndef LEDCTL_H
#define LEDCTL_H

#include <Arduino.h>

/*
 * This class manages the LED display, capable of displaying either RED or
 * GREEN.  It can also flash the LED in either colour... just because we can.
 */
class LedController
{
	#define OFF		0
	#define GREEN	1
	#define RED		2
	
	// Class Member Variables
	int ledPin1;		// one end of the bi-colour LED
	int ledPin2;		// the other end
	long OnTime;		// milliseconds of on-time
	long OffTime;		// milliseconds of off-time
	int curColour;		// current LED colour

	// These maintain the current state
	int ledState;             	// ledState used to set the LED
	unsigned long lastMillis;  	// will store last time LED was updated
	bool flashing;				// indicates we are currently flashing the LED

	// Constructor - creates a controller and initialises it
	public:
	LedController(int pin1, int pin2)
	{
		ledPin1 = pin1;
		ledPin2 = pin2;
		pinMode(ledPin1, OUTPUT);     
		pinMode(ledPin2, OUTPUT);

		// turn the LED off
		digitalWrite(ledPin1, LOW);
		digitalWrite(ledPin2, LOW);
	  
		OnTime = 500;
		OffTime = 500;

		ledState = LOW; 
		lastMillis = 0;
		flashing = false;
	}

	/*
	 * Flash()
	 *
	 * 
	 */
	void Flash(int colour)
	{
		flashing = true;
		curColour = colour;
		lastMillis = millis();	// start the timer for off-time
	}

	/*
	 * On()
	 *
	 * Turn on the LED with the specified colour.
	 */
	void On(int colour)
	{
		flashing = false;		// ensure flashing is turned off for Justin
		SetColour(colour);
	}
	
	/*
	 * Off()
	 *
	 * Turn the LED off.
	 */
	void Off()
	{
		flashing = false;		// ensure flashing is turned off for Justin
		digitalWrite(ledPin1, LOW);
		digitalWrite(ledPin2, LOW);
	}

	/*
	 * Update()
	 *
	 * Called by the application loop to process the flashing of the LED.
	 */
	void Update()
	{
		if (flashing)
		{
			// check to see if it's time to change the state of the LED
			unsigned long curMillis = millis();

			if ((ledState == HIGH) && (curMillis - lastMillis >= OnTime))
			{
				ledState = LOW;					// Turn it off
				lastMillis = curMillis;			// Remember the time
				digitalWrite(ledPin1, LOW);
				digitalWrite(ledPin2, LOW);
			}
			else if ((ledState == LOW) && (curMillis - lastMillis >= OffTime))
			{
				ledState = HIGH;				// turn it on
				lastMillis = curMillis;			// Remember the time
				SetColour(curColour);
			}
		}
	}

	// "Physically" turn the LED on (RED or GREEN) or OFF.
	private:
	void SetColour(int colour)
	{
		curColour = colour;
		switch(colour)
		{
			case RED:
				digitalWrite(ledPin1, HIGH);
				digitalWrite(ledPin2, LOW);
				break;
				
			case GREEN:
				digitalWrite(ledPin1, LOW);
				digitalWrite(ledPin2, HIGH);
				break;
		}
	}
};

#endif // LEDCTL_H
