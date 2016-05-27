// PulseMaster 2000

#include "Constants.h"
#include "LedController.h"
#include "Debouncer.h"
#include "Thumbwheel.h"
#include "Pulser.h"
#include "Global.h"
#include "Menu.h"


void setup()
{
  MCUSR = 0;  // clear out any flags of prior resets.
	lastButtonState = btn1.getValue();
	attachInterrupt(gpsInterrupt, CountGPS, RISING);
	counter = 0;
	led.On(RED);
	isActive = false;
  metres = thumb.ReadThumbwheels();

  calmode = CALIBRATE_MODE_INIT;
  calibratespeed = CALIBRATE_SPEED_INIT;
  calibrateTime = 3600 / (calibratespeed * GPS_PULSES_PER_METRE);
  
	Serial.begin(9600);
  delay(100);
	// Print the banner
  Serial.println(" ");
  Serial.println("*** Restart ***");

  Serial.print("Firmware Version: ");
  Serial.println(VERSION);
  Serial.println(" ");
	// Print details if in Calibrate mode
  if (calmode)
  {
    Serial.println("Mode is set to CALIBRATE");
    Serial.print("Calibration speed is: ");
    Serial.print(calibratespeed);
    Serial.println(" km/hr");
    
    Serial.print("Calibration pulse period is: ");
    Serial.print(calibrateTime);
    Serial.println(" mSec");

    Serial.print("Time between operations is: ");
    Serial.print((3.6 * metres) / calibratespeed);
    Serial.println(" Seconds");
    Serial.println(" ");

    // Output the menu
     show_menu();
  }
  else
  {
    Serial.println("*** Mode is set to OPERATE");
    Serial.println("Press C to switch to Calibrate mode");
    Serial.println(" ");
    Serial.println("Waiting to start");
    Serial.println(" ");
  }
  
  // Set up for the first operation at the starting point
  firstcycle = true;
}


void loop()
{
  // If in Calibrate mode, output the menu
  if (calmode)
  {
    do_menu();
  }
  else  // Look for serial command to change mode
  {
  int incomingByte = 0;   // for incoming serial data
  
    if (Serial.available() > 0) 
    {
      // read the incoming byte:
      incomingByte = Serial.read();
      //Serial.setTimeout(500);
      //Serial.print("Received: ");
      //Serial.println(incomingByte);

      if (incomingByte == 67)
      {
        calmode = true;
        isActive = false;
        led.On(RED);
        Serial.println("Switch to CALIBRATE mode");
        Serial.println(" ");
        String str = Serial.readStringUntil('\n');
        show_menu();
      } 
    }
  }

	// if button has been pressed, start the GPS Counting
	if (checkButtonPressed())
	{
		// if not active, activate!
		if (!isActive)
		{
			metres = thumb.ReadThumbwheels();
			
			// quickly make sure thumbwheels aren't set too low
			if (metres > MINIMUM_DISTANCE)  
			{
				lastCounter = 0;
				isActive = true;
				lastMillis = millis();
        calibrateMillis = millis();  // Calibrate
				led.On(GREEN);
				float totalPulses = metres * GPS_PULSES_PER_METRE;
				gpsPulsesPerTrigger = (long) totalPulses;
       
        Serial.println("*** Button has been pushed. Activating!");
        Serial.println(" ");
        Serial.print("Firmware Version: ");
        Serial.println(VERSION);
        
        Serial.print("Distance setting: ");
        Serial.println(metres);
        Serial.print("Pulses per trigger: ");
        Serial.println(gpsPulsesPerTrigger);
        Serial.println(" ");
        
        if (calmode)
        {
          Serial.println("Calibration mode is ON");
          Serial.print("Calibration speed is: ");
          Serial.println(calibratespeed);
          
          Serial.print("Calibration pulse period is: ");
          Serial.print(calibrateTime);
          Serial.println(" mSec");
          
          Serial.print("Time between operations is: ");
          Serial.print((3.6 * metres) / calibratespeed);
          Serial.println(" Seconds");
          Serial.println(" ");
        }
        
        // Check for first cycle
        if (firstcycle)
        {
          firstcycle = false; // do this only once each time the button is pushed!
          counter = 100 * GPS_PULSES_PER_METRE;  // set up for immediate operation after a delay
          delay(1000);
        }
			}
     
			// if thumbwheels set to too low, flash red
			else
			{
				led.Flash(RED);
        Serial.println("Error condition - distance set too low");
        Serial.print("Distance setting is: ");
        Serial.println(metres);
        Serial.print("Minimum distance: ");
        Serial.println(MINIMUM_DISTANCE);
        Serial.println(" ");
			}
		}
   
		// if active, deactivate
		else
		{
			isActive = false;
			led.On(RED);
      firstcycle = true; // Reset first cycle flag
      Serial.println("*** Button has been pushed. De-activating");
      if (!calmode)
      {
        Serial.println("");
        Serial.println("Mode is set to OPERATE");
        Serial.println("Press C to switch to Calibrate mode");
      }
      Serial.println(" ");
      Serial.println("Waiting to start");
      Serial.println("");
      do_menu();
		}
	}
	
	if (isActive)
	{
		// check to see if we are receiving GPS pulses
		if (millis() - lastMillis >= 2000)
		{
			if (counter > lastCounter)
			{
				led.Flash(GREEN);
				lastCounter = counter;
			}
			else
			{
				led.On(GREEN);
        Serial.println("Waiting for GPS pulses");
        Serial.println(" ");
			}
			lastMillis = millis();
		}

    // Calibrate mode
    if (calmode)
    {
      if (millis() - calibrateMillis >= calibrateTime)
      {
        counter++; 
        calibrateMillis = millis();
      }
    }
  	
		// check to see if we've reached our GPS pulses
		if (counter >= gpsPulsesPerTrigger)
		{
			relay1.Trigger(Pulse2Trigger);
			counter = 0;
			lastCounter = 0;
      Serial.print("Trigger distance has been reached: ");
      Serial.print(metres);
      Serial.println(" metres");
      
      Serial.println("Operate Relay 1");
      Serial.print("Wait ");
      Serial.print(RELAY2_DELAY);
      Serial.println(" mSecs");
		}
	}

	led.Update();		// process any LED activities
	relay1.Update();	// process any relay 1 activities
	relay2.Update();	// process any relay 2 activities
}


/*
 * Pulse2Trigger()
 *
 * This function is registered as the Pulser callback for pulse 1. It will be
 * called at the end of the pulse 1 and triggers the 2nd pulse.
 */
void Pulse2Trigger()
{
	relay2.Trigger();
  Serial.println("Operate Relay 2");
  Serial.println(" ");
 
}


/*
 * CheckButtonPressed()
 *
 * Execute code only once on the transition from LOW to HIGH, representing the
 * initial button press.
 */
bool checkButtonPressed()
{
	bool buttonWasPressed = false;
	
	// check for button pressed
	if (lastButtonState == HIGH && btn1.getValue() == LOW)
	{
		buttonWasPressed = true;
		lastButtonState = LOW;
	}
	// check for button release
	else if (lastButtonState == LOW && btn1.getValue() == HIGH)
	{
		lastButtonState = HIGH;
	}
	return buttonWasPressed;
}

/*
 * CountGPS()
 *
 * Proessing when the GPS pulse is received via interrupt.
 */
void CountGPS()
{
    if (!calmode)
    {
    counter++;	// yep, that's all we have to do
    }
}

