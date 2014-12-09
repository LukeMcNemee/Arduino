#include <Morse.h>
#include <RotaryEncoder.h>


#define ENC_A 8
#define ENC_B 9
#define ENC_PORT PINB

int globalRed = 0;
int globalGreen = 0;
int globalBlue = 0;
int pos = 0;

RotaryEncoder encoder(A2, A3);


Morse morse;

void color(int red, int green, int blue){
    analogWrite(11, red);
    analogWrite(10, blue);
    analogWrite(9, green);
}



void setup() {
    
    pinMode(11, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
    
    Serial.begin(9600);
    Serial.println("Hello");
    
    
    /* Setup encoder pins as inputs */
    pinMode(ENC_A, INPUT);
    digitalWrite(ENC_A, HIGH);
    pinMode(ENC_B, INPUT);
    digitalWrite(ENC_B, HIGH);
   
    
}

void loop() {
    //morse.methodNumberOne();
    static int pos = 0;
    encoder.tick();

    int newPos = encoder.getPosition();
    if (pos != newPos) {
      Serial.print(newPos);
      Serial.println();
      pos = newPos;
    } // if
    if (((pos*5)%255) >= 170){
	color(0, 0, 255);
    }
    else if (((pos*5)%255) >= 80){    
	color(0, 255, 0);	
    } else {
        color( 255, 0, 0);	
    }
}
