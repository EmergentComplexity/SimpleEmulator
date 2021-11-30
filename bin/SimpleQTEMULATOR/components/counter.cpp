#include "counter.h"

counter::counter()
{

}


void counter::Update(bool CLK, bool CLR, bool LD, int INP) {
    if ((CLK == 1) && (CLK_Last == 0)) {  // clock on rising edge only
        if ( count == 15) {  // only 4 bits
            count = 0;
        }
        else if (CLR == 0) { // CLR is active low
            count = 0;
        }

        else if (LD == 0) {  // LD is active low
            count = INP;
        }
        else {
            count++;
        }
    }
    CLK_Last = CLK;
}

int counter::getCount() {
    return count;
}

void counter::resetCnt() {
    count = 0;
}
