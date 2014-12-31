#include <Arduino.h>
#include <RF12.h>
#include <radioutils.h>

int counter = 0; //
int msgCounter = 0; 

void setup () {
  Serial.begin(57600);
  Serial.println("\n[Alive Send]");
#if !DEBUG
  rf12_initialize(ID, RF12_868MHZ, GROUP);
#endif
}

void loop () {  
  //if incoming message received
  if(rf12_recvDone()){
    if(RF12_WANTS_ACK){
      rf12_sendStart(RF12_ACK_REPLY,0,0);
    }
    
    if(rf12_crc == 0){ //packet checksum is correct
      //propagate to parent 
      byte header = B00000000;
      //fill header using radioUtils      
      rf12_sendNow(header, (const void*)rf12_data, rf12_len);
    }
  }
  
  delay(10);  
  counter++;
  
  if(counter%100 == 0){
    msgCounter++;
    //send still alive msg
    byte header = B00000000;
    //fill header using radioUtils
    void* data; 
    rf12_sendNow(header, (const void*) &msgCounter, sizeof(counter));
    counter = 0;
  }
}