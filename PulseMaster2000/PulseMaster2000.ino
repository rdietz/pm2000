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
  
  attachInterrupt(digitalPinToInterrupt(interruptPin), CountGPS, RISING);  //Set up interrupt

  lastButtonState = btn1.getValue();
	counter = 0;
	led.On(RED);
	isActive = false;
  metres = thumb.ReadThumbwheels();

  mode = OPERATE;  // Initial mode
  calibratespeed = CALIBRATE_SPEED_INIT;
  calibrateTime = 3600 / (calibratespeed * PULSES_PER_METRE);

  
	Serial.begin(9600);
  delay(100);
	// Print the banner
  Serial.println();
  Serial.print(F("Firmware Version: ")); Serial.println(VERSION); 
  Serial.println();



// Get EEPROM values
  int flag;
  EEPROM.get(AddrFlag, flag);
  
  if (flag != 123)
  {
    // First run
    Serial.println(F("First run. Set initial operating parameters"));
    // Set the first run flag to make sure this only runs once
    flag = 123;
    EEPROM.put(AddrFlag, flag); 
    
    // Initialise parameters
    PULSES_PER_METRE = 90;  // Initialise Pulses per metre for shaft encoder
    EEPROM.put(AddrPulses, PULSES_PER_METRE);
    
    RELAY1_DELAY = 0;
    EEPROM.put(AddrRelay1Delay, RELAY1_DELAY);
    RELAY1_PULSE_TIME = 500;
    EEPROM.put(AddrRelay1Time, RELAY1_PULSE_TIME);

    RELAY2_DELAY = 500;
    EEPROM.put(AddrRelay2Delay, RELAY2_DELAY);
    RELAY2_PULSE_TIME = 500;
    EEPROM.put(AddrRelay2Time, RELAY2_PULSE_TIME);
    delay(500);
    
    EEPROM.get(AddrRelay1Time, RELAY1_PULSE_TIME);
    EEPROM.get(AddrRelay1Delay, RELAY1_DELAY);
    Serial.print(F("Initialised Relay1 values: ")); Serial.print(RELAY1_PULSE_TIME);Serial.print(" - "); Serial.println(RELAY1_DELAY);
    
    EEPROM.get(AddrRelay2Time, RELAY2_PULSE_TIME);
    EEPROM.get(AddrRelay2Delay, RELAY2_DELAY);
    Serial.print(F("Initialised Relay2 values: ")); Serial.print(RELAY2_PULSE_TIME);Serial.print(" - "); Serial.println(RELAY2_DELAY);

    EEPROM.get(AddrPulses, PULSES_PER_METRE);
    Serial.print(F("Initialised Pulses Per Metre value: ")); Serial.println(PULSES_PER_METRE);

  }

// Get stored params
  EEPROM.get(AddrRelay1Delay, RELAY1_DELAY);
  EEPROM.get(AddrRelay1Time, RELAY1_PULSE_TIME);
  EEPROM.get(AddrRelay2Delay, RELAY2_DELAY);
  EEPROM.get(AddrRelay2Time, RELAY2_PULSE_TIME);
  EEPROM.get(AddrPulses, PULSES_PER_METRE);

  Serial.print(F("Pulses Per Metre value: ")); Serial.print(PULSES_PER_METRE); 
  Serial.println();
/*  
  Serial.println(RELAY1_DELAY);
  Serial.println(RELAY1_PULSE_TIME);
  Serial.println(RELAY2_DELAY);
  Serial.println(RELAY2_PULSE_TIME);
*/

  // Check if this is a calibration run mode
  
  if (metres == 0.01)
  {
  mode = CALRUN;
  Serial.println();
  Serial.println(F("*** Calibration Run Mode *** \n"));
  }

	// Print details if in Calibrate mode
  else if (mode == CALMODE)
  {
    Serial.println(F("Mode is set to CALIBRATE"));
    Serial.print(F("Simulation speed is: ")); Serial.print(calibratespeed); Serial.println(F(" km/hr"));
    Serial.print(F("Simulation pulse period is: ")); Serial.print(calibrateTime); Serial.println(F(" mSec"));
    Serial.print(F("Time between operations is: ")); Serial.print((3.6 * metres) / calibratespeed); Serial.println(F(" Seconds \n"));

    // Output the menu
     show_menu();
  }
  else
  {
    Serial.println(F("*** Mode is set to OPERATE"));
    Serial.println(F("Press C to switch to Calibrate mode \n"));
    Serial.println(F("Waiting to start \n"));
  }
  
  // Set up for the first operation at the starting point
  firstcycle = true;
}


