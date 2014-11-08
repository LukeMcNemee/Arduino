#include <Morse.h>

int globalRed = 0;
int globalGreen = 0;
int globalBlue = 0;

Morse morse;

void color(int red, int green, int blue){
  analogWrite(11, red);
  analogWrite(10, blue);
  analogWrite(9, green);
}

void readAnalog(){
  int red = analogRead(A0);
  int green = analogRead(A1);
  int blue = analogRead(A2);
  
  globalRed = map(red, 0, 1023, 0, 255);
  globalBlue = map(blue, 0, 1023, 0, 255);
  globalGreen = map(green, 0, 1023, 0, 255);

}

void setup() {
  // put your setup code here, to run once:
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
  
    pinMode(11, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
    
    Serial.begin(9600);
}

void loop() {
    //morse.methodNumberOne();
    readAnalog();
    color(globalRed, globalGreen, globalBlue);
}
