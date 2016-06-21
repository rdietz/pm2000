#ifndef GLOBAL_H
#define GLOBAL_H

// Key variables
volatile unsigned long counter;  // GPS pulse count
unsigned long lastCounter;       // for checking that we're receiving GPS pulses
int lastButtonState;             // track state of the master button

int PULSES_PER_METRE;            // the number of pulses per metre travelled

int RELAY1_DELAY;
int RELAY1_PULSE_TIME;
int RELAY2_DELAY;
int RELAY2_PULSE_TIME;

long PulsesPerTrigger;          // the number of GPS pulses between relay triggers
unsigned long lastMillis;       // last millisecond value
unsigned long calibrateMillis;  // Calibration mode millisecond counter value
unsigned long calibrateTime;    // Period of pulses in Calibration mode
float calibratespeed;           // the current setting for calibrate mode speed
float metres;                   // required distance as set on thumbwheels
bool isActive;                  // indicates we're actively counting GPS pulses
bool firstcycle;                // indicates the first cycle
int mode;                       // indicates Calibrate mode


// Setup controller objects
LedController led(ledPin1, ledPin2);  // object to control the LED
Debouncer btn1(buttonPin);            // object to debounce the main button
Thumbwheel thumb;                     // object to read the thumbwheels

Pulser relay1(relay1Pin);
Pulser relay2(relay2Pin);

#endif  // GLOBAL_H
