#include <Arduino.h>
#include "Morse.h"

Morse::Morse() {
	// initialize variables
	_variableOne = 2;
	_variableTwo = 3;
}

void Morse::methodNumberOne() const {
	// print variable one
	Serial.println(_variableOne);
}

void Morse::methodNumberTwo() const {
	// print variable one
	Serial.println(_variableTwo);
}
