#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include <avr/wdt.h>
#include "Global.h"

// Routines for menu handling


void show_menu()
{
    Serial.println("Setup Menu");
    //Serial.println("1. Select Calibration mode");
    //Serial.println("2. Select Operational mode");
    Serial.println("1. Set Calibration speed");
    Serial.println("2. Set Relay times");
    Serial.println("3. Display settings");
    Serial.println("");
    Serial.println("O. Switch to Operate mode");
    Serial.println("");
    Serial.println("R. RESET");
    Serial.println("");
    Serial.println("Waiting to start Calibration run");
    Serial.println(" ");

}


void do_CalSpeed()
{
  int incomingByte = 0;
  String str;
  float inputspeed;
  //float operationtime;
  
  //Serial.println(str);
  Serial.println("Input the speed in km/hr (0.1 - 3)");
  Serial.println(" ");

  str = Serial.readStringUntil('\n'); // empty the buffer

  Serial.setTimeout(5000);

  str = Serial.readStringUntil('\n');
  Serial.print("Input: ");
  Serial.print(str);
  Serial.println(" ");

  inputspeed = str.toFloat();
  if (inputspeed < 0.1)
  {
    Serial.print("Invalid value");
  }
  else if (inputspeed > 3.0)
  {
    Serial.print("Invalid value");
  }
  else
  {
    calibratespeed = inputspeed;
  }

  calibrateTime = 3600 / (calibratespeed * GPS_PULSES_PER_METRE); // calculate the time between pulses
  
  Serial.println(" ");
  Serial.print("Calibration speed set to : ");
  Serial.print(calibratespeed);
  Serial.println(" km/hr");
  Serial.println(" ");
    
  Serial.print("Time between operations is: ");
  Serial.print((3.6 * metres) / calibratespeed);
  Serial.println(" Seconds");
  Serial.println(" ");

  Serial.println("Returning to menu. Please wait.");
  Serial.println(" ");

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

    //Serial.println("Received:  ");  // Uncomment for debug
    //Serial.println(incomingByte);

    Serial.setTimeout(500);
    
    if (incomingByte == 49)
    {
      Serial.println("*** 1. Set Calibrate speed ");
      Serial.println(" ");
      //Serial.println("Input the speed in km/hr (0.1 - 10)");
      do_CalSpeed();
      String str = Serial.readStringUntil('\n');
      show_menu();
    } 
    else if (incomingByte == 50)
    {
      Serial.println("*** 2. Set Relay times - TBD");
      Serial.println(" ");
      String str = Serial.readStringUntil('\n');
      show_menu();
    } 
    else if (incomingByte == 51)
    {
      Serial.println("*** 3. Display Settings ");
      Serial.println(" ");
      
      Serial.print("Mode:  "); Serial.println("CALIBRATION");
      Serial.print("Calibration Speed: "); Serial.print(calibratespeed); Serial.println("km/hr");
      Serial.print("Relay 1:    Delay: "); Serial.print("  0"); Serial.print("mSec  Duration: "); Serial.print("400"); Serial.println("mSec");
      Serial.print("Relay 2:    Delay: "); Serial.print("500"); Serial.print("mSec  Duration: "); Serial.print("500"); Serial.println("mSec");
      Serial.println("");
      Serial.println("");
      String str = Serial.readStringUntil('\n');
      show_menu();      
    }
    else if (incomingByte == 79)
    {
      String str = Serial.readStringUntil('\n');
      calmode = false;
      isActive = false;
      led.On(RED);

      Serial.println("*** Mode is set to OPERATE");
      Serial.println("Press C to switch to Calibrate mode");
      Serial.println(" ");
      Serial.println("Waiting to start");
      Serial.println(" ");
      
      //show_menu();
    } 
    else if (incomingByte == 82)
    {
      Serial.println("*** RESET ");
      Serial.println(" ");
      
      // Reset with watchdog
      delay(500);
      wdt_enable(WDTO_15MS); // turn on the WatchDog and don't stroke it.
      for(;;) { 
       // do nothing and wait for the eventual...
      }
    } 
    else
    {
      Serial.println("*** Invalid selection ***");
      //Serial.println(incomingByte);   // Uncomment for debug
      Serial.println(" ");
      String str = Serial.readStringUntil('\n');
      show_menu();
    }
  }
}


#endif  // MENU_H
