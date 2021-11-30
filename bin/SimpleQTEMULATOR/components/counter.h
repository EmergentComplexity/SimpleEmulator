#ifndef COUNTER_H
#define COUNTER_H


class counter
{
private:
    int count = 0;
    int CLK_Last = 0; // used to detect rising edge of clock
public:
    counter();
    void Update(bool CLK, bool CLR, bool LD, int INP);
    int getCount();
    void resetCnt(); // reset the count for programming purposes, avoids using Update()
};

#endif // COUNTER_H
