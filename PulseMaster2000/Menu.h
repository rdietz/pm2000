#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include <avr/wdt.h>
#include <EEPROM.h>
#include "Global.h"

// Routines for menu handling


void show_menu()
{
    Serial.println("Setup Menu");
    Serial.println(F("1. Set Relay 1 times"));
    Serial.println(F("2. Set Relay 2 times"));
    Serial.println(F("3. Set Pulses per metre"));
    Serial.println(F("4. Set Simulation speed"));
    Serial.println(F("5. Display settings"));

    Serial.println();
    Serial.println(F("O. Switch to Operate mode \n"));
    Serial.println(F("R. RESET \n"));
    Serial.println(F("Waiting to start Simulation run \n"));

}


void do_CalSpeed()
{
  int incomingByte = 0;
  String str;
  float inputspeed;

  Serial.println(F("Input the speed in km/hr (0.1 - 3) \n"));

  str = Serial.readStringUntil('\n'); // empty the buffer

  Serial.setTimeout(5000);
  str = Serial.readStringUntil('\n');
  Serial.print(F("Input: ")); Serial.print(str);
  Serial.println();

  inputspeed = str.toFloat();
  if ((inputspeed < 0.1) || (inputspeed > 3.0))
  {
    Serial.print(F("Invalid value"));
  }
  else
  {
    calibratespeed = inputspeed;
  }

  calibrateTime = 3600 / (calibratespeed * PULSES_PER_METRE); // calculate the time between pulses
  
  Serial.println("");
  Serial.print(F("Calibration speed set to : ")); Serial.print(calibratespeed); Serial.println(F(" km/hr \n"));
    
  Serial.print(F("Time between operations is: ")); Serial.print((3.6 * metres) / calibratespeed); Serial.println(F(" Seconds \n"));

  Serial.print(F("Time between pulses is: ")); Serial.print(calibrateTime); Serial.println(F(" mSecs \n"));

  Serial.println(F("Returning to menu. Please wait. \n"));

  Serial.setTimeout(500);
  str = Serial.readStringUntil('\n'); // empty the buffer
}


void do_Relay1Time()
{
  int incomingByte = 0;
  String str;
  int input;

  // Get the delay time
  Serial.println(F("Input the Delay time in mSec (100 - 1000) \n"));
  str = Serial.readStringUntil('\n'); // empty the buffer
 
  Serial.setTimeout(5000);
  str = Serial.readStringUntil('\n');
  Serial.print(F("Input: ")); Serial.print(str); Serial.println();

  input = str.toInt();
  if ((input < 0) || (input > 1000))
  {
    Serial.print(F("Invalid value input"));
  }
  else
  {
    Serial.println(F("Save the setting"));
    EEPROM.put(AddrRelay1Delay, input);
  }

  EEPROM.get(AddrRelay1Delay, RELAY1_DELAY);
 
  //Serial.println("");
  Serial.print(F("Relay delay set to : ")); Serial.print(RELAY1_DELAY); Serial.println(F(" mSec \n"));
    

// Get the Operate time
  Serial.println(F("Input the Operate time in mSec (100 - 1000) \n"));
//  str = Serial.readStringUntil('\n'); // empty the buffer
  Serial.setTimeout(5000);
  
  str = Serial.readStringUntil('\n');
  Serial.print(F("Input: "));   Serial.print(str);   Serial.println("");

  input = str.toInt();
  if ((input < 100) || (input > 1000))
  {
    Serial.print(F("Invalid value input"));
  }
  else
  {
    Serial.println(F("Save the setting"));
    EEPROM.put(AddrRelay1Time, input);
  }

  EEPROM.get(AddrRelay1Time, RELAY1_PULSE_TIME);
 
  //Serial.println("");
  Serial.print(F("Relay time set to : ")); Serial.print(RELAY1_PULSE_TIME); Serial.println(F(" mSec \n"));

  Serial.println(F("Returning to menu. Please wait. \n"));

  Serial.setTimeout(500);
  str = Serial.readStringUntil('\n'); // empty the buffer
}


void do_Relay2Time()
{
  int incomingByte = 0;
  String str;
  int input;

  // Get the delay time
  Serial.println(F("Input the Delay time in mSec (0 - 1000) \n"));
  str = Serial.readStringUntil('\n'); // empty the buffer
 
  Serial.setTimeout(5000);
  str = Serial.readStringUntil('\n');
  Serial.print(F("Input: ")); Serial.print(str); Serial.println();

  input = str.toInt();
  if ((input < 0) || (input > 1000))
  {
    Serial.print(F("Invalid value input"));
  }
  else
  {
    Serial.println(F("Save the setting"));
    EEPROM.put(AddrRelay2Delay, input);
  }

  EEPROM.get(AddrRelay2Delay, RELAY2_DELAY);
  Serial.print(F("Relay delay set to : ")); Serial.print(RELAY2_DELAY); Serial.println(F(" mSec \n"));
    

// Get the Operate time

  Serial.println(F("Input the Operate time in mSec (100 - 1000) \n"));
  Serial.setTimeout(5000);
  
  str = Serial.readStringUntil('\n');
  Serial.print(F("Input: ")); Serial.print(str); Serial.println();

  input = str.toInt();
  if ((input < 100) || (input > 1000))
  {
    Serial.print(F("Invalid value input"));
  }
  else
  {
    Serial.println(F("Save the setting"));
    EEPROM.put(AddrRelay2Time, input);
  }

  EEPROM.get(AddrRelay2Time, RELAY2_PULSE_TIME);
  Serial.print(F("Relay time set to : ")); Serial.print(RELAY2_PULSE_TIME); Serial.println(F(" mSec \n"));
  Serial.println(F("Returning to menu. Please wait. \n"));

  Serial.setTimeout(500);
  str = Serial.readStringUntil('\n'); // empty the buffer
}


