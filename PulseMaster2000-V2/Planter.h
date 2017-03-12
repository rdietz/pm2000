#ifndef PLANTER_H
#define PLANTER_H

void do_planter_init()
{
  Serial.println(F("Planter initialisation")); 
  Serial.println();

  /* Ensure all outputs are off */
  digitalWrite(relay1Pin, HIGH);
  digitalWrite(relay2Pin, HIGH);
  digitalWrite(relay3Pin, HIGH);
  digitalWrite(relay4Pin, HIGH);

  /* Operate Relay 2 to raise auger */
  Serial.println(F("Raise auger")); 
  Serial.println();
  digitalWrite(relay2Pin, LOW);
  delay(1000);
  digitalWrite(relay2Pin, HIGH);
  delay(500);
  
  /* Operate Relay 4 to return carriage */
  Serial.println(F("Return carriage")); 
  Serial.println();
  digitalWrite(relay4Pin, LOW);
  delay(1000);
  digitalWrite(relay4Pin, HIGH);
  delay(500);
}


#endif  // PLANTER_H