void loop()
{
  // If in Calibrate mode, output the menu
  if (mode == CALMODE)
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

      if (incomingByte == 67)  // Received "C" character
      {
        mode = CALMODE;
        isActive = false;
        led.On(RED);
        Serial.println(F("Switch to CALIBRATE mode \n"));
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
			
			// check thumbwheels aren't set too low
			if (metres > MINIMUM_DISTANCE && (mode == OPERATE || mode == CALMODE))
			{
				lastCounter = 0;
				isActive = true;
				lastMillis = millis();
        calibrateMillis = millis();  // Calibrate
        led.On(GREEN);
				float totalPulses = metres * PULSES_PER_METRE;
				PulsesPerTrigger = (long) totalPulses;
       
        Serial.println(F("*** Button has been pushed. Activating! \n"));

        Serial.print(F("Firmware Version: ")); Serial.println(VERSION);
        Serial.print(F("Distance setting: ")); Serial.println(metres);
        Serial.print(F("Pulses per trigger: ")); Serial.println(PulsesPerTrigger);
        Serial.println();
        
        if (mode == CALMODE)
        {
          calibrateTime = 3600 / (calibratespeed * PULSES_PER_METRE);
          Serial.println(F("Simulation mode is ON"));
          Serial.print(F("Simulation speed is: ")); Serial.print(calibratespeed); Serial.println(F(" km/hr"));
          Serial.print(F("Simulation pulse period is: ")); Serial.print(calibrateTime); Serial.println(F(" mSec"));
          Serial.print(F("Time between operations is: ")); Serial.print((3.6 * metres) / calibratespeed); Serial.println(F(" Seconds \n"));
        }

        if (mode == CALRUN)
        {
          firstcycle = false;
        }
        
        // Check for first cycle
        if (firstcycle)
        {
          firstcycle = false; // do this only once each time the button is pushed!
          counter = 100 * PULSES_PER_METRE;  // set up for immediate operation after a delay
          delay(1000);
        }
			}
     else if (mode == OPERATE || mode == CALMODE) // if thumbwheels set to too low, flash red
			{
				led.Flash(RED);
        Serial.println(F("Error condition - distance set too low"));
        Serial.print(F("Distance setting is: ")); Serial.println(metres);
        Serial.print(F("Minimum distance: ")); Serial.println(MINIMUM_DISTANCE);
        Serial.println();
			}
     else if (mode == CALRUN)
     {
      Serial.println(F("Starting Calibration run"));
      isActive = true;
     }
		}
   
		// if active, deactivate
		else
		{
			isActive = false;
			led.On(RED);
      firstcycle = true; // Reset first cycle flag
      Serial.println(F("*** Button has been pushed. De-activating"));

      if (mode == CALRUN)
      {
        long CounterCopy = counter; // Save the counter value
        int calcount = (CounterCopy / CALDISTANCE); // Work out the pulses per metre

        // Sanity check the value
        if (calcount < 20 || calcount > 200) 
        {
          calcount = 99; // Set to a default if out of bounds
        }
        
        PULSES_PER_METRE = calcount; // Save the working copy!!
        
        // Save calibration
        EEPROM.put(AddrPulses, calcount);
        delay(100);
        // Set mode to Operate
        mode = OPERATE;
         
        EEPROM.get(AddrPulses, calcount);
        Serial.println();
        Serial.println(F("Ending Calibration run, setting mode to Operate"));
        Serial.print(F("Total Input Count:      ")); Serial.println(CounterCopy);
        Serial.print(F("Cal Distance:     ")); Serial.println(CALDISTANCE);
        Serial.print(F("Cal. Pulses per metre:  ")); Serial.println(calcount);
        Serial.print(F("Input Pulses per metre: ")); Serial.println(calcount * 4);
      }

      if (mode == OPERATE)
      {
        Serial.println();
        Serial.println(F("Mode is set to OPERATE"));
        Serial.println(F("Press C to switch to Calibrate mode"));
      }
      // In any case...
      Serial.println();
      Serial.println(F("Waiting to start \n"));
      do_menu();
		}
	}
	
	if (isActive)
	{
		// check to see if we are receiving pulses
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
        Serial.println(F("Waiting for pulses \n"));
			}
			lastMillis = millis();
		}

    // Calibrate mode pulse generation
    if (mode == CALMODE)
    {
      if (millis() - calibrateMillis >= calibrateTime)
      {
        counter++; 
        calibrateMillis = millis();
      }
    }
  	
		// check to see if we've reached our required number of pulses
		if (counter >= PulsesPerTrigger && mode != CALRUN)
		{
			relay1.Trigger(Pulse2Trigger);
			counter = 0;
			lastCounter = 0;
      Serial.print(F("Trigger distance has been reached: ")); Serial.print(metres); Serial.println(F(" metres"));
      Serial.println(F("Operate Relay 1"));
      Serial.print(F("Wait ")); Serial.print(RELAY2_DELAY); Serial.println(F(" mSecs"));
		}
	}

	led.Update();		// process any LED activities
	relay1.Update(RELAY1_DELAY, RELAY1_PULSE_TIME);	// process any relay 1 activities
	relay2.Update(RELAY2_DELAY, RELAY2_PULSE_TIME);	// process any relay 2 activities
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
  Serial.println(F("Operate Relay 2 \n")); 
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
    if (mode == OPERATE || mode == CALRUN)
    {
    counter++;	// yep, that's all we have to do
    }
}

