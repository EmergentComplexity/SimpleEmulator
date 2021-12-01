#include "decoder.h"

Decoder::Decoder()
{
    HLT = 0;
    ADD = 0;
    SUB = 0;
    STO = 0;
    LD = 0;
    B = 0;
    BZ = 0;
    LDV = 0;
    INP = 0;
    OUT = 0;
    AND = 0;
    OR = 0;
    NOT = 0;
}


void Decoder::Update(int dataIn) {
    HLT = 0;
    ADD = 0;
    SUB = 0;
    STO = 0;
    LD = 0;
    B = 0;
    BZ = 0;
    LDV = 0;
    INP = 0;
    OUT = 0;
    AND = 0;
    OR = 0;
    NOT = 0;
    switch (dataIn) {
        case 0b0000: {
            HLT = 1;
            break;
        }
        case 0b0001: {
            ADD = 1;
            break;
        }
        case 0b0010: {
            SUB = 1;
            break;
        }
        case 0b0011: {
            STO = 1;
            break;
        }
        case 0b0100: {
            LD = 1;
            break;
        }
        case 0b0101: {
            B = 1;
            break;
        }
        case 0b0110: {
            BZ = 1;
            break;
        }
        case 0b0111: {
            LDV = 1;
            break;
        }
        case 0b1000: {
            INP = 1;
            break;
        }
        case 0b1001: {
            OUT = 1;
            break;
        }
        case 0b1010: {
            AND = 1;
            break;
        }
        case 0b1011: {
            OR = 1;
            break;
        }
        case 0b1100: {
            NOT = 1;
            break;
        }
        case 0b1101: {
            // free
            break;
        }
        case 0b1110: {
            // free
            break;
        }
        case 0b1111: {
            // free
            break;
        }
    }
}
bool Decoder::getHLT() {
    return HLT;
}
bool Decoder::getADD() {
    return ADD;
}
bool Decoder::getSUB() {
    return SUB;
}
bool Decoder::getSTO() {
    return STO;
}
bool Decoder::getLD() {
    return LD;
}
bool Decoder::getB() {
    return B;
}
bool Decoder::getBZ() {
    return BZ;
}
bool Decoder::getLDV() {
    return LDV;
}
bool Decoder::getINP() {
    return INP;
}
bool Decoder::getOUT() {
    return OUT;
}
bool Decoder::getAND() {
    return AND;
}
bool Decoder::getOR() {
    return OR;
}
bool Decoder::getNOT() {
    return NOT;
}
