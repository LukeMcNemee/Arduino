#include <Morse.h>
#include <RotaryEncoder.h>

#define RGB
#define STATES 20

int globalRed = 0;
int globalGreen = 0;
int globalBlue = 0;
int pos = 0;

RotaryEncoder encoder(A2, A3);

#ifdef RGB
Morse morse(9,10,11);
#else
Morse morse(9);
#endif

void color(int red, int green, int blue){
    analogWrite(11, red);
    analogWrite(10, blue);
    analogWrite(9, green);
}

void fade(int red, int green, int blue){
    for(int i = 255; i >1; i--){
	color((int)red/i, (int)green/i, (int)blue/i);
	delay(10);
    }  
}



void setup() {
    
    pinMode(11, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
    
    Serial.begin(9600);
    Serial.println("Hello");
    
#ifdef RGB
    morse.defineColor(255,255,255);
#endif
    /* Setup encoder pins as inputs 
    pinMode(ENC_A, INPUT);
    digitalWrite(ENC_A, HIGH);
    pinMode(ENC_B, INPUT);
    digitalWrite(ENC_B, HIGH);
   */
    PCICR |= (1 << PCIE1);    // This enables Pin Change Interrupt 1 that covers the Analog input pins or Port C.
    PCMSK1 |= (1 << PCINT10) | (1 << PCINT11);  // This enables the interrupt for pin 2 and 3 of Port C.
}

// The Interrupt Service Routine for Pin Change Interrupt 1
// This routine will only be called on any signal change on A2 and A3: exactly where we need to check.
ISR(PCINT1_vect) {
  encoder.tick(); // just call tick() to check the state.
}

void loop() {
    color(0,0,0);
    static int pos = 0;
    int newPos = encoder.getPosition();
    if (pos != newPos) {
      Serial.print(newPos);
      Serial.println();
      pos = newPos % STATES;
    } 
    switch (pos){
      case  0:
	morse.msg("SOS");	
	
	break;
      case  1:
      case  2:
	color(0,0,255);
	break;
      case  3:
      case  4:
      case  5:
	fade(0, 0, 255);
	break;
      case  6:
      case  7:
      case  8:
      case  9:
	color(0,255,0);
	break;
      case 10:
      case 11:
      case 12:
	fade(0, 255, 0);
	break;
      case 13:
      case 14:
      case 15:
      case 16:
	color(255,0,0);
	break;
      case 17:
      case 18:
      case 19:
	fade( 255, 0, 0);
	break;
      default:
	color(255,0,0);
	delay(10);	
	color(0,0,0);
	delay(10);
    }
}
