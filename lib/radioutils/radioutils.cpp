#include "radioutils.h"
#include <RF12.h>
#include <Arduino.h>

radioUtils::radioUtils(){

}

int radioUtils::setAck(byte* hdr){
    byte ackOr = B10000000;
    *hdr = (*hdr | ackOr);
    return 0;
}

int radioUtils::resetAck(byte* hdr){
    byte ackOr = B10000000;
    *hdr =(*hdr & ~ackOr);
    return 0;
}

int radioUtils::setBroadcast(byte* hdr){
    byte broadOr = B10111111;
    *hdr = (*hdr & broadOr);
    return 0;
}

int radioUtils::setID(byte* hdr, byte id){
    byte idAnd = B00011111;
    id = (id & idAnd);
    *hdr = (*hdr & ~idAnd);
    *hdr = (*hdr | id);
    return 0;
}

int radioUtils::getID(byte* hdr, byte* id){
    byte idAnd = B00011111;
    *id = *hdr & idAnd;
    return 0;
}
