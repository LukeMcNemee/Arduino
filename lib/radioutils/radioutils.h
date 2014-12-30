#ifndef RADIOUTILS_H
#define RADIOUTILS_H
#include <Arduino.h>

class radioUtils
{
public:
    radioUtils();

    int setAck();

    int resetAck();

    int setBroadcast();

    int setDstID(byte id);

    int getSrcID();
};

#endif // RADIOUTILS_H
