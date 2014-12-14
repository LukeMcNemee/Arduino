#ifndef _MORSE_
#define _MORSE_
#define RGB
/**
 * @file Morse.h
 * @author LukeMcNemee
 * @version 1.0
 */

#include <Arduino.h>

class Morse {

public:

    void setInterrupt();
    void resetInterrupt();

#ifdef RGB
    Morse(int red, int green, int blue);
    void defineColor(int red, int green, int blue);
#else
    Morse(int pin);
#endif

    void msg(char *msg);


private:
    //all morse code letters and some extra, number representing length of beep, thus 13 <=> ._ <=> A
    static const char* code[];
    //same as code, but in ascii, indexes are equal
    static const char* ascii;

    static const int dotLength = 250;

    bool interrupt;

#ifdef RGB
    int pin[3];
    int color[3];
#else
    int pin[1];
#endif

};

#endif
