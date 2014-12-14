#include <Arduino.h>
#include "Morse.h"


#ifdef RGB
Morse::Morse(int red, int blue, int green){
    pin[0] = red;
    pin[1] = green;
    pin[2] = blue;
}

void Morse::defineColor(int red, int green, int blue){
    color[0] = red;
    color[1] = green;
    color[2] = blue;
    interrupt = false;
}
#else
Morse::Morse(int pin){
    this->pin[0] = pin;
    interrupt = false;
}

#endif

void Morse::msg(char *msg){
    for (unsigned int i = 0; i < strlen(msg); i++){

        char* found = strchr(ascii, msg[i]);

        Serial.print(msg[i]);
        if(interrupt) return;
        if(found != NULL){ //found in ascii string
            //beep it out
            int index = found - ascii;
            Serial.print(ascii[index]);
            Serial.println(code[index]);
            for (unsigned int j = 0; j < strlen(code[index]); j++){
                //start dot or dash
#ifdef RGB
                digitalWrite(pin[0], color[0]);
                digitalWrite(pin[1], color[1]);
                digitalWrite(pin[2], color[2]);
#else
                digitalWrite(pin[0], HIGH);
#endif
                if(code[index][j] == '1'){
                    delay(dotLength);
                    Serial.print('.');

                } else {
                    delay(6*dotLength);
                    Serial.print('_');
                }
#ifdef RGB
                digitalWrite(pin[0], LOW);
                digitalWrite(pin[1], LOW);
                digitalWrite(pin[2], LOW);
#else
                digitalWrite(pin[0], LOW);
#endif
                Serial.println(code[index][j]);
                //end dot or dash
                delay(dotLength);
                if(interrupt) return;
            }

        } else if(msg[i] == ' '){ //if not found, check if space
            delay(dotLength*5);
        } else {
            //else skip and delay
            delay(dotLength*10);
        }
        //end letter
        delay(dotLength*3);
        if(interrupt) return;
    }
    delay(dotLength*7);
    if(interrupt) return;
}


void Morse::setInterrupt(){
    interrupt = true;
}

void Morse::resetInterrupt(){
    interrupt = false;
}


const char* Morse::ascii = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,?'!/()&:;=+-_\"$@";
const char* Morse::code[] = {"13","3111","3131","311","1","1131","331","1111","11","1333","313","1311","33","31","333","1331","3313","131","111","3","113","1113","133","3113","3133","3311","33333","13333","11333","11133","11113","11111","31111","33111","33311","33331","131313","331133","113311","133331","313133","31131","31331","313313","13111","333111","313131","31113","13131","311113","113313","131131","1113113","133131"};