void do_PulsesPerMetre()
{
  int incomingByte = 0;
  String str;
  int input;

// Get the Pulse parameter
  Serial.println(F("Input the number of pulses per metre (10 - 200) \n"));
  str = Serial.readStringUntil('\n'); // empty the buffer

  Serial.setTimeout(5000);
  str = Serial.readStringUntil('\n');
  Serial.print(F("Input: ")); Serial.println(str);

  input = str.toInt();
  if ((input < 10) || (input > 200))
  {
    Serial.print(F("Invalid value input"));
  }
  else
  {
    Serial.println(F("Save the setting"));
    EEPROM.put(AddrPulses, input);
  }

  EEPROM.get(AddrPulses, PULSES_PER_METRE);
  Serial.print(F("Pulses per metre set to : ")); Serial.println(PULSES_PER_METRE);

  Serial.println(F("Returning to menu. Please wait. \n"));

  Serial.setTimeout(500);
  str = Serial.readStringUntil('\n'); // empty the buffer
  
}


void do_menu()
{
  int incomingByte = 0;   // for incoming serial data
  
  if (Serial.available() > 0) 
  {
    // read the incoming byte:
    incomingByte = Serial.read();

    //Serial.println(F("Received:  "));  // Uncomment for debug
    //Serial.println(F(incomingByte));

    Serial.setTimeout(500);
    
    if (incomingByte == 49)
    {
      Serial.println(F("*** 1. Set Relay 1 times"));
      Serial.println("");
      do_Relay1Time();
      
      String str = Serial.readStringUntil('\n');
      show_menu();
    } 
    else if (incomingByte == 50)
    {
      Serial.println(F("*** 2. Set Relay 2 times"));
      Serial.println("");
      do_Relay2Time();
      
      String str = Serial.readStringUntil('\n');
      show_menu();
    } 
    else if (incomingByte == 51)
    {
      Serial.println(F("*** 3. Set Pulses per metre"));
      Serial.println("");
      do_PulsesPerMetre();
      
      String str = Serial.readStringUntil('\n');
      show_menu();
    } 
    else if (incomingByte == 52)
    {
      Serial.println(F("*** 4. Set Simulation speed "));
      Serial.println(F(""));
      do_CalSpeed();
      
      String str = Serial.readStringUntil('\n');
      show_menu();
    } 
    else if (incomingByte == 53)
    {
      metres = thumb.ReadThumbwheels();
      
      Serial.println(F("*** 5. Display Settings "));
      Serial.println();
      
      Serial.println(F("Mode:  CALIBRATION"));
      Serial.print(F("Simulation Speed: ")); Serial.print(calibratespeed); Serial.println(F(" km/hr"));
      Serial.print(F("Distance:          ")); Serial.print(metres); Serial.println(F(" metres"));
      Serial.print(F("Relay 1:    Delay: ")); Serial.print(RELAY1_DELAY); Serial.print(F("mSec  Duration: ")); Serial.print(RELAY1_PULSE_TIME); Serial.println(F(" mSec"));
      Serial.print(F("Relay 2:    Delay: ")); Serial.print(RELAY2_DELAY); Serial.print(F("mSec  Duration: ")); Serial.print(RELAY2_PULSE_TIME); Serial.println(F(" mSec"));
      Serial.print(F("Cal. Pulses per metre:  ")); Serial.println(PULSES_PER_METRE);
      Serial.print(F("Input Pulses per metre: ")); Serial.println(PULSES_PER_METRE * 4);
      Serial.println("\n");
      String str = Serial.readStringUntil('\n');
      show_menu();      
    }
    else if (incomingByte == 79)
    {
      String str = Serial.readStringUntil('\n');
      mode = OPERATE;
      isActive = false;
      led.On(RED);

      Serial.println(F("*** Mode is set to OPERATE"));
      Serial.println(F("Press C to switch to Calibrate mode"));
      Serial.println(F(" "));
      Serial.println(F("Waiting to start"));
      Serial.println("");
      
      //show_menu();
    } 
    else if (incomingByte == 82)
    {
      Serial.println(F("*** RESET "));
      Serial.println(F(" "));
      
      // Reset with watchdog
      delay(500);
      wdt_enable(WDTO_15MS); // turn on the WatchDog and don't stroke it.
      
      for(;;) 
      { 
       // do nothing and wait for the eventual...
      }
    } 
    else
    {
      Serial.println(F("*** Invalid selection ***"));
      //Serial.println(incomingByte);   // Uncomment for debug
      Serial.println();
      String str = Serial.readStringUntil('\n');
      show_menu();
    }
  }
}


#endif  // MENU_H
