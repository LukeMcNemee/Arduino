#ifndef _MORSE_
#define _MORSE_

/**
 * @file MyFirstLib.h
 * @author John Doe
 * @version 1.0
 */

#include <Arduino.h>

class Morse {

	public:

		Morse();

		void definePins(int pins) const;
		void methodNumberTwo() const;

	private:

		//	VARIABLES
		uint8_t _variableOne;
		uint8_t _variableTwo;

		//	CONSTANTS
};

#endif
