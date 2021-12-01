#ifndef SRLATCH_H
#define SRLATCH_H


class SRLatch
{

private:
    bool Q;
    bool Qprime;
public:
    SRLatch();
    void Update( bool S, bool R);
    bool getQ();
    bool getQprime();
};

#endif // SRLATCH_H
