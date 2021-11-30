#include "register.h"

Register::Register()
{
 data = 0;
}
void Register::Update(bool CLK, int dataIn) {
    if ((CLK == 1) && (CLK_Last == 0)) {  // clock on rising edge only
       data = dataIn;
    }
    CLK_Last = CLK;
}


int Register::getRegVal() {
    return data;
}
