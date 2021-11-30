#ifndef DECODER_H
#define DECODER_H


class Decoder
{
private:
    bool HLT = 0;
    bool ADD = 0;
    bool SUB = 0;
    bool STO = 0;
    bool LD = 0;
    bool B = 0;
    bool BZ = 0;
    bool LDV = 0;
    bool INP = 0;
    bool OUT = 0;
    bool AND = 0;
    bool OR = 0;
    bool NOT = 0;
public:
    Decoder();
    void Update(int dataIn);
    bool getHLT();
    bool getADD();
    bool getSUB();
    bool getSTO();
    bool getLD();
    bool getB();
    bool getBZ();
    bool getLDV();
    bool getINP();
    bool getOUT();
    bool getAND();
    bool getOR();
    bool getNOT();
};

#endif // DECODER_H
