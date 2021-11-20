#include "srlatch.h"

SRLatch::SRLatch()
{
    // initial state of SR Latch
    Qprime = 1;
    Q = 0;
}


void SRLatch::Update( bool S, bool R) {

    // ignore cases where S == R
    if ((S == 1) && (R == 0)) {
        Q = 1;
        Qprime = 0;
    }
    else if((S == 0) && (R == 1)) {
        Q = 0;
        Qprime = 1;
    }
}

bool SRLatch::getQ() {
    return Q;
}
bool SRLatch::getQprime() {
    return Qprime;
}
