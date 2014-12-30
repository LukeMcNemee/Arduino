#include <Arduino.h>
#include <RF12.h>
#include <radioutils.h>




void setup () {
  Serial.begin(57600);
  Serial.println("\n[Alive Send]");
#if !DEBUG
  rf12_initialize(1, RF12_868MHZ, 5);
#endif
}



void loop () {
  delay(10);
}