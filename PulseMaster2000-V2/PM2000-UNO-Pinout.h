
 PM2000-UNO Adapter Board Connections
 ------------------------------------

Schematic:   http://schematics.com/project/pulse-master-2000-uno-v1-33367/

1. Power - Three pin header
   ------------------------
Pin 1 Red   - +12 V
Pin 2       - NC
Pin 3 Black - Gnd


2. Thumbwheels - Eight pin header
   ------------------------------
Pin 1 Br - BCD 1
Pin 2 Rd - BCD 2
Pin 3 Or - BCD 4
Pin 4 Ye - BCD 8
Pin 5 Gn - Digit 1 - Units
Pin 6 Bl - Digit 2 - Tenths
Pin 7 Pu - Digit 2 - Hundredths
Pin 8 Gr - Reserved


3. Switch, GPS, LED, Relay - Ten pin header
   ----------------------------------------
Pin 1 Br - Gnd
Pin 2 Rd - Pushbutton

Pin 3 Or - GPS Pulse Input +
Pin 4 Ye - GPS Pulse Input -

Pin 5 Gn - R/G LED 
Pin 6 Bl - R/G LED

Pin 7 Pu - Relay 1    | Connected to     | Pin 1 Wh - VCC
Pin 8 Gr - Relay 2    | four pin header  | Pin 2 Pu - Relay 1
Pin 9 Wh - VCC        | on relay board   | Pin 3 Gr - Relay 2
Pin 10 Bk - Gnd       |                  | Pin 4 Bk - Gnd


