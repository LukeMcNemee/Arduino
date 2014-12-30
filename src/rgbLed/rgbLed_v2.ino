#include <Morse.h>
#include <RotaryEncoder.h>


#define RGB
#define STATES 24

int globalRed = 0;
int globalGreen = 0;
int globalBlue = 0;
int pos = STATES * 20;
int interrupt = false;


RotaryEncoder encoder(A2, A3);

#ifdef RGB
Morse morse(11,10,9);
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
	delay((255-i) /8);
	if (interrupt) return;
    }  
    delay(100);
}



void setup() {
    
    pinMode(11, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
    
    Serial.begin(9600);
    Serial.println("Hello");
    
#ifdef RGB
    morse.defineColor(50,0,50);
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
  morse.setInterrupt();
  interrupt = true;
}

void loop() {
    encoder.tick();
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
	fade(250,0,0);	
	break;
      case  1:
	fade(0,250,0);	
	break;
      case  2:
	fade(0,0,250);	
	break;
      case  3:
	fade(125,125,0);	
	break;
      case  4:
	fade(125,0,125);	
	break;
      case  5:
	fade(0,125,125);
	break;
      case  6:
	morse.defineColor(250,0,0);
	morse.msg("AHOJ ");	
	break;
      case  7:
	morse.defineColor(0,250,0);
	morse.msg("AHOJ ");	
	break;
      case  8:
	morse.defineColor(0,0,250);
	morse.msg("AHOJ ");	
	break;
      case  9:
	morse.defineColor(125,125,0);	
	morse.msg("AHOJ ");
	break;
      case  10:
	morse.defineColor(125,0,125);	
	morse.msg("AHOJ ");
	break;
      case  11:
	morse.defineColor(0,125,125);
	morse.msg("AHOJ ");
	break;
      case  12:
	morse.defineColor(250,0,0);
	morse.msg("MILUJI CHEMII ");	
	break;
      case  13:
	morse.defineColor(0,250,0);
	morse.msg("KOFEIN ");	
	break;
      case  14:
	morse.defineColor(0,0,250);
	morse.msg("SPIRIT ");	
	break;
      case  15:
	morse.defineColor(125,125,0);	
	morse.msg("MILUJI CHEMII ");
	break;
      case  16:
	morse.defineColor(125,0,125);	
	morse.msg("KOFEIN ");
	break;
      case  17:
	morse.defineColor(0,125,125);
	morse.msg("SPIRIT ");
	break;
      case  18:
	morse.defineColor(250,0,0);
	morse.msg("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.");	
	break;
      case  19:
	morse.defineColor(0,250,0);
	morse.msg("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.");	
	break;
      case  20:
	morse.defineColor(0,0,250);
	morse.msg("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.");	
	break;
      case  21:
	morse.defineColor(125,125,0);	
	morse.msg("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.");
	break;
      case  22:
	morse.defineColor(125,0,125);	
	morse.msg("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.");
	break;
      case  23:
	morse.defineColor(0,125,125);
	morse.msg("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.");
	break;
      default:
	color(255,0,0);
	delay(10);	
	color(0,0,0);
	delay(10);
    }
    
    morse.resetInterrupt();
    interrupt = false;
}

//250,0,0 -red 
//0,250,0 -green
//0,0,250 -blue
//125,125,0 - orange
//125,0,125 - purple 
//0,125,125 - aqua
